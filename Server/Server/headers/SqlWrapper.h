#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include <string>
#include <vector>


struct Message
{
    //size_t id;
    size_t user_id;
    std::string text;
    std::string date;
    bool operator==(const Message& other) const;
};

class SqlWrapper
{
    std::string path_to_db;
    SQLite::Database db;
public:
    SqlWrapper(std::string path_to_db);
    ~SqlWrapper() = default;

    size_t getLastIdMessages();
    //Message getOneMessage(size_t id);
    std::vector<Message> getNewMessages(size_t last_id);
    //std::vector<Message> getMessages(size_t from_id, size_t to_id);

    int insertMessage(Message& message);

    //bool validUser(std::string name, std::string password);
};
