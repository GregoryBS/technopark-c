#include <gtest/gtest.h>

extern "C" {
#include "letter_io.h"
#include "spam.h"
}

class TestLetter : public ::testing::Test
{
protected:
    void SetUp()
    {
        char s[] = "sender", r[] = "receiver", t1[] = "theme", t2[] = "text";
        ltr = new letter;
        ltr->sender = s;
        ltr->receiver = r;
        ltr->theme = t1;
        ltr->text = t2;
        flag = false;
    }
    void TearDown()
    {
        delete ltr;
    }

    letter *ltr;
    bool flag;
};

TEST(is_spam, err_letter)
{
    letter ltr = { NULL, NULL, NULL, NULL };
    bool flag = false;
    int rc = is_spam(&ltr, &flag);
    EXPECT_EQ(rc, ERR_PARAM);
}

TEST_F(TestLetter, err_flag)
{ 
    int rc = is_spam(ltr, NULL);
    EXPECT_EQ(rc, ERR_PARAM);
}

TEST_F(TestLetter, no_spam)
{
    int rc = is_spam(ltr, &flag);
    EXPECT_EQ(rc, OK);
    EXPECT_EQ(flag, false);
}

TEST_F(TestLetter, spam)
{
    ltr->text = (char*) SPAM;
    int rc = is_spam(ltr, &flag);
    EXPECT_EQ(rc, OK);
    EXPECT_EQ(flag, true);
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
    free_mem(&ltr);
}

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
