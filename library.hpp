#pragma once
#include <vector>
#include <string>
#include "book.hpp"
#include "user.hpp"

class Lib
{
private:
	std::vector<Book> v_book;
	std::vector<User> v_user;

public:
	void add_book();
	void show_book();
	void save_book();
	void search_book();
	void read_book();
	void issued_books();
	void book_menu();

	void add_user();
	void show_user();
	void save_user();
	void search_user();
	void read_user();
	void book_to_user();
	void return_book();
	void show_users_book();
	void user_menu();

	void main_menu();
};
