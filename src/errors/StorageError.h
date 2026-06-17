#ifndef NOSQLITE_STORAGEERROR_H
#define NOSQLITE_STORAGEERROR_H

#include <cstdint>

namespace nosqlite {

enum class StorageError : std::uint8_t {
    PageNotFound,
    DiskReadFailure,
    DiskWriteFailure,
    FileCorrupted,
    PermissionDenied,
};

}

#endif  // NOSQLITE_STORAGEERROR_H
