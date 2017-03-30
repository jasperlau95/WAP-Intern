#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "book.h"
#include "user.h"


class Library {
public:
	int findUser(string name); // find user with name and return its position, -1 means not found
	void LoadUser(); // Load User.txt
	int findBook(string isbn); // check if the book with the given ISBN exist
	void LoadBook(); // Load Book.txt
	void LoadCash(); // Load Cash.txt
	void SetIncome(double new_income) { income = new_income; };	// Change income
	void SetOutcome(double new_outcome) { outcome = new_outcome; }; // Change outcome
	double GetIncome() { return income; };
	double GetOutcome() { return outcome; };
	vector<Book> BookArray;	// Store all books in vector
	vector<User> UserArray;	// Store all users in vector

private:
	double income; // Total income
	double outcome; // Total outcome
};

#endif