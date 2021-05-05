#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "library.hpp"
#include "book.hpp"
#include "user.hpp"

void Lib::add_book()
{
    Book new_book;
    char continue_symbol;
    std::cout << "Enter the identification number of the book: " << std::endl;
    std::cin >> new_book.book_id;
    std::cout << "Enter the title of the book: " << std::endl;
    std::cin.ignore();
    std::getline(std::cin, new_book.book_title);
    std::cout << "Enter the name of the author: " << std::endl;
    std::cin >> new_book.book_author_name;
    std::cout << "Enter the surname of the author: " << std::endl;
    std::cin >> new_book.book_author_surname;

    try
    {
        v_book.push_back(new_book);
    }
    catch (const std::bad_alloc &ba)
    {
        std::cerr << "Bad alloc caught in add_book function!\n"
                  << ba.what() << std::endl;
                  return;
    }

    std::cout << "Book added!" << std::endl;
    std::cout << "Do you want to continue? (y/n) " << std::endl;
    std::cin >> continue_symbol;

    while (!(continue_symbol == 'Y' || continue_symbol == 'y' || continue_symbol == 'N' || continue_symbol == 'n'))
    {
        std::cout << "Invalid entry, please repeat: ";
        std::cin >> continue_symbol;
    }
    if (continue_symbol == 'Y' || continue_symbol == 'y')
    {
        add_book();
    }
}

void Lib::show_book()
{
    auto it = v_book.begin();
    while (it != v_book.end())
    {
        std::cout << "==============================" << std::endl;
        std::cout << "Book ID: " << it->book_id << std::endl;
        std::cout << "Book title: " << it->book_title << std::endl;
        std::cout << "Author name: " << it->book_author_name << std::endl;
        std::cout << "Author surname: " << it->book_author_surname << std::endl;
        if (!it->is_borrow)
        {
            std::cout << "Book is available." << std::endl;
        }
        else
        {
            std::cout << "This book has been issued." << std::endl;
        }
        std::cout << "==============================\n"
                  << std::endl;
        it++;
    }
}

void Lib::save_book()
{
    std::fstream lib("lib.txt", std::fstream::out);

    if (!lib.is_open())
    {
        std::cerr << "Error! The file did not open." << std::endl;
    }
    auto it = v_book.begin();
    while (it != v_book.end())
    {
        lib << it->book_id << std::endl;
        lib << it->is_borrow << std::endl;
        lib << it->book_title << std::endl;
        lib << it->book_author_name << std::endl;
        lib << it->book_author_surname << std::endl;
        lib << it->user_id << std::endl;
        lib << it->user_name << std::endl;
        lib << it->user_surname << std::endl;

        it++;
    }
    std::cout << "Book saved!" << std::endl;
    lib.close();
}

void Lib::search_book()
{
    bool is_here = false;
   auto it = v_book.begin();
    std::string book_name;
    std::string tmp_str;
    std::cout << "Enter the title of the book you are looking for." << std::endl;
    std::cin.ignore();
    std::getline(std::cin, book_name);

    std::transform(book_name.begin(), book_name.end(), book_name.begin(), ::tolower);
    while (it != v_book.end())
    {
        tmp_str = it->book_title;
        std::transform(tmp_str.begin(), tmp_str.end(), tmp_str.begin(), ::tolower);
        if (tmp_str == book_name)
        {
            std::cout << "Book ID: " << it->book_id << std::endl;
            std::cout << "Book title: " << it->book_title << std::endl;
            std::cout << "Author name: " << it->book_author_name << std::endl;
            std::cout << "Author surname: " << it->book_author_surname << std::endl;

            if (!it->is_borrow)
            {
                std::cout << "Book is available " << std::endl;
            }
            else
            {
                std::cout << "This book has been issued." << std::endl;
            }
            is_here = true;
        }
        it++;
    }
    if (is_here)
    {
        std::cout << "Book find!" << std::endl;
    }
    else
    {
        std::cout << "This book does not belong to the library." << std::endl;
    }
}

