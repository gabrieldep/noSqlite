#include <stddef.h>
#include <stdint.h>
#include "page_table.h"
#include <stdbool.h>

bool page_table_lookup(HashNode **buckets, size_t pool_size, uint32_t page_id, size_t *out_frame) {
    const size_t hash_id = page_table_hash(page_id, pool_size);
    HashNode *current = buckets[hash_id];

    while (current != NULL) {
        if (current->page_id == page_id) {
            if (out_frame != NULL) {
                *out_frame = current->frame_id;
            }
            return true;
        }
        current = current->next;
    }
    return false;
}

void page_table_insert(HashNode **buckets, HashNode *node_pool, size_t pool_size, uint32_t page_id, size_t frame_id) {
    const size_t hash_id = page_table_hash(page_id, pool_size);
    HashNode *new_node = &node_pool[frame_id];

    new_node->page_id = page_id;
    new_node->frame_id = frame_id;
    new_node->next = buckets[hash_id];

    buckets[hash_id] = new_node;
}

bool page_table_remove(HashNode **buckets, size_t pool_size, uint32_t page_id) {
    return false;
}
