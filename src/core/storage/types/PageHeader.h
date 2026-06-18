#ifndef NOSQLITE_PAGEHEADER_H
#define NOSQLITE_PAGEHEADER_H


#include <cstdint>

#pragma pack(push, 1)

struct PageHeader {
    uint8_t page_type; // 1 byte  | Page type (1 = data, 2 = index, 3 = free)
    uint8_t flags; // 1 byte  | State flags (e.g., bit 0 = dirty, bit 1 = compressed)
    uint16_t collection_id; // 2 bytes | Numeric ID of the collection this page belongs to
    uint32_t next_page_id; // 4 bytes | Pointer to the next page (useful for linked lists)
    uint16_t slot_count; // 2 bytes | Number of active records/slots on this page
    uint16_t free_space_end; // 2 bytes | Offset where free space ends (where the last document was inserted)
};

#pragma pack(pop)

#endif //NOSQLITE_PAGEHEADER_H
