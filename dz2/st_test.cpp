#include <gtest/gtest.h>

extern "C" {
#include "lib.h"
}

#define ERR_CMP 1

int cmp_int_array(int arr1[TOP_COUNT], int arr2[TOP_COUNT])
{
    for (int i = 0; i < TOP_COUNT; i++)
    {
        if (arr1[i] != arr2[i])
            return ERR_CMP;
    }
    return OK;
}

int cmp_char_array(char **arr1, char **arr2, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(arr1[i], arr2[i]))
            return ERR_CMP;
    }
    return OK;
}

TEST(write_results, err_pointer)
{
    EXPECT_EQ(ERR_PARAM, write_results(NULL));
}

TEST(change_result, err_pointer_1)
{
    EXPECT_EQ(ERR_PARAM, change_result(NULL, "file.txt", 1));
}

TEST(change_result, err_pointer_2)
{
    topfiles var = { { 0 }, { 0 } };
    EXPECT_EQ(ERR_PARAM, change_result(&var, NULL, 1));
}

TEST(change_result, count_less)
{
    topfiles var = { { 5, 4, 3, 2, 1}, {(char*)"1.txt", (char*)"2.txt", \
                    (char*)"3.txt", (char*)"4.txt", (char*)"5.txt" } };
    int count[TOP_COUNT] = { 5, 4, 3, 2, 1 };
    char *name[TOP_COUNT] = {(char*)"1.txt", (char*)"2.txt", (char*)"3.txt", \
                             (char*)"4.txt", (char*)"5.txt" };
    int rc = change_result(&var, "test.txt", 0);
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(OK, cmp_int_array(var.count, count));
    EXPECT_EQ(OK, cmp_char_array(name, var.name, TOP_COUNT));
}

TEST(change_result, count_more)
{
    topfiles var = { { 5, 4, 3, 1, 1}, {(char*)"1.txt", (char*)"2.txt", \
                    (char*)"3.txt", (char*)"4.txt", (char*)"5.txt" } };
    int count[TOP_COUNT] = { 5, 4, 3, 2, 1 };
    char *name[TOP_COUNT] = {(char*)"1.txt", (char*)"2.txt", (char*)"3.txt", \
                             (char*)"6.txt", (char*)"4.txt"};
    int rc = change_result(&var, "6.txt", 2);
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(OK, cmp_int_array(var.count, count));
    EXPECT_EQ(OK, cmp_char_array(name, var.name, TOP_COUNT));
}

TEST(get_str_count, err_pointer_1)
{
    int count = 0;
    EXPECT_EQ(ERR_PARAM, get_str_count(NULL, "str", &count));
}

TEST(get_str_count, err_pointer_2)
{
    int count = 0;
    EXPECT_EQ(ERR_PARAM, get_str_count("1.txt", NULL, &count));
}

TEST(get_str_count, err_pointer_3)
{
    EXPECT_EQ(ERR_PARAM, get_str_count("1.txt", "str", NULL));
}

TEST(get_str_count, ok)
{
    int count = 0;
    int rc = get_str_count("../tests/6.txt", "was", &count);
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(33, count);
}

TEST(find_topfiles, err_pointer_1)
{
    EXPECT_EQ(ERR_PARAM, find_topfiles(NULL, "../tests", "123"));
}

TEST(find_topfiles, err_pointer_2)
{
    topfiles var = { { 0 }, { 0 } };
    EXPECT_EQ(ERR_PARAM, find_topfiles(&var, NULL, "123"));
}

TEST(find_topfiles, err_pointer_3)
{
    topfiles var = { { 0 }, { 0 } };
    EXPECT_EQ(ERR_PARAM, find_topfiles(&var, "../tests", NULL));
}

TEST(find_topfiles, no_str)
{
    topfiles var = { { 0 }, { 0 } };
    int count[TOP_COUNT] = { 0 };
    int rc = find_topfiles(&var, "../tests", "no_such_str");
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(OK, cmp_int_array(var.count, count));
}

TEST(find_topfiles, ok)
{
    topfiles var = { { 0 }, { 0 } };
    int count[TOP_COUNT] = { 33, 32, 26, 22, 19 };
    char *name[TOP_COUNT] = {(char*)"6.txt", (char*)"5.txt", (char*)"10.txt",\
                             (char*)"15.txt", (char*)"21.txt"};                       
    int rc = find_topfiles(&var, "../tests", "was");
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(OK, cmp_int_array(var.count, count));
    EXPECT_EQ(OK, cmp_char_array(name, var.name, TOP_COUNT));
}

int main(int argc, char **argv) 
{
    setbuf(stdout, NULL);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}