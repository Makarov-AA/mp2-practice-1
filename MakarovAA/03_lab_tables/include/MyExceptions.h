#ifndef MY_EXCEPTION
#define MY_EXCEPTION

#include <iostream>
#include <string>
#include <exception>

class MyException : public std::exception {
private:
	std::string msg;
public:
	MyException(std::string iMsg) : msg(iMsg) {}
	const char* what() const {
		return msg.c_str();
	}
};

#endif
