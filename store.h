#ifndef STORE_H
#define STORE_H

#include <string>
#include "library.h"

class Store {
public:
	// Get different information of Book 
	string GetName() { return name; }
	string GetAddress() { return address; }
	string GetBookAddress() { return bookAddress; }
	string GetCashAddress() { return cashAddress; }
	string GetBookLogAddress() { return bookLogAddress; }
	string GetCashLogAddress() { return cashLogAddress; }

	// Change different information of Book 
	void SetName(string new_name) { name = new_name; }
	void SetAddress(string new_address) { address = new_address; }
	void SetBookAddress(string new_book_address) { bookAddress = new_book_address; }
	void SetCashAddress(string new_cash_address) { cashAddress = new_cash_address; }
	void SetBookLogAddress(string new_book_log_address) { bookLogAddress = new_book_log_address; }
	void SetCashLogAddress(string new_cash_log_address) { cashLogAddress = new_cash_log_address; }

private:
	string name;
	string address;
	string bookAddress;
	string cashAddress;
	string bookLogAddress;
	string cashLogAddress;
};

#endif