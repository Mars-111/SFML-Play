#include "SqlWrapper.h"
#include <iostream>

SqlWrapper::SqlWrapper(std::string path_to_db) :
    path_to_db(std::move(path_to_db)),
    db(SQLite::Database(this->path_to_db, SQLite::OPEN_READWRITE))
{
    std::cout << "SQLite database file '" << db.getFilename().c_str() << "' opened successfully\n";
}


size_t SqlWrapper::getLastIdMessages()
{
    SQLite::Statement query(db,"SELECT MAX(`id`) FROM `chat_data`");
    query.executeStep();
    return query.getColumn(0).getInt64();
}

std::vector<Message> SqlWrapper::getNewMessages(size_t last_id)
{
    std::vector<Message> result;

    SQLite::Statement query(db,"SELECT `user_id`, `text`, `date` FROM `chat_data`");

    for (size_t i = 0; i < last_id; i++) {
        query.executeStep();
    }

    result.reserve(getLastIdMessages()-last_id);

    while (query.executeStep())
    {
        result.emplace_back(Message{
            static_cast<size_t>(query.getColumn(0).getInt64()),
            query.getColumn(1).getString(),
            query.getColumn(2).getString()
        });
    }

    return result;
}

int SqlWrapper::insertMessage(Message& message)
{
    SQLite::Statement query(db,
    "INSERT INTO `chat_data` (user_id, text, date) VALUES "
            "(" + std::to_string(message.user_id) + ", '" + message.text + "', '" + message.date + "');");
    return query.exec();
}




bool Message::operator==(const Message &other) const {
    if (user_id == other.user_id && text == other.text && date == other.date) {
        return true;
    }
    return false;
}
