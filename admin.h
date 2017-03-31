#ifndef ADMIN_H
#define ADMIN_H

#include "staff.h"

class Admin : public Staff {
public:
	void AddUser(); // Add new user
	void AddCustomer(); // For customer self sign up use
	void DelUser();	// Delete old user
	void SetUser();	// Change user's status (like Customer, Staff, Administartor)
	void Interface(); // Admin interface

private:
	void ListUser(); // List all users' information
	void ShowSalesData(); // Show the sales data of each book
};

#endif
