#ifndef NOSQLITE_PAGE_HEADER_H
#define NOSQLITE_PAGE_HEADER_H

#include <stdint.h>

#pragma pack(push, 1)

typedef struct PageHeader {
    uint8_t page_type;
    uint8_t flags;
    uint16_t collection_id;
    uint32_t next_page_id;
    uint16_t slot_count;
    uint16_t free_space_end;
} PageHeader;

#pragma pack(pop)

#endif /* NOSQLITE_PAGE_HEADER_H */
