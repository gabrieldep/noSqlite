#include "page_manager.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../errors/storage_error.h"

struct PageManager {
    FILE *file;
};

PageManager *page_manager_create(const char *filepath) {
    PageManager *pm = calloc(1, sizeof(PageManager));
    if (pm == NULL) {
        return NULL;
    }
    pm->file = fopen(filepath, "r+b");

    if (pm->file == NULL) {
        pm->file = fopen(filepath, "w+b");
        if (pm->file == NULL) {
            free(pm);
            return NULL;
        }
    }
    return pm;
}

void page_manager_destroy(PageManager *pm) {
    if (pm != NULL) {
        if (pm->file != NULL) {
            fclose(pm->file);
        }
        free(pm);
    }
}

int page_manager_read(PageManager *pm, uint32_t page_id, Page *out_page) {
    if (pm == NULL || pm->file == NULL || out_page == NULL) {
        return NOSQLITE_ERR_DISK_READ_FAILURE;
    }

    long offset = (long)page_id * NOSQLITE_PAGE_SIZE;
    if (fseek(pm->file, offset, SEEK_SET) != 0) {
        return NOSQLITE_ERR_DISK_READ_FAILURE;
    }

    size_t bytes_read = fread(out_page->bytes, 1, NOSQLITE_PAGE_SIZE, pm->file);
    if (bytes_read < NOSQLITE_PAGE_SIZE) {
        for (size_t i = bytes_read; i < NOSQLITE_PAGE_SIZE; i++) {
            out_page->bytes[i] = 0;
        }
        return NOSQLITE_ERR_PAGE_NOT_FOUND;
    }
    return NOSQLITE_OK;
}

int page_manager_write(PageManager *pm, uint32_t page_id, const Page *in_page) {
    if (pm == NULL || pm->file == NULL || in_page == NULL) {
        return NOSQLITE_ERR_DISK_WRITE_FAILURE;
    }

    long offset = (long)page_id * NOSQLITE_PAGE_SIZE;
    if (fseek(pm->file, offset, SEEK_SET) != 0) {
        return NOSQLITE_ERR_DISK_WRITE_FAILURE;
    }

    size_t bytes_written = fwrite(in_page->bytes, 1, NOSQLITE_PAGE_SIZE, pm->file);

    if (bytes_written != NOSQLITE_PAGE_SIZE) {
        return NOSQLITE_ERR_DISK_WRITE_FAILURE;
    }

    if (fflush(pm->file) != 0) {
        return NOSQLITE_ERR_DISK_WRITE_FAILURE;
    }
    return NOSQLITE_OK;
}
