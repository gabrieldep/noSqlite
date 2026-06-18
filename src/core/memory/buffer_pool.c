#include "buffer_pool.h"

#include <stdlib.h>

#include "../../errors/storage_error.h"
#include "../storage/page.h"
#include "../storage/page_manager.h"
#include "frame_metadata.h"

struct BufferPool {
    size_t pool_size;
    PageManager *page_manager;

    Page *page_pool;
    FrameMetadata *frame_metadata;
    void *page_table;
    void *lru_list;
};

BufferPool *buffer_pool_create(size_t pool_size, PageManager *page_manager) {
    BufferPool *pool = calloc(1, sizeof(BufferPool));
    if (pool == NULL) {
        return NULL;
    }

    pool->pool_size = pool_size;
    pool->page_manager = page_manager;
    return pool;
}

void buffer_pool_destroy(BufferPool *pool) {
    free(pool);
}

Page *buffer_pool_fetch(BufferPool *pool, uint32_t page_id, int *err) {
    (void)pool;
    (void)page_id;
    if (err != NULL) {
        *err = NOSQLITE_OK;
    }
    return NULL;
}

int buffer_pool_unpin(BufferPool *pool, uint32_t page_id, int is_dirty) {
    (void)pool;
    (void)page_id;
    (void)is_dirty;
    return NOSQLITE_OK;
}

Page *buffer_pool_new_page(BufferPool *pool, uint32_t *out_page_id, int *err) {
    (void)pool;
    (void)out_page_id;
    if (err != NULL) {
        *err = NOSQLITE_OK;
    }
    return NULL;
}

int buffer_pool_flush_page(BufferPool *pool, uint32_t page_id) {
    (void)pool;
    (void)page_id;
    return NOSQLITE_OK;
}

int buffer_pool_flush_all_pages(BufferPool *pool) {
    (void)pool;
    return NOSQLITE_OK;
}
