#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
public:
	// Get different information of Book 
	string GetName() { return name; }
	string GetIsbn() { return isbn; }
	string GetAuthor() { return author; }
	int GetNumber() { return number; }
	int GetCategory() { return category; }
	string GetCategoryName() {return categoryNum2categoryName[category-1]; }
	double GetPrice() { return price; }
	string GetInformation() { return information; }
	int GetNumberOfSale() { return num_of_sale; }

	// Change different information of Book 
	void SetName(string new_name) { name = new_name; }
	void SetIsbn(string new_isbn) { isbn = new_isbn; }
	void SetAuthor(string new_author) { author = new_author; }
	void SetNumber(int new_number) { number = new_number; }
	void SetCategory(int new_category) { category = new_category; }
	void SetPrice(double new_price) { price = new_price; }
	void SetInformation(string new_imfor) { information = new_imfor; }
	void SetNumberOfSale(int new_num_of_sale) {num_of_sale = new_num_of_sale; }

private:
	string name;
	string isbn; // ISBN number
	string author;		
	int number; // The copy number of book
	int category; // The category number
	double price; // Unit-price of book
	string information;	// More commentary of that book
	string categoryNum2categoryName[3] = {"Art", "Engineering", "Science"};
	int num_of_sale; // count the number of sale of this book
};

#endif