#ifndef NOSQLITE_PAGE_H
#define NOSQLITE_PAGE_H

#include <stdint.h>

#include "page_header.h"

#define NOSQLITE_PAGE_SIZE 4096

typedef struct Page {
    uint8_t bytes[NOSQLITE_PAGE_SIZE];
} Page;

static inline PageHeader *page_get_header(Page *page) {
    return (PageHeader *)page->bytes;
}

static inline const PageHeader *page_get_header_const(const Page *page) {
    return (const PageHeader *)page->bytes;
}

#endif /* NOSQLITE_PAGE_H */
