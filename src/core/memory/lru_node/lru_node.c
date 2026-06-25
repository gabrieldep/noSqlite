#include <stddef.h>
#include <stdint.h>
#include "lru_node.h"
#include <stdbool.h>
#include <stdlib.h>
#define LRU_NULL ((size_t)-1)

void lru_init(LRUList *lru, LRUNode *pool, size_t pool_size) {
    lru->pool = pool;
    lru->pool_size = pool_size;
    lru->head = LRU_NULL;
    lru->tail = LRU_NULL;

    for (size_t i = 0; i < pool_size; i++) {
        lru->pool[i].prev = LRU_NULL;
        lru->pool[i].next = LRU_NULL;
    }
}

void lru_unpin(LRUList *lru, size_t frame_id) {
    if (lru->head == LRU_NULL) {
        lru->head = frame_id;
        lru->tail = frame_id;
        lru->pool[frame_id].prev = LRU_NULL;
        lru->pool[frame_id].next = LRU_NULL;
        return;
    }

    lru->pool[frame_id].next = lru->head;
    lru->pool[frame_id].prev = LRU_NULL;
    lru->pool[lru->head].prev = frame_id;
    lru->head = frame_id;
}

void lru_pin(LRUList *lru, size_t frame_id) {
    if (lru->head == LRU_NULL) {
        return;
    }

    if (lru->head == frame_id) {
        lru->head = lru->pool[frame_id].next;
    } else {
        size_t prev_node = lru->pool[frame_id].prev;
        lru->pool[prev_node].next = lru->pool[frame_id].next;
    }

    if (lru->tail == frame_id) {
        lru->tail = lru->pool[frame_id].prev;
    } else {
        size_t next_node = lru->pool[frame_id].next;
        lru->pool[next_node].prev = lru->pool[frame_id].prev;
    }

    lru->pool[frame_id].prev = LRU_NULL;
    lru->pool[frame_id].next = LRU_NULL;
}

bool lru_victim(LRUList *lru, size_t *out_frame) {
    if (lru->tail == LRU_NULL) {
        return false;
    }

    size_t victim = lru->tail;

    if (out_frame != NULL) {
        *out_frame = victim;
    }

    if (lru->head == lru->tail) {
        lru->head = LRU_NULL;
        lru->tail = LRU_NULL;
    }
    else {
        lru->tail = lru->pool[victim].prev;
        lru->pool[lru->tail].next = LRU_NULL;
    }

    lru->pool[victim].prev = LRU_NULL;
    lru->pool[victim].next = LRU_NULL;
    return true;
}
