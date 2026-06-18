// IBufferPoolManager.h
#ifndef NOSQLITE_IBUFFERPOOLMANAGER_H
#define NOSQLITE_IBUFFERPOOLMANAGER_H

#include <cstdint>
#include <expected>
#include "../../storage/types/Page.h"
#include "../types/BufferError.h"
#include "core/storage/interfaces/PageManager.h"

namespace nosqlite::memory {

    class IBufferPoolManager {
    public:
        virtual ~IBufferPoolManager() = default;

        /**
         * @brief Fetches a page from the buffer pool.
         * If the page is not in memory, reads it from disk using PageManager.
         * Increments the page's pin count.
         */
        virtual std::expected<storage::Page&, BufferError> fetch_page(std::uint32_t page_id) = 0;

        /**
         * @brief Unpins a page, indicating the caller is done using it.
         * Decrements the pin count. Marks the page as dirty if requested.
         */
        virtual std::expected<void, BufferError> unpin_page(std::uint32_t page_id, bool is_dirty) = 0;

        /**
         * @brief Allocates a brand new page on the database file.
         * Places it into a buffer frame and returns it ready for modification.
         */
        virtual std::expected<storage::Page&, BufferError> new_page(std::uint32_t& out_page_id) = 0;

        /**
         * @brief Forces the buffer pool to write a specific page back to disk if it is dirty.
         */
        virtual std::expected<void, BufferError> flush_page(std::uint32_t page_id) = 0;

        /**
         * @brief Flushes all dirty pages to disk, bringing the database file to a consistent state.
         */
        virtual std::expected<void, BufferError> flush_all_pages() = 0;
    };

} // namespace nosqlite::memory

#endif // NOSQLITE_IBUFFERPOOLMANAGER_H