#include "admin.h"
#include "md5.h"
#include "conio.h"

extern Log rec;
extern Library lib;
extern string account;
extern MD5 md5;
extern int user_index;

string Status[3] = {"Admin", "Staff", "Customer"}; // array of string, use to indicate the status of user
string Vip[4] = {"non-vip", "vip", "vvip", "vvvip"}; // array of string, use to indicate the status of user

void Admin::AddUser() // Add new user
{
	User newuser; // Define 'newuser' to User class
	string name, pwd;
	int status, vip_level;
	while (1){
		system("cls");
		cout << "Please input the username that you want to register:" << endl;
		cin.ignore();
		getline(cin, name); // Input username
		if (lib.findUser(name) < 0) // findUser() will return -1 if not user with name name
			break;
		else
		{
			cout << "Username already exist! " << endl;
			Sleep(2000);
		}
	}

	cout << "Please input your password" << endl; // The case that user doesn't exist in User.txt
	cin >> pwd;
	while (1)
	{
		system("cls");
		cout << "Please input the user type:" << endl;
		cout << "1: Admin" << endl;
		cout << "2: Employee" << endl;
		cout << "3: Customer" << endl;
		cout << "0: Back to previous page" << endl;
		cin >> status;
		if (status == 0) return;
		else if (status == 1 || status == 2 || status == 3)
			break;
		else
			cout << "Please input number from 0 to 3!" << endl;
	}
	while (1)
	{
		system("cls");
		cout << "Please input the user's vip level:" << endl;
		cout << "0: normal (non-vip)" << endl;
		cout << "1: vip (10% discount)" << endl;
		cout << "2: vvip (20% discount)" << endl;
		cout << "3: vvvip (30% discount)" << endl;
		cout << "9: Back to previous page" << endl;
		cin >> vip_level;
		if (vip_level == 9) return;
		else if (vip_level == 0 || vip_level == 1 || vip_level == 2 || vip_level == 3)
			break;
		else
			cout << "Please input number from 0 to 3!" << endl;
	}

	newuser.SetUsername(name);
	md5.reset();
	md5.update(pwd);
	newuser.SetPassword(md5.toString());
	newuser.SetStatus(status);
	newuser.SetVip(vip_level);
	lib.UserArray.push_back(newuser); // Add newuser to lib.UserArray
	cout << "Add user succsessfully!" << endl;
	Sleep(1000);
	cout << "Automatic quit in 2 seconds." << endl;
	Sleep(2000);
	rec.UserLog(account, name, "add", 0); // Update UserLog.txt with "add" operation
	PrintUserArray(); // Output user information to User.txt
}

void Admin::AddCustomer() // Add new user
{
	User newuser; // Define 'newuser' to User class
	string name, pwd;
	while (1){
		system("cls");
		cout << "Please input the username that you want to register:" << endl;
		cin.ignore();
		getline(cin, name); // Input username
		if (lib.findUser(name) < 0) // findUser() will return -1 if not user with name name
			break;
		else
		{
			cout << "Username already exist! " << endl;
			Sleep(2000);
		}
	}

	cout << "Please input your password" << endl; // The case that user doesn't exist in User.txt
	cin >> pwd;

	newuser.SetUsername(name);
	md5.reset();
	md5.update(pwd);
	newuser.SetPassword(md5.toString());
	newuser.SetStatus(3);
	newuser.SetVip(0);
	lib.UserArray.push_back(newuser); // Add newuser to lib.UserArray

	cout << "Sign up succsessfully!" << endl;
	Sleep(1000);
	cout << "Automatic return to the Login page in 2 seconds." << endl;
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
	cout << "Please input the username that you want to change its information:" << endl;
	cin.ignore();
	getline(cin, name);	// Input the username
	userPos = lib.findUser(name);
	if (userPos >= 0) // user exist
	{
		cout << "The user's current status is: " << Status[lib.UserArray[userPos].GetStatus()-1] << endl;
		cout << "Do you want to change it? (input 1 for YES and 0 for NO )" << endl;
		cin >> choice;
		if (choice == 1) 
		{
			cout << "Please input a number:  3 for Customer, 2 for Staff, 1 for Administartor, 0 for quit:" << endl;
			cin >> choice;
			if (choice != 0) // Make sure want to change this user's status 
			{ 
				lib.UserArray[userPos].SetStatus(choice);
				cout << "Change user status succsessfully!" << endl;
			} 
			else return;
		}

		cout << "The user's current vip level is: " << Vip[lib.UserArray[userPos].GetVip()] << endl;
		cout << "Do you want to change it? (input 1 for YES and 0 for NO )" << endl;
		cin >> choice;
		if (choice == 1) 
		{
			cout << "Please input a number:  0 for non-vip, 1 for vip, 2 for vvip, 3 for vvvip, 9 for quit:" << endl;
			cin >> choice;
			if (choice != 9) // Make sure want to change this user's status 
			{ 
				lib.UserArray[userPos].SetVip(choice);
				cout << "Change user vip level succsessfully!" << endl;
			} 
			else return;
		}
		
		Sleep(1000);
		cout << "Automatic quit in 2 seconds." << endl;
		Sleep(2000);
		PrintUserArray(); // Output user information to User.txt
		rec.UserLog(account, name, "set", choice); // Update UserLog.txt with "set" operation
	}
	else
		cout << "User not exist! " << endl;	// Username not exist in User.txt or status equal to 0(deleted)
	Sleep(1000);
}

