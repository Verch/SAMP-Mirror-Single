#pragma once
 
#include <vector>
#include "MyUtiles.h"

struct cPointObject
{
	float posX;
	float posY;
	float posZ;
	float angle;
};

struct Point_Struct_Str
{
	std::string posX_4byte;
	std::string posY_4byte;
	std::string posZ_4byte;
	std::string angle_4byte;
};
 
class c_DataAnswerManager
{
public:

	Point_Struct_Str init(cPointObject inputFloatStruct);

	void initArr(Point_Struct_Str objectStr, size_t IndexArray);

private:
	std::vector <Point_Struct_Str> m_data;
};

class c_DataAnswer{
public:
	std::string createStr(float fDesign, const std::string HexNumberPackage, const std::string Hex);
};






class CDataAnswerManager
{
public: 

};




