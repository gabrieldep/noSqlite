#ifndef NOSQLITE_BUFFERERROR_H
#define NOSQLITE_BUFFERERROR_H

#include <cstdint>

namespace nosqlite::memory {
    enum class BufferError : std::uint8_t {
        NoAvailableFrames, // All pages are pinned, cannot evict
        PageNotPinned, // Attempted to unpin a page that wasn't locked
        DiskError // Underlying storage manager failed
    };
}

#endif  // NOSQLITE_BUFFERERROR_H
