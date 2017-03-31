#include "library.h"

extern string book_address;
extern string cash_address;

int Library::findUser(string name) // if the book with name is the library, return true
{
	for (size_t i = 0; i < UserArray.size(); i++)
		if (UserArray[i].GetUsername() == name && UserArray[i].GetStatus() != 0) // If find that username (0 means deleted)
			return i;
	return -1;
}

void Library::LoadUser() // Load User.txt(users' account and password database)
{
	User olduser;
	string str;
	ifstream ifs("User.csv"); // Open and read User.txt
	if(!ifs) // If can't open
	{ 	
		cerr << "User.csv can't open" << endl;
		abort(); // Exit
	}
	while (getline(ifs, str)) 
	{
		size_t i = str.find(","); // Find fisrt spacebar
		olduser.SetUsername(str.substr(0, i)); // Divide str by spacebar and get username
		str = str.substr(i+1);

		i = str.find(","); // Find second spacebar
		olduser.SetPassword(str.substr(0, i));	// Divide str by spacebar and get password
		str = str.substr(i+1);

		i = str.find(","); // Find thirt spacebar
		olduser.SetStatus(stoi(str.substr(0, i))); // Divide str by spacebar and get status

		olduser.SetVip(stoi(str.substr(i+1)));

		UserArray.push_back(olduser); // Add to lib.UserArray
	}
	ifs.close(); // Close User.txt
}

int Library::findBook(string isbn) // check if the book with the given ISBN exist
{
	for (size_t i = 0; i < BookArray.size(); i++)
		if (BookArray[i].GetIsbn() == isbn) // If find that book, return its position in the BookArray
			return i;
	return -1;
}

void Library::LoadBook()	// Load Book.txt
{
	Book oldbook;
	string str;
	ifstream ifs(book_address); // Open and read Book.txt
	if(!ifs) // If can't open
	{ 
		cerr << book_address << " can't open" << endl;
		abort(); // Exit
	}
	while (getline(ifs, str)) {
		size_t i = str.find(","); // Find fisrt spacebar
		oldbook.SetName(str.substr(0, i)); // Divide str by spacebar and get bookname
		str = str.substr(i+1);

		i = str.find(","); // Find second spacebar
		oldbook.SetIsbn(str.substr(0, i)); // Divide str by spacebar and get ISBN number
		str = str.substr(i+1);

		i = str.find(",");
		oldbook.SetAuthor(str.substr(0, i)); // Divide str by spacebar and get author
		str = str.substr(i+1);
		
		i = str.find(",");
		oldbook.SetNumber(stoi(str.substr(0, i))); // Divide str by spacebar and get copy number
		str = str.substr(i+1);
		
		i = str.find(",");
		oldbook.SetCategory(stoi(str.substr(0, i))); // Divide str by spacebar and get category number
		str = str.substr(i+1);
		
		i = str.find(",");
		oldbook.SetPrice(stoi(str.substr(0, i))); // Divide str by spacebar and get price
		str = str.substr(i+1);

		i = str.find(",");
		oldbook.SetInformation(str.substr(0, i));

		oldbook.SetNumberOfSale(stoi(str.substr(i+1)));

		BookArray.push_back(oldbook); // Add to lib.BookArray
	}
	ifs.close(); // Close Book.txt
}

void Library::LoadCash() // Load Cash.txt
{
	ifstream ifs(cash_address); // Open and read Book.txt
	if(!ifs) // If can't open
	{ 
		cerr << cash_address << " can't open" << endl;
		abort(); // Exit
	}
	ifs >> income;	// Input income
	ifs >> outcome;	// Input outcome
	ifs.close(); // Close Cash.txt
}