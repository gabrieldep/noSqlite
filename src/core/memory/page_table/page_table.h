#ifndef NOSQLITE_PAGE_TABLE_H
#define NOSQLITE_PAGE_TABLE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct HashNode {
    uint32_t page_id; // The key: Disk page identifier
    size_t frame_id; // The value: Index inside the memory page_pool array
    struct HashNode *next; // Pointer to the next node in case of bucket collision
} HashNode;

static inline size_t page_table_hash(uint32_t page_id, size_t pool_size) {
    return (size_t) (page_id % pool_size);
}

bool page_table_lookup(HashNode **buckets, size_t pool_size, uint32_t page_id, size_t *out_frame);

void page_table_insert(HashNode **buckets, HashNode *node_pool, size_t pool_size, uint32_t page_id, size_t frame_id);

bool page_table_remove(HashNode **buckets, size_t pool_size, uint32_t page_id);

#endif //NOSQLITE_PAGE_TABLE_H
