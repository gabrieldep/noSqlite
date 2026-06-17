#ifndef NOSQLITE_PAGE_H
#define NOSQLITE_PAGE_H

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

struct PageHeader;

namespace nosqlite {
    inline constexpr std::size_t PAGE_SIZE = 4096;

    struct Page {
        std::array<std::uint8_t, PAGE_SIZE> bytes{};

        template <typename Self>
        auto* get_header(this Self&& self) {
            using HeaderPtr = std::conditional_t<
                std::is_const_v<std::remove_reference_t<Self>>,
                const PageHeader*,
                PageHeader*
            >;

            return reinterpret_cast<HeaderPtr>(self.bytes.data());
        }
    };
}

#endif  // NOSQLITE_PAGE_H