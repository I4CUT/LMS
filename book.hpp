#pragma once
#include <string>

class Book
{
public:
    int book_id = 0;
    bool is_borrow = false;
    std::string book_title;
    std::string book_author_name;
    std::string book_author_surname;
    std::string user_id = "0000000";
    std::string user_name;
    std::string user_surname;
};
