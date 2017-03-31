#include "customer.h"
#include "storelist.h"

extern Log rec;
extern Library lib;
extern string account;
extern int storeNum;
extern Storelist storelist;
extern Customer customer;
extern int user_index;

void Customer::BuyBook() // Customer buy books
{
	string name, isbn, temp;
	int searchByWhat; // buy by ISBN or name

	while (1) 
	{
		system("cls");
		cout << "Please choose how to search the book by inputing a number" << endl;
		cout << "1. By its name" << endl;
		cout << "2. By its ISBN number" << endl;
		cin >> searchByWhat;

		if (searchByWhat == 1)
		{
			cout << "Please input the name of the book that you want to buy " << endl;
			cin >> name; // Input the book's name
			break;
		}

		else if (searchByWhat == 2)
		{
			cout << "Please input the ISBN number of the book that you want to buy " << endl;
			cin >> isbn; // Input the ISBN number
			break;
		}

		else {
			cout << "Please input 1 or 2, try again " << endl;
			Sleep(1000);
		}
	}

	for (size_t i = 0; i < lib.BookArray.size(); i++) // Find the book
	{
		bool found; // found the book or not
		if (searchByWhat == 1) // search by name
			found = lib.BookArray[i].GetName() == name;

		else if (searchByWhat == 2)
			found = lib.BookArray[i].GetIsbn() == isbn;

		if (found) // If the book is found
		{	
			cout << "Here is the information of this book:" << endl;
			cout << "Name: " << lib.BookArray[i].GetName() << endl;
			cout << "Category: " << lib.BookArray[i].GetCategory() << endl;
			cout << "Price: " << lib.BookArray[i].GetPrice() << endl;
			cout << "Quantity: " << lib.BookArray[i].GetNumber() << endl;
			cout << "Description: " << lib.BookArray[i].GetInformation() << endl;

			cout << "Please input the number of book that your want to buy: " << endl; 
			while (1) 
			{
				cin >> temp; // Input how many book customer want to buy
				if (IsAllDigit(temp)) break;
				cout << "Pleass input a digital number, try again." << endl;
			}
			if (stoi(temp) > lib.BookArray[i].GetNumber()) // If book is not enough for customer to buy
			{
				cout << "Book is not enough! " << endl;
				Sleep(1000);
			} 
			else 
			{
				lib.BookArray[i].SetNumber(lib.BookArray[i].GetNumber() - stoi(temp)); // Decrease the number of this book in lib.BookArray
				lib.BookArray[i].SetNumberOfSale(lib.BookArray[i].GetNumberOfSale() + stoi(temp)); // record the number of sale
				cout << "Buy " << stoi(temp) << " copy of that books, succsessfully! You need to pay $"
				<< stoi(temp)*lib.BookArray[i].GetPrice()*(1-User::GetVip()/10.0) << endl;
				rec.BookLog(account, isbn, "buy", stoi(temp)); // Update BookLog.txt with "buy" operation
				rec.CashLog(account, isbn, "buy", stoi(temp)*lib.BookArray[i].GetPrice()*(1-User::GetVip()/10.0)); // Update CashLog.txt with "buy" operation
				PrintBookArray(); // Output book information to Book.txt
				PrintCash(); // Output cash information to Cash.txt

				if (lib.BookArray[i].GetNumber() < 10)
					rec.ShortOfBookLog(lib.BookArray[i].GetName(), storelist.StoreArray[storeNum-1].GetName());

				Sleep(1000);
				cout << "Automatic quit after 4 seconds." << endl;
				Sleep(4000);
			}
			return;
		}
	}
	cout << "Book not found! " << endl;	// Book not found in Book.txt
	Sleep(1000);
}

void Customer::Refund()	// Customer ask for refund
{
	system("cls");
	string isbn, temp;
	cout << "Please input the ISBN number of the book that you want to ask for refund: " << endl;
	cin >> isbn; // Input the ISBN number
	int bookPos = lib.findBook(isbn); // found the book or not, if found, store its position
	if (bookPos >= 0)
	{
		cout << "How many copies of that book do you want to refund?  " << endl; 
		while (1) 
		{
			cin >> temp; // Input how many book customer want to refund
			if (IsAllDigit(temp)) break;
			cout << "Pleass input a digital number :)   Try again." << endl;
		}
		lib.BookArray[bookPos].SetNumber(lib.BookArray[bookPos].GetNumber() + stoi(temp)); // Increase the number of this book in lib.BookArray
		cout << "Refund " << stoi(temp) << " of that books, succsessfully!" << endl;
		rec.BookLog(account, isbn, "ref", stoi(temp)); // Update BookLog.txt with "buy" operation
		rec.CashLog(account, isbn, "ref", stoi(temp)*lib.BookArray[bookPos].GetPrice()*(1-User::GetVip()/10.0)); // Update CashLog.txt with "buy" operation
		PrintBookArray(); // Output book information to Book.txt
		PrintCash(); // Output cash information to Cash.txt
		Sleep(1000);
		cout << "Automatic quit after 3 seconds." << endl;
		Sleep(2000);
		return;
	}
	else
		cout << "This is not our store's book! " << endl;				// Book not found in Book.txt
	Sleep(1000);
}

void Customer::LeaveComment() // Leave a comment
{
	system("cls");
	string str;
	cout << "Please leave your valuable advice or comment: " << endl;
	cin.ignore();
	getline(cin, str);
	rec.CommentLog(account, str);
	cout << endl << "Comment received! Thank you for your time!" << endl;
	Sleep(1000);
	cout << "Automatic quit after 3 seconds." << endl;
	Sleep(2000);
}

void Customer::Interface() // Admin interface
{
	LoadUser();
	char command;
	int stop = 0;
	while (1) {
		system("cls");
		cout << "Welcome " << lib.UserArray[user_index].GetUsername() << "! You are in the customer mode" << endl;
		cout << "Please choose what you want to do by input a number " << endl;
		while (1) {														// The operation list
			cout << "1 ----- Buy book" << endl;
			cout << "2 ----- Refund" << endl;
			cout << "3 ----- List book (ALL)" << endl;
			cout << "4 ----- List book (By Category)" << endl;
			cout << "5 ----- List book (By Name)" << endl;
			cout << "6 ----- Show more book information by ISBN number" << endl;
			cout << "7 ----- Change my password" << endl;
			cout << "8 ----- Leave a comment" << endl;
			cout << "0 ----- Exit" << endl;
			cin >> command;
			if (command < '0' || command > '8') {
				cout << endl << "Please input number between 0 and 8!" << endl;
			} else break;
		}
		switch (command)
		{
			case '1':
				BuyBook(); // Customer buy books
				break;
			case '2':
				Refund(); // Customer ask for refund
				break;
			case '3':
				ListBookAll(); // List all book
				break;
			case '4':
				ListBookByC(); // List book by category
				break;
			case '5':
				ListBookByN(); // List book by name
				break;
			case '6':
				BookInfor(); // See more information of one book
				break;
			case '7':
				ChangePsw(); // Change password
				break;
			case '8':
				LeaveComment(); // Leave a comment
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