void Admin::ListUser()	// List all users' information
{
	system("cls");
	int temp;

	cout << "This is the information of all the users:" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "|       Username      |   Status   | Vip Level |" << endl;
	cout << "------------------------------------------------" << endl;
	for (size_t i = 0; i < lib.UserArray.size(); i++) 					// Output each user information 
		if (lib.UserArray[i].GetStatus() != 0)
			cout << "|" << setw(21) << lib.UserArray[i].GetUsername() << "|" << setw(12) 
			<< Status[lib.UserArray[i].GetStatus() - 1] << "|" << setw(11) 
			<< Vip[lib.UserArray[i].GetVip()] << "|" << endl;
	cout << "------------------------------------------------" << endl;
	cout << endl;
	cout << "Input 0 to exit" << endl;
	cin >> temp;
	while (temp != 0)
		cin >> temp;
}

void Admin::ShowSalesData() // Show the sales data of each book
{
	system("cls");
	int temp;
	cout << "This is the sales data of all the books:" << endl;
	cout << "----------------------------------------------------------------------------------------------" << endl;
	cout << "|    ISBN    |           Name          |   Category   | Quantity | Unit Price | Sales Volume |" << endl;
	cout << "----------------------------------------------------------------------------------------------" << endl;
	int maxSalesBookIndex = 0, maxSalesNumber = 0, minSalesBookIndex = 0, minSalesNumber = 0;
	for (size_t i = 0; i < lib.BookArray.size(); i++) // Output each book information
	{
		cout << "|" << setw(12) << lib.BookArray[i].GetIsbn() << "|" <<  setw(25) << lib.BookArray[i].GetName() << "|" << setw(14) << lib.BookArray[i].GetCategoryName()<<  "|" 
			<<  setw(10) << lib.BookArray[i].GetNumber() << "|"<<  setw(12) << setiosflags(ios::fixed) << setprecision(2) <<lib.BookArray[i].GetPrice()  << "|" 
			<< setw(14) << lib.BookArray[i].GetNumberOfSale()<<  "|" << endl;

		if (lib.BookArray[i].GetNumberOfSale() > maxSalesNumber)
		{
			maxSalesBookIndex = i;
			maxSalesNumber = lib.BookArray[i].GetNumberOfSale();
		}
		else if (lib.BookArray[i].GetNumberOfSale() < maxSalesNumber)
		{
			minSalesBookIndex = i;
			minSalesNumber = lib.BookArray[i].GetNumberOfSale();
		}
	}

	cout << "----------------------------------------------------------------------------------------------" << endl;
	cout << endl;
	cout << "The best seller is \"" << lib.BookArray[maxSalesBookIndex].GetName() << "\", it's sales Volume is: "
		<< lib.BookArray[maxSalesBookIndex].GetNumberOfSale() << endl;
	cout << "The worst seller is \"" << lib.BookArray[minSalesBookIndex].GetName() << "\", it's sales Volume is: "
		<< lib.BookArray[minSalesBookIndex].GetNumberOfSale() << endl << endl;

	cout << "Tips: For the book which sells best, you may consider restocking more copies of this book. And for the book which sells worst, you may consider lowering it's pricee and not to restock it next time." << endl << endl;

	while(1)
	{
		cout << "Input 0 to exit, 1 to display the books on web: " << endl;
		cin >> temp;
		if (temp == 1)
		{
			ofstream doc("html_file.html");
			if (doc.fail())
			{
				cout << "ERROR: there was an error exporting the file" << endl;
				abort(); // Exit
			}
			else
			{
				cout << "please wait..." << endl;
				doc << "<!DOCTYPE html><html><head><title>Departmental Store Management System</title><style>td{border: solid 2px #ddd;}tr:hover{background:#ddd;}</style></head><body><h2>Books List</h2><table><tr>	<td>ISBN</td> <td>Book name</td> <td>Category&nbsp;</td> <td>Quantity&nbsp;</td>	<td>Unit price&nbsp;</td>	<td>Sales Volume&nbsp;</td></tr> " << endl;

				for (size_t i = 0; i < lib.BookArray.size(); i++)
					doc << "<tr>" << "<td>" << lib.BookArray[i].GetIsbn() << "&nbsp;" << "</td>" << "<td>" << lib.BookArray[i].GetName() << "&nbsp;" << "</td>" << "<td>"<< lib.BookArray[i].GetCategoryName() << "&nbsp;" << "</td>" << "<td>" << lib.BookArray[i].GetNumber() << "</td>" << "<td>" << lib.BookArray[i].GetPrice() << "</td>" << "<td>" << lib.BookArray[i].GetNumberOfSale() << "&nbsp;" << "</td>" << "</tr>";
				
				doc << "</table></body></html>";
				doc << "<br>";
				doc << "The best seller is \"" << lib.BookArray[maxSalesBookIndex].GetName() << "\", it's sales Volume is: "
					<< lib.BookArray[maxSalesBookIndex].GetNumberOfSale() << "<br>";
				doc << "The worst seller is \"" << lib.BookArray[minSalesBookIndex].GetName() << "\", it's sales Volume is: "
					<< lib.BookArray[minSalesBookIndex].GetNumberOfSale() << "<br>";
				doc << "<br>";
				doc << "Tips: For the book which sells best, you may consider restocking more copies of this book. And for the book which sells worst, you may consider lowering it's pricee and not to restock it next time." << "<br>" << "<br>";
				doc.close();
				system("start html_file.html");
			}
		}
		else if (temp == 0)
			break;
		else
			cout << "Please input 0 or 1!" << endl;
	}
}

