# Book Works Bookstore Chain Management System

#### All files :
____	
	|.h
	|----
	|	|--admin.h
	|	|--book.h
	|	|--customer.h
	|	|--library.h
	|	|--log.h
	|	|--md5
	|	|--password.h
	|	|--staff.h
	|	|--store.h
	|	|--storelist.h
	|	|--user.h
	|
	|.cpp
	|----
	|	|--admin.cpp
	|	|--customer.cpp
	|	|--library.cpp
	|	|--log.cpp
	|	|--main.cpp
	|	|--md5.cpp
	|	|--password.cpp
	|	|--staff.cpp
	|	|--storelist.cpp
	|	|--user.cpp
	|
	|.txt
	|----
	|	|--CheckComment.txt
	|	|--CheckShortBook.txt
	|	|--Comments.txt
	|	|--ShortOfBook.txt
	|	|--UserLog.txt
	|
	|.csv
	|----
	|	|--Store.csv
	|	|--User.csv
	|
	|\
	|----
	|	|--Store1
	|	|--------
	|	|		|--Book.csv
	|	|		|--BookLog.txt
	|	|		|--Cash.txt
	|	|		|--CashLog.txt
	|	|--Store2
	|	|--------
	|	|		|--Book.csv
	|	|		|--BookLog.txt
	|	|		|--Cash.txt
	|	|		|--CashLog.txt
	|	|--Store3
	|	|--------
	|	|		|--Book.csv
	|	|		|--BookLog.txt
	|	|		|--Cash.txt
	|	|		|--CashLog.txt
	|
	|.exe
	|----
	|	|--Book Works.exe
	|
	|.md
	|----
	|	|--README.md
	|
	|

---

#### How to use those files to run the system?
Option 1:
	double click the "Book Works.exe" (make sure the "Book Works.exe" is in the same folder with all the source code, .txt and .csv files)

Option 2:
	1) Open all the .cpp and .h files in Visual Studio, compile and run them.
	2) The main file is "main.cpp".

---

#### Classes Construction :
 
**User Classes :**

	1) User 	:	Fundamental class with basic authority like list book, check book information or change password. Also with some attributes like username, password, status and vip level.
	2) Customer : 	Inherit from "User", add new ability like buy book, refund and leave comment. 
	3) Staff	:   Inherit from "User", add new ability like add new book, delete book, lookup net profit or change book's information.
	4) Admin	:	Inherit from "Staff", add new ability like add new user, delete user, list users or change user's information.

**Other Classes :**

	5) Book 	 : 	Fundamental class with book's information and some basic book management function.
	6) Store     :  This class has some attributes of each bookstore in the chain and some functions to access and modify these attributes.
	7) Storelist :	This class can create a list to store all the bookstores of the chain and has some functions to load the store's data.
	8) Log 		 :	This class has some functions used to log all the executed operation to text file, record the shortage of books and customers' complaint (advice).
	9) Library   :	This class is a container to store all the information of books, users and cash, also it have some functions that can load and modify the database.
	10) Password :	This class has some functions have connection with password disposal.
	11) MD5 	 :	This class can use the MD5 algorithm to encrypt the users' password for security.

-----------------------------------------------------------------------------------------

#### Detail Information:

Book :
	name			the book's name
	isbn			the book's ISBN number, it's the ID of the book
	author			the author of the book
	quantity		the quantity of the book in the store
	category		the book's category number. 1 for "Art", 2 for "Engineering", and 3 for "Science"
	price			the sells price of one book
	information		the more detail information about this book
	num_of_sale		the number indicating how many copies of this book were sold so far

User/Customer/Staff/Admin :
	username		the user's username, it's unique  
	password		the user's password 
	status			the user's status, 1 for Admin, 2 for Staff, 3 for Customer, 0 for deleted (not exist)
	vip				the user's vip level, 0 for non-vip(no discount), 1 for vip(10% discount), 2 for vvip(20% discount) and 3 for vvvip(30% discount)

Library :
	BookArray		store all the books' information imported from Book.txt
	UserArray		store all the students' information imported from User.txt
	income			the total income of the store so far
	outcome			the total outcome of the store so far

Store :
	name			the code of the bookstore e.g. Store1, Stor2 and Store3
	storeName		the name of the bookstore e.g. Shanghai Store, Hong Kong Store
	address			the address of the store
	bookAddress		the address of the Book.csv of this store
	cashAddress		the address of the Cash.txt of this store
	bookLogAddress	the address of the BookLog.txt of this store
	cashLogAddress	the address of the CashLog.txt of this store

-----------------------------------------------------------------------------------------

#### "Killer" feature :

1) When a book's quantity is less than 10, send a emergent message to the manager (admin)
2) The customer can leave comment or advice for the store and the system will notify the manager (admin) immediately
3) Keep track of the books' sales situation, find out the best seller and the worst seller and help the manager to make business strategy
4) The manager can manage different bookstores of the chain using the same system, the customer can buy books from all the bookstores of the chain using the system.
5) etc...

-----------------------------------------------------------------------------------------
