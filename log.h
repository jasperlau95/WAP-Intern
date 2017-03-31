#ifndef LOG_H
#define LOG_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Log {
public:
	void UserLog(string loginname, string username, string operation, int status); // Add new information to UserLog.txt
	void BookLog(string loginname, string bookisbn, string operation, int number); // Add new information to BookLog.txt
	void CashLog(string loginname, string bookisbn, string operation, double money); // Add new information to CashLog.txt
	void CommentLog(string loginname, string comment); // Add new comment to comment.txt
	void ShortOfBookLog(string bookName, string storeName); // Add new short of book reminder to ShortOfBook.txt
	void CheckShortOfBookLog(); 
	void CheckCommentLog();
};

#endif