#include <gtest/gtest.h>

extern "C" {
#include "letter_io.h"
#include "func.h"
}

TEST(is_spam, err_flag)
{
    char s[] = "sender", r[] = "receiver", t1[] = "theme", t2[] = "text";
    letter ltr = { s, r, t1, t2 };
    int rc = is_spam(ltr, NULL);
    EXPECT_EQ(rc, ERR_PARAM);
}

TEST(is_spam, err_letter)
{
    letter ltr = { NULL, NULL, NULL, NULL };
    int flag = FALSE;
    int rc = is_spam(ltr, &flag);
    EXPECT_EQ(rc, ERR_PARAM);
}

TEST(is_spam, no_spam)
{
    char s[] = "sender", r[] = "receiver", t1[] = "theme", t2[] = "text";
    letter ltr = { s, r, t1, t2 };
    int flag = TRUE;
    int rc = is_spam(ltr, &flag);
    EXPECT_EQ(rc, OK);
    EXPECT_EQ(flag, FALSE);
}

TEST(is_spam, spam)
{
    char s[] = "sender", r[] = "receiver", t1[] = "theme", t2[] = SPAM;
    letter ltr = { s, r, t1, t2 };
    int flag = FALSE;
    int rc = is_spam(ltr, &flag);
    EXPECT_EQ(rc, OK);
    EXPECT_EQ(flag, TRUE);
}

TEST(read_text, err_pointer)
{
    int rc = read_text(NULL, ' ');
    EXPECT_EQ(rc, ERR_PARAM);
}

TEST(read_text, bad_input)
{
    char *text = NULL;
    freopen("../test1.txt", "r", stdin);
    int rc = read_text(&text, ' ');
    EXPECT_EQ(rc, ERR_IO);
}

TEST(read_text, good_input)
{
    char *text = NULL;
    freopen("../test2.txt", "r", stdin);
    int rc = read_text(&text, ' ');
    EXPECT_EQ(rc, OK);
    free(text);
}

TEST(read_letter, err_pointer)
{
    int rc = read_letter(NULL);
    EXPECT_EQ(rc, ERR_PARAM);
}

TEST(read_letter, no_input)
{
    letter ltr = { NULL, NULL, NULL, NULL };
    freopen("../test1.txt", "r", stdin);
    int rc = read_letter(&ltr);
    EXPECT_EQ(rc, ERR_IO);
}

TEST(read_letter, bad_letter_1)
{
    letter ltr = { NULL, NULL, NULL, NULL };
    freopen("../test2.txt", "r", stdin);
    int rc = read_letter(&ltr);
    EXPECT_EQ(rc, ERR_IO);
}

TEST(read_letter, bad_letter_2)
{
    letter ltr = { NULL, NULL, NULL, NULL };
    freopen("../test3.txt", "r", stdin);
    int rc = read_letter(&ltr);
    EXPECT_EQ(rc, ERR_IO);
}

TEST(read_letter, bad_letter_3)
{
    letter ltr = { NULL, NULL, NULL, NULL };
    freopen("../test4.txt", "r", stdin);
    int rc = read_letter(&ltr);
    EXPECT_EQ(rc, ERR_IO);
}

TEST(read_letter, good_letter)
{
    letter ltr = { NULL, NULL, NULL, NULL };
    freopen("../test5.txt", "r", stdin);
    int rc = read_letter(&ltr);
    EXPECT_EQ(rc, OK);
    EXPECT_FALSE(ltr.sender == NULL);
    EXPECT_FALSE(ltr.receiver == NULL);
    EXPECT_FALSE(ltr.theme == NULL);
    EXPECT_FALSE(ltr.text == NULL);
    free_mem(ltr);
}

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}