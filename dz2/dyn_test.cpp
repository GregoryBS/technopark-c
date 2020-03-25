#include <gtest/gtest.h>

extern "C" {
#include "lib.h"
#include "dynamic.h"
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

TEST(myround, lower)
{
    EXPECT_EQ(0, myround(0.3));
}

TEST(myround, upper)
{
    EXPECT_EQ(1, myround(0.5));
}

TEST(get_filenames_array, err_pointer_1)
{
    DIR *dp = opendir("../tests");
    EXPECT_EQ(ERR_PARAM, get_filenames_array(NULL, dp));
    closedir(dp);
}

TEST(get_filenames_array, err_pointer_2)
{
    dyn_array filenames = { NULL, 0, 0, 10 };
    EXPECT_EQ(ERR_PARAM, get_filenames_array(&filenames, NULL));
}

TEST(get_filenames_array, ok)
{
    dyn_array filenames = { NULL, 0, 0, 10 };
    DIR *dp = opendir("../tests");
    EXPECT_EQ(OK, get_filenames_array(&filenames, dp));
    closedir(dp);
    free(filenames.data);
}

TEST(run_process, err_params)
{
    struct sembuf s = { 0, 1, 0 };
    EXPECT_EQ(ERR_PARAM, run_process(NULL, NULL, NULL, 1, 3, &s, &s, 0));
    topfiles var = { { 0 }, { 0 } };
    dyn_array filenames = { NULL, 0, 0, 10 };
    EXPECT_EQ(ERR_PARAM, run_process(&var, &filenames, "str", 1, 3, NULL, \
              NULL, 0));
    EXPECT_EQ(ERR_PARAM, run_process(&var, &filenames, "str", -1, -1, &s, &s,\
              0));
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
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}