void Lib::read_book()
{
    std::fstream lib("lib.txt", std::fstream::in);
    Book new_book;

    if (!lib.is_open())
    {
        std::cerr << "Error! The file did not open." << std::endl;
        return;
    }
    std::string temp;

    while (true)
    {
        std::getline(lib, temp);
        std::istringstream(temp) >> new_book.book_id;
        std::getline(lib, temp);
        std::istringstream(temp) >> new_book.is_borrow;
        std::getline(lib, new_book.book_title);
        std::getline(lib, new_book.book_author_name);
        std::getline(lib, new_book.book_author_surname);
        std::getline(lib, new_book.user_id);
        std::getline(lib, new_book.user_name);
        std::getline(lib, new_book.user_surname);

        if (!lib)
        {
            break;
        }

        try
        {
            v_book.push_back(new_book);
        }
        catch (const std::bad_alloc &ba)
        {
            std::cerr << "Bad alloc caught in read_book function!\n"
                      << ba.what() << std::endl;
                      return;
        }
    }
    lib.close();
}

void Lib::issued_books()
{
    bool is_issued = false;
    auto it = v_book.begin();
    while (it != v_book.end())
    {
        if (it->is_borrow)
        {
            std::cout << "==============================" << std::endl;
            std::cout << "Users ID: " << it->user_id << std::endl;
            std::cout << "Users name: " << it->user_name << std::endl;
            std::cout << "Users surname: " << it->user_surname << std::endl;
            std::cout << "------------------------------" << std::endl;
            std::cout << "Book title: " << it->book_title << std::endl;
            std::cout << "Name of the author of the book: " << it->book_author_name << std::endl;
            std::cout << "Surame of the author of the book: " << it->book_author_surname << std::endl;
            std::cout << "==============================\n"
                      << std::endl;
            is_issued = true;
        }
        it++;
    }
    if (!is_issued)
    {
        std::cout << "No books issued to users." << std::endl;
    }
}

void Lib::add_user()
{
    char continue_symbol;
    User new_user;

    std::cout << "Enter user number: " << std::endl;
    std::cin >> new_user.user_id;
    std::cout << "Enter user name: " << std::endl;
    std::cin >> new_user.user_name;
    std::cout << "Enter user surname: " << std::endl;
    std::cin >> new_user.user_surname;

    try
    {
        v_user.push_back(new_user);
    }
    catch (const std::bad_alloc &ba)
    {
        std::cerr << "Bad alloc caught in add_user function!\n"
                  << ba.what() << std::endl;
                  return;
    }

    std::cout << "User added!" << std::endl;
    std::cout << "Do you want to continue? (y/n) " << std::endl;
    std::cin >> continue_symbol;

    while (!(continue_symbol == 'Y' || continue_symbol == 'y' || continue_symbol == 'N' || continue_symbol == 'n'))
    {
        std::cout << "Invalid entry, please repeat: ";
        std::cin >> continue_symbol;
    }
    if (continue_symbol == 'Y' || continue_symbol == 'y')
    {
        add_user();
    }
}

void Lib::show_user()
{
    auto it = v_user.begin();

    while (it != v_user.end())
    {
        std::cout << "==============================" << std::endl;
        std::cout << "User ID: " << it->user_id << std::endl;
        std::cout << "User name: " << it->user_name << std::endl;
        std::cout << "User surname: " << it->user_surname << std::endl;
        std::cout << "==============================\n"
                  << std::endl;

        it++;
    }
}

void Lib::save_user()
{
    std::fstream ufile("users.txt", std::fstream::out);

    if (!ufile.is_open())
    {
        std::cerr << "Error! The file did not open." << std::endl;
        return;
    }
    auto it = v_user.begin();
    while (it != v_user.end())
    {
        ufile << it->user_id << std::endl;
        ufile << it->user_name << std::endl;
        ufile << it->user_surname << std::endl;

        it++;
    }
    std::cout << "User saved! " << std::endl;
    ufile.close();
}

void Lib::search_user()
{
    bool is_here = false;
    auto it = v_user.begin();
    std::string user_id;
    std::cout << "Enter the ID number of the user you are looking for: " << std::endl;
    std::cin >> user_id;
    while (it != v_user.end())
    {
        if (it->user_id == user_id)
        {
            std::cout << "User id: " << it->user_id << std::endl;
            std::cout << "User name: " << it->user_name << std::endl;
            std::cout << "User surname: " << it->user_surname << std::endl;

            is_here = true;
        }
        it++;
    }
    if (is_here)
    {
        std::cout << "User find!" << std::endl;
    }
    else
    {
        std::cout << "This user is not registered in the library!" << std::endl;
    }
}

