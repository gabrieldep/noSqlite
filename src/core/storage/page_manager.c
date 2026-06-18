#include "page_manager.h"

#include <stdlib.h>

#include "errors/storage_error.h"

struct PageManager {
    int reserved;
};

PageManager *page_manager_create(void) {
    PageManager *pm = calloc(1, sizeof(PageManager));
    return pm;
}

void page_manager_destroy(PageManager *pm) {
    free(pm);
}

int page_manager_read(PageManager *pm, uint32_t page_id, Page *out_page) {
    (void)pm;
    (void)page_id;
    (void)out_page;
    return NOSQLITE_OK;
}

int page_manager_write(PageManager *pm, uint32_t page_id, const Page *in_page) {
    (void)pm;
    (void)page_id;
    (void)in_page;
    return NOSQLITE_OK;
}
