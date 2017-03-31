#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"
#include "library.h"

class Customer : public User {
public:
	void BuyBook(); // Customer buy books
	void Refund(); // Customer ask for refund
	//void History();					
	void LeaveComment(); // Leave a comment
	void Interface(); // Customer interface
};

#endif