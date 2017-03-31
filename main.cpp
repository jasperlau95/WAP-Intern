#include "log.h"
#include "book.h"
#include "user.h"
#include "staff.h"
#include "admin.h"
#include "library.h"
#include "customer.h"
#include "password.h"
#include "store.h"
#include "storelist.h"
#include "md5.h"

Log rec;
Storelist storelist;
Store store;
Library lib;
Password pwd;
string account;
string book_address;
string cash_address;
string book_log_address;
string cash_log_address;
MD5 md5;
Admin admin;
int user_index;

int storeNum = 0; // number of the store

int Login(string username, string password)	// Get user's status
{
	for (size_t i = 0; i < lib.UserArray.size(); i++ )
		if (username == lib.UserArray[i].GetUsername() && password == lib.UserArray[i].GetPassword()) // If find username and password in User.txt
		{
			user_index = i;
			return lib.UserArray[i].GetStatus(); // Return user's status
		}	
	return 0;
}

void Welcome() // Welcome interface
{
	lib.LoadUser();	// Load User.txt
	storelist.LoadStoreList();
	int status = 0, time = 0, choice;
	while(1)
	{
		while(1)
		{
			system("cls");
			cout << "Welcome to Book Works Management System!" << endl;
			cout << "1. Sign Up (Only for customer)" << endl;
			cout << "2. Sign In" << endl;
			cin >> choice;
			if (choice == 1 || choice == 2) break;
			cout << "Please input 1 or 2!" << endl;
			Sleep(3000);
		}

		if (choice == 1)
		{
			system("cls");
			admin.AddCustomer();
			continue;
		}

		else if (choice == 2)
		{
			system("cls");
			cout << "Please login" << endl;
			while (status == 0) 
			{	
				cout << "Username: " << endl;
				cin >> account;	// Input username
				cout << "Password: " << endl;
				pwd.InputPassword(); // Input password without showing what you input
				md5.reset();
				md5.update(pwd.GetPassword());
				status = Login(account, md5.toString()); // Get user's status
				if (status < 1 || status > 3) 
				{
					time++;	// Try how many times
					if (time < 3) cout << "Your username or password is incorrected, please try again." << endl; 
					else if (time < 4) cout << "Incorrected 3 times, this is the last chance." << endl;
					else 
					{
						cout << "Please contact the admin to reset your password!" << endl;	// fail four times, force to exit
						Sleep(1500);
						return;
					}
					Sleep(1500);
				} 
				else // Choose Book store,  Choose interface depend on status
				{
					system("cls");
					for (size_t i = 0; i < storelist.StoreArray.size(); i++)
						cout << i + 1 << ". " << storelist.StoreArray[i].GetName() << "  |  Address: " << storelist.StoreArray[i].GetAddress() << endl;
					cout << endl;
					cout << "Please input the number of the bookstore that you want to visit:" << endl;
					cin >> storeNum;
					while(storeNum != 1 && storeNum != 2 && storeNum != 3)
					{
						cout << "Please input number between 1 and 3!" << endl;
						cin >> storeNum;
					}
					storelist.LoadLib(storeNum);

					if (status == 1) 
					{
						Admin person;
						person.Interface();
					} 
					else if (status == 2) 
					{
						Staff person;
						person.Interface();
					}
					else if (status == 3) 
					{
						Customer person;
						person.Interface();
					}
					break;
				}

				system("cls");
				cout << "Welcome to Book Works Management System!" << endl;
				cout << "Please login" << endl;
			}
		}
		break;
	}
}


int main(void)
{
	Welcome(); // Welcome interface
}