void Admin::Interface()	// Admin interface
{
	LoadUser();

	char command;
	int stop = 0;
	system("cls");
	string str;
	rec.CheckShortOfBookLog();
	rec.CheckCommentLog();

	while (1) {
		system("cls");
		cout << "Welcome " << lib.UserArray[user_index].GetUsername() << "! You are in the administartor mode" << endl;
		cout << "Please choose what you want to do:" << endl;
		while (1) {														// The operation list
			cout << "1 ----- Add new user" << endl;
			cout << "2 ----- Delete user" << endl;
			cout << "3 ----- Change user information" << endl;
			cout << "4 ----- Add new book" << endl;
			cout << "5 ----- Delete book" << endl;
			cout << "6 ----- Change book information" << endl;
			cout << "7 ----- List book (ALL)" << endl;
			cout << "8 ----- List book (By Category)" << endl;
			cout << "9 ----- List book (By Name)" << endl;
			cout << "* ----- Show more book information by ISBN number" << endl;
			cout << "| ----- List all users' information" << endl;
			cout << "@ ----- Lookup sales data" << endl;
			cout << "$ ----- Lookup net profit" << endl;
			cout << "% ----- Change my password" << endl;
			cout << "0 ----- Exit;" << endl;
			cin >> command;
			if (command != '@' && command != '*' && command != '|' && command != '%' && command != '$' && (command < '0' || command > '9')) {						// If command doesn't match input rule
				cout << endl << "Please input '@', '*','|','%','$' or number between 0-9:" << endl;
			} 
			else break;
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
				SetUser(); // Change user's status (like Customer, Staff, Administartor) and their vip level
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
			case '@':
				ShowSalesData(); // Show the sales data of each book
				break;
			case '|':
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