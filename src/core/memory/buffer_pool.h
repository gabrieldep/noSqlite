#ifndef NOSQLITE_BUFFER_POOL_H
#define NOSQLITE_BUFFER_POOL_H

#include <stddef.h>
#include <stdint.h>

#include "../storage/page.h"
#include "../storage/page_manager.h"

typedef struct BufferPool BufferPool;

BufferPool *buffer_pool_create(size_t pool_size, PageManager *page_manager);
void buffer_pool_destroy(BufferPool *pool);

Page *buffer_pool_fetch(BufferPool *pool, uint32_t page_id, int *err);
int buffer_pool_unpin(BufferPool *pool, uint32_t page_id, int is_dirty);
Page *buffer_pool_new_page(BufferPool *pool, uint32_t *out_page_id, int *err);
int buffer_pool_flush_page(BufferPool *pool, uint32_t page_id);
int buffer_pool_flush_all_pages(BufferPool *pool);

#endif /* NOSQLITE_BUFFER_POOL_H */
