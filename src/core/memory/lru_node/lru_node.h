#ifndef NOSQLITE_LRU_NODE_H
#define NOSQLITE_LRU_NODE_H
#include <stddef.h>

typedef struct LRUNode {
    size_t prev;
    size_t next;
} LRUNode;

typedef struct LRUList {
    LRUNode *pool; // Points to the array of size pool_size
    size_t pool_size;
    size_t head; // Most Recently Used frame
    size_t tail; // Least Recently Used frame (The Victim)
} LRUList;

// Initializes the LRU list tracking state (everything starts pinned/empty)
void lru_init(LRUList *lru, LRUNode *pool, size_t pool_size);

// Adds a frame to the front (head) of the list (Most Recently Used)
void lru_unpin(LRUList *lru, size_t frame_id);

// Removes a frame from ANYWHERE in the list (pinned/active frame)
void lru_pin(LRUList *lru, size_t frame_id);

// Removes the last item (tail) and returns its frame_id via out_frame
bool lru_victim(LRUList *lru, size_t *out_frame);

#endif //NOSQLITE_LRU_NODE_H