void Lib::read_user()
{
    std::fstream ufile("users.txt", std::fstream::in);
    if (!ufile.is_open())
    {
        std::cerr << "Error! The file did not open." << std::endl;
        return;
    }

    User new_user;
    while (true)
    {
        ufile >> new_user.user_id;
        ufile >> new_user.user_name;
        ufile >> new_user.user_surname;

        if (!ufile)
        {
            break;
        }

        try
        {
            v_user.push_back(new_user);
        }
        catch (const std::bad_alloc &ba)
        {
            std::cerr << "Bad alloc caught in read_user function!\n"
                      << ba.what() << std::endl;
                      return;
        }
    }

    ufile.close();
}

void Lib::book_to_user()
{
    std::string user_id;
    std::string owner_name;
    std::string owner_surname;
    std::string book_title;

    bool is_it_a_user = false;
    bool book_is_here = false;
    bool is_already_borrowed = true;

    std::cout << "Enter the ID number of the user that you want to give the book: " << std::endl;
    std::cin >> user_id;

    auto it = v_user.begin();

    while (it != v_user.end())
    {
        if (it->user_id == user_id)
        {
            owner_name = it->user_name;
            owner_surname = it->user_surname;
            is_it_a_user = true;
            break;
        }
        it++;
    }
    if (!is_it_a_user)
    {
        std::cout << "This user is not served in the library!" << std::endl;
        return;
    }

    std::cout << "Enter the title of the book you want to give to the user: " << std::endl;
    std::cin.ignore();
    std::getline(std::cin, book_title);

    auto it2 = v_book.begin();
    while (it2 != v_book.end())
    {
        if (it2->book_title == book_title)
        {
            std::cout << "Book ID: " << it2->book_id << std::endl;
            std::cout << "Book title: " << it2->book_title << std::endl;
            std::cout << "Name of the author of the book: " << it2->book_author_name << std::endl;
            std::cout << "Surame of the author of the book: " << it2->book_author_surname << std::endl;
            if (!it2->is_borrow)
            {
                std::cout << "This book is available for issuance to the user." << std::endl;
            }
            else
            {
                std::cout << "This book has already been issued." << std::endl;
            }
            book_is_here = true;
        }
        it2++;
    }
    if (!book_is_here)
    {
        std::cout << "This book does not belongs to library." << std::endl;
        return;
    }

    std::cout << "Enter the ID number of the book to be issued to user." << std::endl;
    int book_id;
    std::cin >> book_id;
    it2 = v_book.begin();
    while (it2 != v_book.end())
    {
        if (it2->book_title == book_title && it2->book_id == book_id && !it2->is_borrow)
        {
            it2->user_id = user_id;
            it2->user_name = owner_name;
            it2->user_surname = owner_surname;
            it2->is_borrow = true;

            std::cout << "This book has been issued." << std::endl;
            is_already_borrowed = false;
            break;
        }
        it2++;
    }
    if (is_already_borrowed)
    {
        std::cout << "This book has already been issued." << std::endl;
    }
}

void Lib::return_book()
{
    bool is_obligor = false;
    bool is_book_return = false;
    std::string user_id;
    std::cout << "Enter the ID number of the user from whom you want to return the book: " << std::endl;
    std::cin >> user_id;

    auto it = v_book.begin();

    while (it != v_book.end())
    {
        if (it->user_id == user_id)
        {
            std::cout << "Book ID: " << std::endl;
            std::cout << "Book title: " << it->book_title << std::endl;
            std::cout << "Name of the author of the book: " << it->book_author_name << std::endl;
            std::cout << "Surame of the author of the book: " << it->book_author_surname << std::endl;
            is_obligor = true;
        }

        it++;
    }

    if (!is_obligor)
    {
        std::cout << "You do not have any books. " << std::endl;
    }
    else
    {
        std::cout << "Input book ID to return: " << std::endl;
    }
    int book_id;

    std::cin >> book_id;

    it = v_book.begin();
    while (it != v_book.end())
    {
        if (it->user_id == user_id && it->book_id == book_id)
        {
            it->user_id = "000000";
            it->user_name = " ";
            it->user_surname = " ";
            it->is_borrow = false;
            is_book_return = true;
            std::cout << "Book returned." << std::endl;
            break;
        }
        it++;
    }
    if (!is_book_return)
    {
        std::cout << "Failed!" << std::endl;
    }
}

