#include <gtest/gtest.h>

extern "C" {
#include "static.h"
#include "dynamic.h"
}

#define ERR_CMP 1

int cmp_char_array(char **arr1, char **arr2, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(arr1[i], arr2[i]))
            return ERR_CMP;
    }
    return OK;
}

class TestTopfiles : public ::testing::Test
{
protected:
    void SetUp()
    {
        var = new topfiles;
        for (int i = 0; i < 5; i++)
            var->count[i] = 5 - i;
        var->name[0] = (char*) "1.txt";
        var->name[1] = (char*) "2.txt";
        var->name[2] = (char*) "3.txt";
        var->name[3] = (char*) "4.txt";
        var->name[4] = (char*) "5.txt";
    }
    void TearDown()
    {
        delete var;
    }
    topfiles *var;
};

class TestDynArray : public ::testing::Test
{
protected:
    void SetUp()
    {
        filenames = new dyn_array;
        filenames->data = NULL;
        filenames->len = 0;
        filenames->size = 0;
        filenames->step = 10;
        var = new topfiles;
        for (int i = 0; i < TOP_COUNT; i++)
        {
            var->name[i] = 0;
            var->count[i] = 0;
        }
    }
    void TearDown()
    {
        delete filenames;
        delete var;
    }
    topfiles *var;
    dyn_array *filenames;
};

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

TEST_F(TestTopfiles, count_less)
{
    int count[TOP_COUNT] = { 5, 4, 3, 2, 1 };
    char *name[TOP_COUNT] = {(char*)"1.txt", (char*)"2.txt", (char*)"3.txt", \
                             (char*)"4.txt", (char*)"5.txt" };
    int rc = change_result(var, "test.txt", 0);
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(OK, memcmp(var->count, count, TOP_COUNT * sizeof(int)));
    EXPECT_EQ(OK, cmp_char_array(name, var->name, TOP_COUNT));
}

TEST_F(TestTopfiles, count_more)
{
    int count[TOP_COUNT] = { 5, 4, 3, 2, 2 };
    char *name[TOP_COUNT] = {(char*)"1.txt", (char*)"2.txt", (char*)"3.txt", \
                             (char*)"4.txt", (char*)"test.txt"};
    int rc = change_result(var, "test.txt", 2);
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(OK, memcmp(var->count, count, TOP_COUNT * sizeof(int)));
    EXPECT_EQ(OK, cmp_char_array(name, var->name, TOP_COUNT));
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

TEST_F(TestDynArray, err_pointer_1)
{
    EXPECT_EQ(ERR_PARAM, find_topfiles(NULL, filenames, "../tests", "123"));
}

TEST_F(TestDynArray, err_pointer_2)
{
    EXPECT_EQ(ERR_PARAM, find_topfiles(var, NULL, "../tests", "123"));
    EXPECT_EQ(ERR_PARAM, find_topfiles(var, filenames, NULL, "123"));
}

TEST_F(TestDynArray, err_pointer_3)
{
    EXPECT_EQ(ERR_PARAM, find_topfiles(var, filenames, "../tests", NULL));
}

TEST_F(TestDynArray, no_str)
{
    int count[TOP_COUNT] = { 0 };
    EXPECT_EQ(OK, get_filenames_array(filenames, "../tests"));
    int rc = find_topfiles(var, filenames, "../tests", "no_such_str");
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(OK, memcmp(var->count, count, TOP_COUNT * sizeof(int)));
    EXPECT_EQ(OK, free_filenames_array(filenames));
}

TEST_F(TestDynArray, correct_data)
{
    int count[TOP_COUNT] = { 33, 32, 26, 22, 19 };
    char *name[TOP_COUNT] = {(char*)"6.txt", (char*)"5.txt", (char*)"10.txt",\
                             (char*)"15.txt", (char*)"21.txt"};     
    EXPECT_EQ(OK, get_filenames_array(filenames, "../tests"));                  
    int rc = find_topfiles(var, filenames, "../tests", "was");
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(OK, memcmp(var->count, count, TOP_COUNT * sizeof(int)));
    EXPECT_EQ(OK, cmp_char_array(name, var->name, TOP_COUNT));
    EXPECT_EQ(OK, free_filenames_array(filenames));
}

TEST(myround, less)
{
    EXPECT_EQ(0, myround(0.3));
}

TEST(myround, more)
{
    EXPECT_EQ(1, myround(0.5));
}

TEST(get_filenames_array, err_ptr_1)
{
    EXPECT_EQ(ERR_PARAM, get_filenames_array(NULL, "../tests"));
    EXPECT_EQ(ERR_PARAM, free_filenames_array(NULL));
}

TEST_F(TestDynArray, err_ptr_2)
{
    EXPECT_EQ(ERR_PARAM, get_filenames_array(filenames, NULL));
    EXPECT_EQ(OK, free_filenames_array(filenames));
}

TEST_F(TestDynArray, correct_files)
{
    EXPECT_EQ(OK, get_filenames_array(filenames, "../tests"));
    EXPECT_EQ(OK, free_filenames_array(filenames));
}

TEST_F(TestDynArray, err_params)
{
    struct sembuf s = { 0, 1, 0 };
    EXPECT_EQ(ERR_PARAM, run_process(NULL, NULL, NULL, 1, 3, &s, &s, 0));
    EXPECT_EQ(ERR_PARAM, run_process(var, filenames, "str", 1, 3, NULL, \
              NULL, 0));
    EXPECT_EQ(ERR_PARAM, run_process(var, filenames, "str", -1, -1, &s, &s,\
              0));
}

TEST_F(TestDynArray, no_str_cmp)
{
    int count[TOP_COUNT] = { 0 };
    EXPECT_EQ(OK, get_filenames_array(filenames, "../tests"));  
    int rc = find_topfiles(var,  filenames, "../tests", "no_such_str");
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(OK, memcmp(var->count, count, TOP_COUNT * sizeof(int)));
    rc = find_topfiles_p(var, filenames, "../tests", "no_such_str");
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(OK, memcmp(var->count, count, TOP_COUNT * sizeof(int)));
    EXPECT_EQ(OK, free_filenames_array(filenames));
}

TEST_F(TestDynArray, correct_data_cmp)
{
    int count[TOP_COUNT] = { 33, 32, 26, 22, 19 };
    char *name[TOP_COUNT] = {(char*)"6.txt", (char*)"5.txt", (char*)"10.txt",\
                             (char*)"15.txt", (char*)"21.txt"};     
    EXPECT_EQ(OK, get_filenames_array(filenames, "../tests"));                    
    int rc = find_topfiles(var, filenames, "../tests", "was");
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(OK, memcmp(var->count, count, TOP_COUNT * sizeof(int)));
    EXPECT_EQ(OK, cmp_char_array(name, var->name, TOP_COUNT));
    rc = find_topfiles_p(var, filenames, "../tests", "was");
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(OK, memcmp(var->count, count, TOP_COUNT * sizeof(int)));
    EXPECT_EQ(OK, cmp_char_array(name, var->name, TOP_COUNT));
    EXPECT_EQ(OK, free_filenames_array(filenames));
}

int main(int argc, char **argv) 
{
    setbuf(stdout, NULL);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}