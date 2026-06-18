#ifndef NOSQLITE_BUFFERPOOLMANAGER_H
#define NOSQLITE_BUFFERPOOLMANAGER_H

#include <vector>
#include <unordered_map>
#include <memory>
#include <list>
#include <expected>
#include <cstddef>
#include "../interfaces/IBufferPoolManager.h"
#include "../../storage/interfaces/PageManager.h"
#include "../types/FrameMetadata.h"
#include "../types/BufferError.h"

namespace nosqlite::memory {
    class BufferPoolManager : public IBufferPoolManager {
    public:
        explicit BufferPoolManager(std::size_t pool_size, std::shared_ptr<storage::PageManager> page_manager);

        ~BufferPoolManager() override;

        std::expected<storage::Page &, BufferError> fetch_page(std::uint32_t page_id) override;

        std::expected<void, BufferError> unpin_page(std::uint32_t page_id, bool is_dirty) override;

        std::expected<storage::Page &, BufferError> new_page(std::uint32_t &out_page_id) override;

        std::expected<void, BufferError> flush_page(std::uint32_t page_id) override;

        std::expected<void, BufferError> flush_all_pages() override;

    private:
        // Internal helper to find an available frame slot using the eviction policy (LRU)
        std::expected<std::size_t, BufferError> find_victim_frame();

        // Updates the LRU tracking state when a page is accessed
        void update_lru_history(std::size_t frame_id);

        std::size_t pool_size_;
        std::shared_ptr<storage::PageManager> page_manager_;

        // Fixed internal buffers for the RAM cache
        std::vector<storage::Page> page_pool_;
        std::vector<FrameMetadata> frame_metadata_;

        // Fast mapping lookup: <page_id, frame_index>
        std::unordered_map<std::uint32_t, std::size_t> page_table_;

        // LRU Eviction Tracking: Keeps frame indices with pin_count == 0 ordered by usage
        std::list<std::size_t> lru_list_;
    };
} // namespace nosqlite::memory

#endif // NOSQLITE_BUFFERPOOLMANAGER_H
