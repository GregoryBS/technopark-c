 #include <gtest/gtest.h>

extern "C" {
#include "sport_result_io.h"
#include "func.h"
}

TEST(process, err_pointer_1)
{
    int a[BEST_COUNT] = {0};
    int rc = find_best(NULL, 1, a);
    EXPECT_EQ(rc, ERR_PARAM);
}

TEST(process, err_pointer_2)
{
    sport_result r = {1, 2, (char*)"name", 3};
    int rc = find_best(&r, 1, NULL);
    EXPECT_EQ(rc, ERR_PARAM);
}

TEST(process, zero_count)
{
    sport_result r = {1, 2, (char*)"name", 3};
    int a[BEST_COUNT] = {0};
    int rc = find_best(&r, 0, a);
    EXPECT_EQ(rc, OK);
    EXPECT_EQ(a[0], -1);
}

TEST(process, ok)
{
    sport_result r[2] = {{1, 2, (char*)"name", 3}, {2, 3, (char*)"name2", 5}};
    int a[BEST_COUNT] = {0};
    int rc = find_best(r, 2, a);
    EXPECT_EQ(rc, OK);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 0);
}

TEST(read, err_pointer_1)
{
    sport_result *r = NULL;
    int rc = read_results(&r, NULL);
    EXPECT_EQ(rc, ERR_PARAM);
}

TEST(read, err_pointer_2)
{
    int n = 0;
    int rc = read_results(NULL, &n);
    EXPECT_EQ(rc, ERR_PARAM);
}

TEST(read, err_read_1)
{
    sport_result *r = NULL;
    int n = 0;
    freopen("../in_1.txt", "r", stdin);
    int rc = read_results(&r, &n);
    EXPECT_EQ(rc, ERR_IO);
}

TEST(read, err_read_2)
{
    sport_result *r = NULL;
    int n = 0;
    freopen("../in_2.txt", "r", stdin);
    int rc = read_results(&r, &n);
    EXPECT_EQ(rc, ERR_IO);
}

TEST(read, err_read_3)
{
    sport_result *r = NULL;
    int n = 0;
    freopen("../in_3.txt", "r", stdin);
    int rc = read_results(&r, &n);
    EXPECT_EQ(rc, ERR_IO);
}

TEST(read, ok)
{
    sport_result *r = NULL;
    int n = 0;
    freopen("../in.txt", "r", stdin);
    int rc = read_results(&r, &n);
    EXPECT_EQ(rc, OK);
    EXPECT_EQ(n, 12);
}

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}