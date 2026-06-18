#ifndef NOSQLITE_FRAME_METADATA_H
#define NOSQLITE_FRAME_METADATA_H

#include <stdbool.h>
#include <stdint.h>

typedef struct FrameMetadata {
    uint32_t page_id;
    uint32_t pin_count;
    bool is_dirty;
} FrameMetadata;

#endif /* NOSQLITE_FRAME_METADATA_H */
