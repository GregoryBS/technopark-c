 #include <gtest/gtest.h>

extern "C" {
#include "io.h"
#include "func.h"
}

TEST(alloc, err__pointer)
{
    int rc = alloc_mem(NULL, 5);
    ASSERT_EQ(rc, ERR_PARAM);
}

TEST(alloc, err_count)
{
    sport_result *r = NULL;
    int rc = alloc_mem(&r, -1);
    ASSERT_EQ(rc, ERR_PARAM);
}

TEST(process, err_pointer_1)
{
    int a[BEST_COUNT] = {0};
    int rc = find_best(NULL, 1, a);
    ASSERT_EQ(rc, ERR_PARAM);
}

TEST(process, err_pointer_2)
{
    sport_result r = {1, 2, (char*)"name", 3};
    int rc = find_best(&r, 1, NULL);
    ASSERT_EQ(rc, ERR_PARAM);
}

TEST(process, zero_count)
{
    sport_result r = {1, 2, (char*)"name", 3};
    int a[BEST_COUNT] = {0};
    int rc = find_best(&r, 0, a);
    ASSERT_EQ(rc, OK);
    ASSERT_EQ(a[0], -1);
}

TEST(process, ok)
{
    sport_result r[2] = {{1, 2, (char*)"name", 3}, {2, 3, (char*)"name2", 5}};
    int a[BEST_COUNT] = {0};
    int rc = find_best(r, 2, a);
    ASSERT_EQ(rc, OK);
    ASSERT_EQ(a[0], 1);
    ASSERT_EQ(a[1], 0);
}

TEST(read, err_pointer_1)
{
    sport_result *r = NULL;
    int rc = read_results(&r, NULL);
    ASSERT_EQ(rc, ERR_PARAM);
}

TEST(read, err_pointer_2)
{
    int n = 0;
    int rc = read_results(NULL, &n);
    ASSERT_EQ(rc, ERR_PARAM);
}

TEST(read, err_read_1)
{
    sport_result *r = NULL;
    int n = 0;
    freopen("../in_1.txt", "r", stdin);
    int rc = read_results(&r, &n);
    ASSERT_EQ(rc, ERR_IO);
}

TEST(read, err_read_2)
{
    sport_result *r = NULL;
    int n = 0;
    freopen("../in_2.txt", "r", stdin);
    int rc = read_results(&r, &n);
    ASSERT_EQ(rc, ERR_IO);
}

TEST(read, err_read_3)
{
    sport_result *r = NULL;
    int n = 0;
    freopen("../in_3.txt", "r", stdin);
    int rc = read_results(&r, &n);
    ASSERT_EQ(rc, ERR_IO);
}

TEST(read, ok)
{
    sport_result *r = NULL;
    int n = 0;
    freopen("in_3.txt", "r", stdin);
    int rc = read_results(&r, &n);
    ASSERT_EQ(rc, OK);
    ASSERT_EQ(n, 1);
}

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}