#include <gtest/gtest.h>
#include <dlfcn.h>
#include <time.h>
#include <cstring>

extern "C" {
#include "file.h"
#include "sequential.h"
}

TEST(diff_counts_print, err_pointer)
{
    EXPECT_NO_FATAL_FAILURE(diff_counts_print(NULL, 0));
}

TEST(file_close, bad_file)
{
    EXPECT_EQ(ERR_MEM, file_close(NULL, 0, 0));
}

TEST(file_open, err_params)
{
    EXPECT_EQ(ERR_PARAM, file_open(NULL, NULL, NULL, NULL));
}

TEST(file_open, bad_filename)
{
    char *filemem = NULL, *filename = (char*) "";
    int filesize = 0, fd = 0;
    EXPECT_EQ(ERR_IO, file_open(filename, &filemem, &filesize, &fd));
}

TEST(file_open, good_filename)
{
    char *filemem = NULL, *filename = (char*) "../test.txt";
    int filesize = 0, fd = 0;
    EXPECT_EQ(OK, file_open(filename, &filemem, &filesize, &fd));
    file_close(filemem, filesize, fd);
}

TEST(byte_diff_count, err_params)
{
    char mem = 0;
    int count = 0;
    EXPECT_EQ(ERR_PARAM, byte_diff_count(NULL, 1, &mem, 1));
    EXPECT_EQ(ERR_PARAM, byte_diff_count(&count, 0, &mem, 1));
    EXPECT_EQ(ERR_PARAM, byte_diff_count(&count, 1, NULL, 1));
    EXPECT_EQ(ERR_PARAM, byte_diff_count(&count, 1, &mem, 0));
}

TEST(byte_diff_count, good_params)
{
    char *mem1 = (char*) "aa", *mem2 = (char*) "ab";
    int count = 0;
    int rc = byte_diff_count(&count, 1, mem1, 1);
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(0, count);
    rc = byte_diff_count(&count, 1, mem1, 2);
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(1, count);
    rc = byte_diff_count(&count, 1, mem2, 2);
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(0, count);
}

class TestLibrary : public ::testing::Test
{
protected:
    void SetUp()
    {
        library = dlopen("libparallel.so", RTLD_LAZY);
        if (library)
        {
            func = (int (*)(int*, int, const char*, int)) dlsym(library, \
                                                        "byte_diff_count");
        }
    }
    void TearDown()
    {
        dlclose(library);
    }

    void *library = NULL;
    int (*func)(int*, int, const char*, int) = NULL;
};

TEST_F(TestLibrary, err_params)
{
    char mem = 0;
    int count = 0;
    EXPECT_EQ(ERR_PARAM, func(NULL, 1, &mem, 1));
    EXPECT_EQ(ERR_PARAM, func(&count, 0, &mem, 1));
    EXPECT_EQ(ERR_PARAM, func(&count, 1, NULL, 1));
    EXPECT_EQ(ERR_PARAM, func(&count, 1, &mem, 0));
}

TEST_F(TestLibrary, good_params)
{
    char *mem1 = (char*) "aa", *mem2 = (char*) "ab";
    int count = 0;
    int rc = byte_diff_count(&count, 1, mem1, 1);
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(0, count);
    rc = byte_diff_count(&count, 1, mem1, 2);
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(1, count);
    rc = byte_diff_count(&count, 1, mem2, 2);
    EXPECT_EQ(OK, rc);
    EXPECT_EQ(0, count);
}

TEST_F(TestLibrary, stress_test)
{
    char *filename = (char*) "../test.pdf", *filemem = NULL;
    int filesize = 0, fd = 0;
    int rc = file_open(filename, &filemem, &filesize, &fd);
    ASSERT_EQ(OK, rc);
    int *res_seq = (int*) calloc(N + 1, sizeof(int));
    int *res_par = (int*) calloc(N + 1, sizeof(int));
    ASSERT_EQ(NULL, !res_seq);
    ASSERT_EQ(NULL, !res_par);
    float time_seq_s = 0, time_par_s = 0;
    struct timespec t1 = { 0 }, t2 = { 0 };
    for (int i = 0; i < N; i++)
    {
        clock_gettime(CLOCK_REALTIME, &t1);
        rc = byte_diff_count(res_seq, N + 1, filemem, filesize);
        clock_gettime(CLOCK_REALTIME, &t2);
        time_seq_s += (t2.tv_sec - t1.tv_sec + 
                      (t2.tv_nsec - t1.tv_nsec) / 1e9);

        clock_gettime(CLOCK_REALTIME, &t1);
        rc = func(res_par, N + 1, filemem, filesize);
        clock_gettime(CLOCK_REALTIME, &t2);
        time_par_s += (t2.tv_sec - t1.tv_sec + 
                      (t2.tv_nsec - t1.tv_nsec) / 1e9);
        
        EXPECT_EQ(OK, memcmp(res_seq, res_par, (N + 1) *sizeof(int)));
    }
    printf("Time of seq-perform: %f\nTime of par-performing: %f\n",
            time_seq_s / N, time_par_s / N);
    free(res_seq);
    free(res_par);
    file_close(filemem, filesize, fd);
}

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
