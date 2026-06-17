#ifndef NOSQLITE_IPAGEMANAGER_H
#define NOSQLITE_IPAGEMANAGER_H

#include <cstdint>
#include <expected>

namespace nosqlite::storage {
    struct Page;
    enum class StorageError : std::uint8_t;

    class PageManager {
    public:
        virtual ~PageManager() = default;

        virtual std::expected<void, StorageError> read_page(std::uint32_t page_id, Page &out_page) = 0;

        virtual std::expected<void, StorageError> write_page(std::uint32_t page_id, const Page &in_page) = 0;
    };
}

#endif  // NOSQLITE_IPAGEMANAGER_H
