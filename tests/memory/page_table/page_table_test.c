#include <criterion/criterion.h>
#include <stdlib.h>

#include "../../../src/core/memory/page_table/page_table.h"

static void setup_page_table(size_t pool_size, HashNode ***out_buckets, HashNode **out_node_pool)
{
    *out_buckets = calloc(pool_size, sizeof(HashNode *));
    *out_node_pool = calloc(pool_size, sizeof(HashNode));
}

static void teardown_page_table(HashNode **buckets, HashNode *node_pool)
{
    free(buckets);
    free(node_pool);
}

Test(page_table, lookup_empty)
{
    const size_t pool_size = 4;
    HashNode **buckets = NULL;
    HashNode *node_pool = NULL;
    setup_page_table(pool_size, &buckets, &node_pool);

    size_t frame_id = 99;
    bool found = page_table_lookup(buckets, pool_size, 42, &frame_id);

    cr_assert_eq(found, false);
    cr_assert_eq(frame_id, 99);

    teardown_page_table(buckets, node_pool);
}

Test(page_table, insert_and_lookup)
{
    const size_t pool_size = 4;
    HashNode **buckets = NULL;
    HashNode *node_pool = NULL;
    setup_page_table(pool_size, &buckets, &node_pool);

    page_table_insert(buckets, node_pool, pool_size, 42, 1);

    size_t frame_id = 0;
    bool found = page_table_lookup(buckets, pool_size, 42, &frame_id);

    cr_assert_eq(found, true);
    cr_assert_eq(frame_id, 1);

    teardown_page_table(buckets, node_pool);
}

Test(page_table, insert_multiple)
{
    const size_t pool_size = 8;
    HashNode **buckets = NULL;
    HashNode *node_pool = NULL;
    setup_page_table(pool_size, &buckets, &node_pool);

    page_table_insert(buckets, node_pool, pool_size, 1, 0);
    page_table_insert(buckets, node_pool, pool_size, 7, 1);
    page_table_insert(buckets, node_pool, pool_size, 13, 2);

    size_t frame_id = 0;

    cr_assert_eq(page_table_lookup(buckets, pool_size, 1, &frame_id), true);
    cr_assert_eq(frame_id, 0);

    cr_assert_eq(page_table_lookup(buckets, pool_size, 7, &frame_id), true);
    cr_assert_eq(frame_id, 1);

    cr_assert_eq(page_table_lookup(buckets, pool_size, 13, &frame_id), true);
    cr_assert_eq(frame_id, 2);

    teardown_page_table(buckets, node_pool);
}

Test(page_table, lookup_missing)
{
    const size_t pool_size = 4;
    HashNode **buckets = NULL;
    HashNode *node_pool = NULL;
    setup_page_table(pool_size, &buckets, &node_pool);

    page_table_insert(buckets, node_pool, pool_size, 42, 0);

    size_t frame_id = 0;
    bool found = page_table_lookup(buckets, pool_size, 99, &frame_id);

    cr_assert_eq(found, false);

    teardown_page_table(buckets, node_pool);
}

Test(page_table, remove_existing)
{
    const size_t pool_size = 4;
    HashNode **buckets = NULL;
    HashNode *node_pool = NULL;
    setup_page_table(pool_size, &buckets, &node_pool);

    page_table_insert(buckets, node_pool, pool_size, 42, 0);

    bool removed = page_table_remove(buckets, pool_size, 42);
    cr_assert_eq(removed, true);
    cr_assert_eq(page_table_lookup(buckets, pool_size, 42, NULL), false);

    teardown_page_table(buckets, node_pool);
}

Test(page_table, remove_missing)
{
    const size_t pool_size = 4;
    HashNode **buckets = NULL;
    HashNode *node_pool = NULL;
    setup_page_table(pool_size, &buckets, &node_pool);

    page_table_insert(buckets, node_pool, pool_size, 42, 0);

    bool removed = page_table_remove(buckets, pool_size, 99);
    cr_assert_eq(removed, false);
    cr_assert_eq(page_table_lookup(buckets, pool_size, 42, NULL), true);

    teardown_page_table(buckets, node_pool);
}

Test(page_table, hash_collision)
{
    const size_t pool_size = 4;
    HashNode **buckets = NULL;
    HashNode *node_pool = NULL;
    setup_page_table(pool_size, &buckets, &node_pool);

    page_table_insert(buckets, node_pool, pool_size, 0, 0);
    page_table_insert(buckets, node_pool, pool_size, 4, 1);
    page_table_insert(buckets, node_pool, pool_size, 8, 2);

    size_t frame_id = 0;

    cr_assert_eq(page_table_lookup(buckets, pool_size, 0, &frame_id), true);
    cr_assert_eq(frame_id, 0);

    cr_assert_eq(page_table_lookup(buckets, pool_size, 4, &frame_id), true);
    cr_assert_eq(frame_id, 1);

    cr_assert_eq(page_table_lookup(buckets, pool_size, 8, &frame_id), true);
    cr_assert_eq(frame_id, 2);

    teardown_page_table(buckets, node_pool);
}

Test(page_table, remove_collision_head)
{
    const size_t pool_size = 4;
    HashNode **buckets = NULL;
    HashNode *node_pool = NULL;
    setup_page_table(pool_size, &buckets, &node_pool);

    page_table_insert(buckets, node_pool, pool_size, 0, 0);
    page_table_insert(buckets, node_pool, pool_size, 4, 1);

    bool removed = page_table_remove(buckets, pool_size, 4);
    cr_assert_eq(removed, true);
    cr_assert_eq(page_table_lookup(buckets, pool_size, 4, NULL), false);
    cr_assert_eq(page_table_lookup(buckets, pool_size, 0, NULL), true);

    teardown_page_table(buckets, node_pool);
}

Test(page_table, remove_collision_middle)
{
    const size_t pool_size = 4;
    HashNode **buckets = NULL;
    HashNode *node_pool = NULL;
    setup_page_table(pool_size, &buckets, &node_pool);

    page_table_insert(buckets, node_pool, pool_size, 0, 0);
    page_table_insert(buckets, node_pool, pool_size, 4, 1);
    page_table_insert(buckets, node_pool, pool_size, 8, 2);

    bool removed = page_table_remove(buckets, pool_size, 4);
    cr_assert_eq(removed, true);
    cr_assert_eq(page_table_lookup(buckets, pool_size, 4, NULL), false);
    cr_assert_eq(page_table_lookup(buckets, pool_size, 0, NULL), true);
    cr_assert_eq(page_table_lookup(buckets, pool_size, 8, NULL), true);

    teardown_page_table(buckets, node_pool);
}
