#include "console.h";


// Void L O L

void Success(std::string ptr) {
	std::cout << "[ " << termcolor::green << "+" << termcolor::reset << " ] > " << ptr << std::endl;
}

void Warning(std::string ptr) {
	std::cout << "[ " << termcolor::yellow << "!" << termcolor::reset << " ] > " << ptr << std::endl;
}

void Error(std::string ptr) {
	std::cout << "[ " << termcolor::red << "/" << termcolor::reset << " ] > " << ptr << std::endl;
}

void Header() {


	std::cout << termcolor::yellow << R"(
	
			88""Yb Yb  dP  dP""b8    db    Yb  dP 
			88__dP  YbdP  dP   `"   dPYb    YbdP  
			88""Yb   8P   Yb  "88  dP__Yb    8P   
			88oodP  dP     YboodP dP""""Yb  dP


			      https://runesoftware.cc
			   https://discord.gg/runesoftware


	)" << termcolor::reset << std::endl;
}