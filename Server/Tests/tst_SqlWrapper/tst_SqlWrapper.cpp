#include <gtest/gtest.h>
#include "SqlWrapper.h"

TEST(HelloTest, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}


TEST(SqlWrapper, getLastIdMessages)
{
    std::string s = "C:\\develop\\C++ CLion\\chat\\Server\\Tests\\tst_SqlWrapper\\db_old.db";
    SqlWrapper sw(s);
    EXPECT_EQ(sw.getLastIdMessages(), 3);
}

TEST(SqlWrapper, getNewMessages)
{
    std::string s = "C:\\develop\\C++ CLion\\chat\\Server\\Tests\\tst_SqlWrapper\\db_old.db";
    SqlWrapper sw(s);

    std::vector<Message> result;

    result = {
            Message{8,"HELLO","31-03-2008"},
            Message{2,"fimopfop","2323213"},
            Message{55,"YOOO","333-333-333"}
    };

    std::vector<Message> newMessage = sw.getNewMessages(0);

    EXPECT_EQ(newMessage, result);
}

TEST(SqlWrapper, insertMessage)
{
    std::string s = "C:\\develop\\C++ CLion\\chat\\Server\\Tests\\tst_SqlWrapper\\db.db";
    SqlWrapper sw(s);

    Message message = Message {55,"BYEEEE","31-88-2008"};

    sw.insertMessage(message);

    EXPECT_EQ(1, 1);
}