#include "log.h"
#include "library.h"
#include "windows.h"
#include "conio.h"

extern Library lib;
extern string book_log_address;
extern string cash_log_address;

void Log::UserLog(string loginname, string username, string operation, int vip_level)			// Add new information to UserLog.txt
{
	ofstream ofs;
	ofs.open("UserLog.txt", ios::app); // Open and append to UserLog.txt
	if (!ofs) // If can't open
	{
		cerr << "UserLog.txt can't open" << endl;
		abort(); // Exit
	}
	SYSTEMTIME time; 
	GetLocalTime(&time);											// Get system time
	ofs << "[ " << time.wYear << "-" << time.wMonth << "-" << time.wDay << " " << time.wHour << ":" << time.wMinute << ":" << time.wSecond << " ]";			// Output system tiime
	if (operation == "add") 
		ofs << " Admin(" << loginname << ") add a new user(" << username << ")" << endl;
	else if (operation == "del")
		ofs << " Admin(" << loginname << ") delete a user(" << username << ")" << endl;
	else if (operation == "set")
		ofs << " Admin(" << loginname << ") set user(" << username << ")'s vip level to (" << vip_level <<") " << endl;
	else if (operation == "psw")
		ofs << " User(" << loginname << ") change his/her password " << endl;
	ofs.close();												// Close UserLog.txt
}

void Log::BookLog(string loginname, string bookisbn, string operation, int number)				// Add new information to BookLog.txt
{
	ofstream ofs;
	ofs.open(book_log_address, ios::app);  						// Open and append to BookLog.txt
	if (!ofs) {												// If can't open
		cerr << book_log_address << " can't open" << endl;
		abort();												// Exit
	}	
	SYSTEMTIME time; 
	GetLocalTime(&time);			// Get system time
	ofs << "[ " << time.wYear << "-" << time.wMonth << "-" << time.wDay << " " << time.wHour << ":" << time.wMinute << ":" << time.wSecond << " ]";			// Output system tiime
	if (operation == "buy") 
		ofs << " Customer(" << loginname << ") buy books(ISBN:" << bookisbn << ") with " << number << " copy(s)" << endl;
	else if (operation == "ref")
		ofs << " Customer(" << loginname << ") refund books(ISBN:" << bookisbn << ") with " << number << " copy(s)" << endl;
	else if (operation == "add")
		ofs << " Manager(" << loginname << ") add new books(ISBN:" << bookisbn << ") with " << number << " copy(s)" << endl;
	else if (operation == "del")
		ofs << " Manager(" << loginname << ") delete books(ISBN:" << bookisbn << ") with " << number << " copy(s)" << endl;
	else if (operation == "set")
		ofs << " Manager(" << loginname << ") change book(ISBN:" << bookisbn << ")'s information " << endl;
	ofs.close();												// Close BookLog.txt
}

void Log::CashLog(string loginname, string bookisbn, string operation, double money)			// Add new information to CashLog.txt
{
	ofstream ofs;
	ofs.open(cash_log_address, ios::app); // Open and append to BookLog.txt
	if (!ofs) // If can't open	
	{					
		cerr << cash_log_address << " can't open" << endl;
		abort(); // Exit
	}	
	SYSTEMTIME time; 
	GetLocalTime(&time);  										// Get system time
	ofs << "[ " << time.wYear << "-" << time.wMonth << "-" << time.wDay << " " << time.wHour << ":" << time.wMinute << ":" << time.wSecond << " ]";			// Output system tiime
	if (operation == "add") {
		ofs << " Manager(" << loginname << ") add new books(ISBN:" << bookisbn << ") ---------- Outcome: " << money << endl;
		lib.SetOutcome(money + lib.GetOutcome());
	} else if (operation == "buy") {
		ofs << " Customer(" << loginname << ") buy books(ISBN:" << bookisbn << ") ---------- Income: " << money << endl;
		lib.SetIncome(money + lib.GetIncome());
	} else if (operation == "ref") {
		ofs << " Customer(" << loginname << ") refund books(ISBN:" << bookisbn << ") ---------- Outcome: " << money << endl;
		lib.SetOutcome(money + lib.GetOutcome());
	}
	ofs.close(); // Close CashLog.txt
}

