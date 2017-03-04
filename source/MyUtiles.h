#ifndef C_MYUTILES_H
#define C_MYUTILES_H 

#include <string>
#include <iostream>


class c_MyUtiles
{

public:
	c_MyUtiles();
	~c_MyUtiles();
	 
	std::string IntToHEX(int);
	std::string floatToHEX(float);
	 
	std::string unsignetIntToHEX(unsigned int Val);

private:

};
 

std::string  getMeDirectory();

void Log(const char *fmt, ...);


#endif  