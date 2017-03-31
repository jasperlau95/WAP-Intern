#include "user.h"
#include "library.h"
#include "cctype"
#include "algorithm"

extern Log rec;
extern Library lib;
extern string account;
extern string book_address;
extern string cash_address;
extern int user_index;

void User::PrintUserArray() // Output user information to User.txt
{
	ofstream fout;
	fout.open("User.csv"); // Open and cover User.txt
	if (!fout) // If can't open
	{ 
		cerr << "User.csv can't open" << endl;
		abort(); // Exit
	}
	for (size_t i = 0; i < lib.UserArray.size(); i++ ) // Output each user's information
		fout << lib.UserArray[i].GetUsername() << "," << lib.UserArray[i].GetPassword() << "," << lib.UserArray[i].GetStatus() << "," << lib.UserArray[i].GetVip() << endl;
	fout.close(); // Close User.txt
}

void User::PrintBookArray()	// Output book information to Book.txt
{
	ofstream fos;
	fos.open(book_address); // Open and cover Book.txt
	if  (!fos) { // If can't open
		cerr << book_address << " can't open" << endl;
		abort(); // Exit
	}
	for (size_t i = 0; i < lib.BookArray.size(); i++ ) // Output each book's information
		fos << lib.BookArray[i].GetName() << "," << lib.BookArray[i].GetIsbn() << "," << lib.BookArray[i].GetAuthor() 
			<< "," << lib.BookArray[i].GetNumber() << "," << lib.BookArray[i].GetCategory() 
			<< "," << lib.BookArray[i].GetPrice() << "," << lib.BookArray[i].GetInformation()
			<< "," << lib.BookArray[i].GetNumberOfSale() << endl;

	fos.close(); // Close Book.txt
}

void User::PrintCash() // Output cash information to Cash.txt
{
	ofstream fout;
	fout.open(cash_address); // Open and cover Cash.txt
	if (!fout) // If can't open
	{
		cerr << cash_address << " can't open" << endl;
		abort(); // Exit
	}
	fout << lib.GetIncome() << endl; // Output income
	fout << lib.GetOutcome() << endl; // Output outcome
	fout.close(); // Close Book.txt
}

 int User::IsAllDigit(const string& str) // Check if str is all made of digital number
{
    int i ;
    for(i = 0; i != str.length(); i++)
        if (!isdigit(str[i]) && (str[i]!='.')) return 0; // '.' for double number
    return 1;
}

