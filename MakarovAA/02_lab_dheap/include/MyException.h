#ifndef _MY_EXCEPTION_
#define _MY_EXCEPTION_

#include <exception>
#include <string>

class MyException : public std::exception {
private:
	std::string errorMsg;

public:
	MyException(const std::string i_msg) : errorMsg(i_msg) {};
	const char* what() const {
		return errorMsg.c_str();
	}
};

#endif
