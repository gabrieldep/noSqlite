#ifndef NOSQLITE_FRAMEMETADATA_H
#define NOSQLITE_FRAMEMETADATA_H

#include <cstdint>

namespace nosqlite::memory {
    struct FrameMetadata {
        std::uint32_t page_id{0}; // The disk page ID currently occupying this frame
        std::uint32_t pin_count{0}; // Number of threads concurrently accessing this page
        bool is_dirty{false}; // Has the page been modified since loaded from disk?
    };
}

#endif //NOSQLITE_FRAMEMETADATA_H