void User::ListBookAll() // List all book
{
	system("cls");
	int temp;
	cout << "This is the list of all the book:" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << "|       ISBN       |            Name           |   Category   | Quantity |  Unit Price  |" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	for (size_t i = 0; i < lib.BookArray.size(); i++) // Output each book information
	{
		cout << "|" << setw(18) << lib.BookArray[i].GetIsbn() << "|" <<  setw(27) << lib.BookArray[i].GetName() << "|" << setw(14) << lib.BookArray[i].GetCategoryName()<<  "|" 
			<<  setw(10) << lib.BookArray[i].GetNumber() << "|"<<  setw(14) << setiosflags(ios::fixed) << setprecision(2) <<lib.BookArray[i].GetPrice()  << "|" << endl;
	}
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << endl;
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
				doc << "<!DOCTYPE html><html><head><title>Departmental Store Management System</title><style>td{border: solid 2px #ddd;}tr:hover{background:#ddd;}</style></head><body><h2>Books List</h2><table><tr>	<td>ISBN</td> <td>Book name</td> <td>Category&nbsp;</td> <td>Quantity&nbsp;</td>	<td>Unit price&nbsp;</td>	<td>Information</td></tr> " << endl;

				for (size_t i = 0; i < lib.BookArray.size(); i++)
					doc << "<tr>" << "<td>" << lib.BookArray[i].GetIsbn() << "&nbsp;" << "</td>" << "<td>" << lib.BookArray[i].GetName() << "&nbsp;" << "</td>" << "<td>"<< lib.BookArray[i].GetCategoryName() << "&nbsp;" << "</td>" << "<td>" << lib.BookArray[i].GetNumber() << "</td>" << "<td>" << lib.BookArray[i].GetPrice() << "</td>" << "<td>" << lib.BookArray[i].GetInformation() << "&nbsp;" << "</td>" << "</tr>";
				doc << "</table></body></html>";
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

void User::ListBookByC() // List book by category
{
	system("cls");
	int temp, category;
	cout << "Category List:" << endl;
	cout << "1. Art" << endl;
	cout << "2. Engineering" << endl;
	cout << "3. Science" << endl;
	cout << "Please input the number of the category of the book:" << endl;
	while (1) 
	{
		cin >> category; // Input category number 
		if (category == 1 || category == 2 || category == 3) break;
		cout << "Pleass input a number between 1 and 3!" << endl;
	}
	system("cls");
	string categoryList[3] = {"Art", "Engineering", "Science"};
	cout << "This is the list of all the book in category " << categoryList[category-1] << " :" << endl;
	cout << "-------------------------------------------------------------------------" << endl;
	cout << "|       ISBN       |            Name           | Quantity |  Unit Price |" << endl;
	cout << "-------------------------------------------------------------------------" << endl;
	for (size_t i = 0; i < lib.BookArray.size(); i++) // Output each book information in this category
	{	if (lib.BookArray[i].GetCategory() == category) 
		{
			cout << "|" << setw(18) << lib.BookArray[i].GetIsbn() << "|" <<  setw(27) << lib.BookArray[i].GetName() <<  "|" 
				<<  setw(10) << lib.BookArray[i].GetNumber() << "|"<<  setw(13) << setiosflags(ios::fixed) << setprecision(2) <<lib.BookArray[i].GetPrice()  << "|" << endl;
		}
	}
	cout << "-------------------------------------------------------------------------" << endl;
	cout << endl;

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
				doc << "<!DOCTYPE html><html><head><title>Departmental Store Management System</title><style>td{border: solid 2px #ddd;}tr:hover{background:#ddd;}</style></head><body><h2>Books List</h2><table><tr>	<td>ISBN</td> <td>Book name</td> <td>Category&nbsp;</td> <td>Quantity&nbsp;</td>	<td>Unit price&nbsp;</td>	<td>Information</td></tr> " << endl;

				for (size_t i = 0; i < lib.BookArray.size(); i++)
					if (lib.BookArray[i].GetCategory() == category) 
						doc << "<tr>" << "<td>" << lib.BookArray[i].GetIsbn() << "&nbsp;" << "</td>" << "<td>" << lib.BookArray[i].GetName() << "&nbsp;" << "</td>" << "<td>"<< lib.BookArray[i].GetCategoryName() << "&nbsp;" << "</td>" << "<td>" << lib.BookArray[i].GetNumber() << "</td>" << "<td>" << lib.BookArray[i].GetPrice() << "</td>" << "<td>" << lib.BookArray[i].GetInformation() << "&nbsp;" << "</td>" << "</tr>";
				doc << "</table></body></html>";
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
;
bool findByName(string fullName, string searchName)
{
	transform(fullName.begin(), fullName.end(), fullName.begin(), toupper);
	transform(searchName.begin(), searchName.end(), searchName.begin(), toupper);
	return fullName.find(searchName) != string::npos;
}

void User::ListBookByN() // List book by name
{
	system("cls");
	int temp;
	string name;
	cout << "Please input the name that you want to find: " << endl;
	cin >> name;
	system("cls");
	cout << "This is the list of all the book that name contains string \"" << name << "\" :" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << "|       ISBN       |            Name           |   Category   | Quantity |  Unit Price  |" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	for (size_t i = 0; i < lib.BookArray.size(); i++) // Output each book information
		if (findByName(lib.BookArray[i].GetName(), name)) 
			cout << "|" << setw(18) << lib.BookArray[i].GetIsbn() << "|" <<  setw(27) << lib.BookArray[i].GetName() << "|" << setw(14) << lib.BookArray[i].GetCategoryName()<<  "|" 
				<<  setw(10) << lib.BookArray[i].GetNumber() << "|"<<  setw(14) << setiosflags(ios::fixed) << setprecision(2) <<lib.BookArray[i].GetPrice()  << "|" << endl;
	
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << endl;
	
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
				doc << "<!DOCTYPE html><html><head><title>Departmental Store Management System</title><style>td{border: solid 2px #ddd;}tr:hover{background:#ddd;}</style></head><body><h2>Books List</h2><table><tr>	<td>ISBN</td> <td>Book name</td> <td>Category&nbsp;</td> <td>Quantity&nbsp;</td>	<td>Unit price&nbsp;</td>	<td>Information</td></tr> " << endl;

				for (size_t i = 0; i < lib.BookArray.size(); i++)
					if (findByName(lib.BookArray[i].GetName(), name)) 
						doc << "<tr>" << "<td>" << lib.BookArray[i].GetIsbn() << "&nbsp;" << "</td>" << "<td>" << lib.BookArray[i].GetName() << "&nbsp;" << "</td>" << "<td>"<< lib.BookArray[i].GetCategoryName() << "&nbsp;" << "</td>" << "<td>" << lib.BookArray[i].GetNumber() << "</td>" << "<td>" << lib.BookArray[i].GetPrice() << "</td>" << "<td>" << lib.BookArray[i].GetInformation() << "&nbsp;" << "</td>" << "</tr>";
				doc << "</table></body></html>";
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

void User::BookInfor() // See more information of one book
{
	system("cls");
	string temp, isbn;
	cout << "Please input the ISBN number of the book that you want to find: " << endl;
	cin >> isbn;
	for (size_t i = 0; i < lib.BookArray.size(); i++)
		if (lib.BookArray[i].GetIsbn() == isbn ) // If exist, list its detail information
		{ 
			system("cls");
			cout << "Detail information of the book with ISBN number " << isbn << " : " << endl;
			cout << "Name			: " << lib.BookArray[i].GetName() << endl;
			cout << "Author			: " << lib.BookArray[i].GetAuthor() << endl;
			cout << "Number			: " << lib.BookArray[i].GetNumber() << endl;  
			cout << "Category		: " << lib.BookArray[i].GetCategoryName() << endl;
			cout << "Price			: " << setiosflags(ios::fixed) << setprecision(2) << lib.BookArray[i].GetPrice() << endl;  
			cout << "Information		: " << lib.BookArray[i].GetInformation() << endl;
			cout << endl;
			cout << "Input 0 to exit" << endl;
			cin >> temp;
			while (temp != "0")
				cin >> temp;
			return;
		}
	cout << "Not found this book! " << endl;
	Sleep(1000);
}

void User::ChangePsw() // User choose to change his or her password
{
	system("cls");
	string temp, password;
	cout << "Please input the new password that you want: " << endl;
	cin >> password;
	cout << "Please repeat it: " << endl;
	cin >> temp;
	if (temp != password) // If two input are not match then exit
	{
		cout << "Two password doesn't match!! Change password failed... " << endl;
		Sleep(1500);
		return;
	} 
	else 
	{
		for (size_t i = 0; i < lib.BookArray.size(); i++)
			if (lib.UserArray[i].GetUsername() == account )
				lib.UserArray[i].SetPassword(password); // Change password
		cout << "Password change successfully !" << endl;
		rec.UserLog(account, account, "psw", 0); // Update UserLog.txt with "psw" operation
		PrintUserArray(); // Output user information to User.txt
		Sleep(2000);
	}
}

void User::LoadUser() // Load the user's vip level
{
	SetUsername(lib.UserArray[user_index].GetUsername());
	SetPassword(lib.UserArray[user_index].GetPassword());
	SetStatus(lib.UserArray[user_index].GetStatus());
	SetVip(lib.UserArray[user_index].GetVip());
}