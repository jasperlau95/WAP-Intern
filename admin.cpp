#include "admin.h"
#include "md5.h"

extern Log rec;
extern Library lib;
extern string account;
extern MD5 md5;

void Admin::AddUser() // Add new user
{
	User newuser; // Define 'newuser' to User class
	string name, pwd;
	int status;
	while (1){
		system("cls");
		cout << "Please input the username that you want to register:" << endl;
		cin.ignore();
		getline(cin, name); // Input username
		if (lib.findUser(name) < 0) // findUser() will return -1 if not user with name name
			break;
		else
		{
			cout << "User already exist! " << endl;
			Sleep(2000);
		}
	}

	cout << "Please input your password" << endl; // The case that user doesn't exist in User.txt
	cin >> pwd;
	while (1){
		cout << "Please input the user type:" << endl;
		cout << "1: Admin" << endl;
		cout << "2: Employee" << endl;
		cout << "3: Customer" << endl;
		cin >> status;
		if (status == 1 || status == 2 || status == 3)
			break;
		else
			cout << "Please input number from 1 to 3!" << endl;
	}
	newuser.SetUsername(name);
	md5.reset();
	md5.update(pwd);
	newuser.SetPassword(md5.toString());
	newuser.SetStatus(status);
	lib.UserArray.push_back(newuser); // Add newuser to lib.UserArray
	cout << "Add user succsessfully!" << endl;
	Sleep(1000);
	cout << "Automatic quit after 3 seconds." << endl;
	Sleep(2000);
	rec.UserLog(account, name, "add", 0); // Update UserLog.txt with "add" operation
	PrintUserArray(); // Output user information to User.txt
}

void Admin::DelUser() // Delete old user
{
	system("cls");
	int choice, userPos;
	string name;
	cout << "Please input the username that you want to delete:" << endl;
	cin.ignore();
	getline(cin, name); // Input the username
	userPos = lib.findUser(name);
	if (userPos >= 0)
	{
		cout << "Are you sure you want to delete this user? (press 1: continue, 0: quit)" << endl; // comfirm delete
		cin >> choice;
		if (choice == 1) // Make sure want to delete this user 
		{		
			lib.UserArray[userPos].SetStatus(0);
			cout << "Delete user succsessfully!" << endl;
			PrintUserArray();
			rec.UserLog(account, name, "del", 0); // Update UserLog.txt with "del" operation
		}
	}
	else
		cout << "User not exist! " << endl;	// Username not exist in User.txt or status equal to 0
	Sleep(1000);
}

void Admin::SetUser() // Change user's status (like Customer, Staff, Administartor)
{
	system("cls");
	int choice, userPos; // userPos: user's position in the library
	string name;
	cout << "Please input the username that you want to change status" << endl;
	cin.ignore();
	getline(cin, name);	// Input the username
	userPos = lib.findUser(name);
	if (userPos >= 0) // user exist
	{
		cout << "Please input a number:  3 for Customer, 2 for Staff, 1 for Administartor, 0 for quit:" << endl;
		cin >> choice;
		if (choice != 0) // Make sure want to change this user's status 
		{ 
			lib.UserArray[userPos].SetStatus(choice);
			cout << "Change user status succsessfully!" << endl;
		} 
		else 
			cout << "Change canceled." << endl; // Cancel the change operation
		Sleep(1000);
		cout << "Automatic quit after 3 seconds." << endl;
		Sleep(2000);
		PrintUserArray(); // Output user information to User.txt
		rec.UserLog(account, name, "set", choice);				// Update UserLog.txt with "set" operation
	}
	else
		cout << "User not exist! " << endl;	// Username not exist in User.txt or status equal to 0(deleted)
	Sleep(1000);
}

void Admin::ListUser()	// List all users' information
{
	system("cls");
	int temp;
	vector<string> Status; // Vector of string, use to indicate the status of user
	Status.push_back("Admin");
	Status.push_back("Staff");
	Status.push_back("Customer");
	cout << "This is the information of all the users:" << endl;
	cout << "------------------------------------" << endl;
	cout << "|       Username      |   Status   |" << endl;
	cout << "------------------------------------" << endl;
	for (size_t i = 0; i < lib.UserArray.size(); i++) 					// Output each user information 
		if (lib.UserArray[i].GetStatus() != 0)
			cout << "|" << setw(21) << lib.UserArray[i].GetUsername() << "|" << setw(12) << Status[lib.UserArray[i].GetStatus() - 1] << "|" << endl;
	cout << "------------------------------------" << endl;
	cout << endl;
	cout << "Input 0 to exit" << endl;
	cin >> temp;
	while (temp != 0)
		cin >> temp;
}

void Admin::Interface(string username)	// Admin interface
{
	char command;
	int stop = 0;
	while (1) {
		system("cls");
		cout << "Welcome " << username << "! You are in the administartor mode" << endl;
		cout << "Please choose what you want to do:" << endl;
		while (1) {														// The operation list
			cout << "1 ----- Add new user" << endl;
			cout << "2 ----- Delete user" << endl;
			cout << "3 ----- Change user privilage" << endl;
			cout << "4 ----- Add new book" << endl;
			cout << "5 ----- Delete book" << endl;
			cout << "6 ----- Change book information" << endl;
			cout << "7 ----- List book (ALL)" << endl;
			cout << "8 ----- List book (By Category)" << endl;
			cout << "9 ----- List book (By Name)" << endl;
			cout << "* ----- Show more book information by ISBN number" << endl;
			cout << "& ----- List all users' information" << endl;
			cout << "$ ----- Lookup net profit" << endl;
			cout << "% ----- Change my password" << endl;
			cout << "0 ----- Exit;" << endl;
			cin >> command;
			if (command != '*' && command != '&' && command != '%' && command != '$' && (command < '0' || command > '9')) {						// If command doesn't match input rule
				cout << endl << "Wrong!! You should input '*','&','%','$' or number between 0-9" << endl;
				cout << "Please repick an order :) " << endl;									// Ask to input again
			} else break;
		}
		switch (command)
		{
			case '1':
				AddUser(); // Add new user
				break;
			case '2':
				DelUser(); // Delete old user
				break;
			case '3':
				SetUser(); // Change user's status (like Customer, Staff, Administartor)
				break;
			case '4':
				AddBook(); // Add new books
				break;
			case '5':
				DelBook(); // Delete some books
				break;
			case '6':
				SetBook(); // Change books' information
				break;	
			case '7':
				ListBookAll(); // List all book
				break;
			case '8':
				ListBookByC(); // List book by category
				break;
			case '9':
				ListBookByN(); // List book by name
				break;
			case '*':
				BookInfor(); // See more information of one book
				break;
			case '%':
				ChangePsw(); // Change password
				break;
			case '$':
				ViewProfit(); // Lookup profit
				break;
			case '&':
				ListUser();	// List all users' information
				break;
			case '0':
				stop = 1;
				cout << "System will quit after 3 seconds " <<endl;
				Sleep(3000);
				break;
		}
		if (stop) break;
	}
}