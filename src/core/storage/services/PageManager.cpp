#include "../interfaces/PageManager.h"

#include "errors/StorageError.h"

namespace nosqlite::storage {
    std::expected<void, StorageError> PageManager::read_page(std::uint32_t page_id, Page &out_page) {
        return {};
    }

    std::expected<void, StorageError> PageManager::write_page(std::uint32_t page_id, const Page &in_page) {
        return {};
    }
}