void Lib::show_users_book()
{

    std::string user_id;
    std::cout << "Enter user ID number: " << std::endl;
    std::cin >> user_id;

    bool is_there_a_book = false;
    auto it = v_book.begin();
    while (it != v_book.end())
    {
        if (it->is_borrow && it->user_id == user_id)
        {
            std::cout << "==============================" << std::endl;
            std::cout << "Users ID: " << it->user_id << std::endl;
            std::cout << "Users name: " << it->user_name << std::endl;
            std::cout << "Users surname: " << it->user_surname << std::endl;
            std::cout << "------------------------------" << std::endl;
            std::cout << "Book title: " << it->book_title << std::endl;
            std::cout << "Name of the author of the book: " << it->book_author_name << std::endl;
            std::cout << "Surame of the author of the book: " << it->book_author_surname << std::endl;
            std::cout << "==============================\n"
                      << std::endl;
            is_there_a_book = true;
        }
        it++;
    }
    if (!is_there_a_book)
    {
        std::cout << "This user has not any books!" << std::endl;
    }
}

void Lib::main_menu()
{
    int choice = 0;
    read_book();
    read_user();
    while (true)
    {

        std::cout << "\t=========================" << std::endl;
        std::cout << "\t1. Books menu" << std::endl;
        std::cout << "\t2. Users menu" << std::endl;
        std::cout << "\t0. Exit" << std::endl;
        std::cout << "\t=========================" << std::endl;
        std::cout << "\tMake your choice: " << std::endl;
        std::cin >> choice;
        while (!(choice >= 0 && choice <= 2))
        {
            std::cout << "Invalid input, try agin. " << std::endl;
            std::cin >> choice;
        }

        switch (choice)
        {
        case 1:
        {
            book_menu();
            break;
        }
        case 2:
        {
            user_menu();
            break;
        }
        case 0:
        {
            return;
        }
        }
    }
}

void Lib::book_menu()
{

    int choice = 0;
    while (true)
    {

        std::cout << "\t=========================" << std::endl;
        std::cout << "\t1. Add a book to the library." << std::endl;
        std::cout << "\t2. Show all books in the library." << std::endl;
        std::cout << "\t3. Search for a book." << std::endl;
        std::cout << "\t4. Issued books." << std::endl;
        std::cout << "\t0. Exit." << std::endl;
        std::cout << "\t=========================" << std::endl;
        std::cout << "\tMake your choice: " << std::endl;
        std::cin >> choice;

        while (!(choice >= 0 && choice <= 4))
        {
            std::cout << "Invalid input, try agin. " << std::endl;
            std::cin >> choice;
        }

        switch (choice)
        {
        case 1:
        {
            add_book();
            break;
        }
        case 2:
        {

            show_book();
            break;
        }
        case 3:
        {

            search_book();
            break;
        }
        case 4:
        {
            issued_books();
            break;
        }
        case 0:
        {
            save_user();
            save_book();
            return;
        }
        }
    }
}

void Lib::user_menu()
{
    int choice = 0;
    while (true)
    {

        std::cout << "\t=========================" << std::endl;
        std::cout << "\t1. Add user to library." << std::endl;
        std::cout << "\t2. Show all users." << std::endl;
        std::cout << "\t3. Search for a user." << std::endl;
        std::cout << "\t4. Issue a book to the user." << std::endl;
        std::cout << "\t5. Show the book issued to the user." << std::endl;
        std::cout << "\t6. Return a book." << std::endl;
        std::cout << "\t0. Exit." << std::endl;
        std::cout << "\t=========================" << std::endl;
        std::cout << "\tMake your choice: " << std::endl;
        std::cin >> choice;

        while (!(choice >= 0 && choice <= 6))
        {
            std::cout << "Invalid input, try agin. " << std::endl;
            std::cin >> choice;
        }

        switch (choice)
        {
        case 1:
        {
            add_user();
            break;
        }
        case 2:
        {

            show_user();
            break;
        }
        case 3:
        {

            search_user();
            break;
        }
        case 4:
        {
            book_to_user();
            break;
        }
        case 5:
        {
            show_users_book();
            break;
        }
        case 6:
        {
            return_book();
            break;
        }
        case 0:
        {
            save_book();
            save_user();
            return;
        }
        }
    }
}