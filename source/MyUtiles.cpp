

#include "MyUtiles.h"


c_MyUtiles::c_MyUtiles()
{
	//std::cout << "c_MyUtiles create!" << "\n";
}

c_MyUtiles::~c_MyUtiles()
{
	//std::cout << "c_MyUtiles Destroy!" << "\n";
}

  
std::string c_MyUtiles::IntToHEX(int Value)
{
	std::string tmpStr((char*)&Value, 4);
	return tmpStr;
}



std::string c_MyUtiles::floatToHEX(float Value)
{
	std::string tmpStr((char*)&Value, 4);
	return tmpStr;
} 