void Log::CommentLog(string loginname, string comment) // Add new comment to comment.txt
{
	ofstream ofs;
	ofs.open("Comments.txt", ios::app); // Open and append to Comments.txt
	if (!ofs) // If can't open	
	{					
		cerr << "Comments.txt can't open" << endl;
		abort(); // Exit
	}	
	SYSTEMTIME time; 
	GetLocalTime(&time);  										// Get system time
	ofs << "[ " << time.wYear << "-" << time.wMonth << "-" << time.wDay << " " << time.wHour << ":" << time.wMinute << ":" << time.wSecond << " ]";	// Output system tiime
	ofs << " Customer(" << loginname << ") leave a comment: " << comment << endl;
	ofs.close(); // Close CashLog.txt

	ofstream ofs2;
	ofs2.open("CheckComment.txt"); // Open and cover CheckCOmment.txt
	if (!ofs2) // If can't open
	{ 
		cerr << "CheckComment.txt can't open" << endl;
		abort(); // Exit
	}
	ofs2 << "true" << endl;
	ofs2.close(); // CheckCOmment.txt
}

void Log::ShortOfBookLog(string bookName, string storeName) // Add new short of book reminder to ShortOfBook.txt
{
	string str;
	ofstream ofs;
	ofs.open("ShortOfBook.txt", ios::app); // Open and append to ShortOfBook.txt
	if (!ofs) // If can't open	
	{					
		cerr << "ShortOfBook.txt can't open" << endl;
		abort(); // Exit
	}	
	SYSTEMTIME time; 
	GetLocalTime(&time);  										// Get system time
	ofs << "[ " << time.wYear << "-" << time.wMonth << "-" << time.wDay << " " << time.wHour << ":" << time.wMinute << ":" << time.wSecond << " ]";	// Output system tiime
	ofs << "The quantity of the book \"" << bookName << "\" in the store \"" 
	<< storeName << "\" is less than 10 now, please restock it ASAP!" << endl;
	ofs.close(); // Close ShortOfBook.txt


	ofstream ofs2;
	ofs2.open("CheckShortOfBook.txt"); // Open and cover CheckShortOfBook.txt
	if (!ofs2) // If can't open
	{ 
		cerr << "CheckShortOfBook.txt can't open" << endl;
		abort(); // Exit
	}
	ofs2 << "true" << endl;
	ofs2.close(); // Close ShortOfBook.txt
}

void Log::CheckShortOfBookLog()
{
	string str;
	ifstream ifs("CheckShortOfBook.txt"); // Check CheckShortOfBook.txt
	if(!ifs) // If can't open
	{ 	
		cerr << "CheckShortOfBook.txt can't open" << endl;
		abort(); // Exit
	}
	getline(ifs, str);
	bool temp = (str == "true");
	if (temp)
	{
		cout << "You have emergent message, press any button to check!" << endl;
		_getch();
		system("cls");
		ifstream ifs1("ShortOfBook.txt");
		if (ifs1.is_open())
		{
			while (getline (ifs1, str))
			{
				cout << str << endl;
			}
			ifs1.close();
		}
		cout << endl << "Press any button twice to return to the interface." << endl;
		_getch();
		_getch();
	}
	ifs.close(); // Close ShortOfBook.txt

	if (temp)
	{
		ofstream ofs;
		ofs.open("CheckShortOfBook.txt"); // Open and cover CheckShortOfBook.txt
		ofs << "false" << endl;
		ofs.close(); // Close CheckShortOfBook.txt
	}
}

void Log::CheckCommentLog()
{
	string str;
	ifstream ifs("CheckComment.txt"); // Open and read CheckComment.txt
	if(!ifs) // If can't open
	{ 	
		cerr << "CheckComment.txt can't open" << endl;
		abort(); // Exit
	}
	getline(ifs, str);
	bool temp = (str == "true");
	if (temp)
	{
		cout << "You have new comment, press any button to check!" << endl;
		_getch();
		system("cls");
		ifstream comment("Comments.txt");
		if (comment.is_open())
		{
			while (getline (comment, str))
			{
				cout << str << endl;
			}
			comment.close();
		}
		cout << endl << "Press any button twice to return to the interface." << endl;
		_getch();
		_getch();
	}
	ifs.close(); // Close CheckComment.txt

	if (temp)
	{
		ofstream ofs;
		ofs.open("CheckComment.txt"); // Open and cover CheckComment.txt
		ofs << "false" << endl;
		ofs.close(); // Close CheckComment.txt	
	}
}
