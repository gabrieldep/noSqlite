#ifndef NOSQLITE_PAGE_MANAGER_H
#define NOSQLITE_PAGE_MANAGER_H

#include <stdint.h>

#include "page.h"

typedef struct PageManager PageManager;

PageManager *page_manager_create(void);
void page_manager_destroy(PageManager *pm);

int page_manager_read(PageManager *pm, uint32_t page_id, Page *out_page);
int page_manager_write(PageManager *pm, uint32_t page_id, const Page *in_page);

#endif /* NOSQLITE_PAGE_MANAGER_H */
