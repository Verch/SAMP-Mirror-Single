#include "dataAnswer.h"
#include "MyUtiles.h"

#include <iostream> 
#include <sstream>
 
Point_Struct_Str c_DataAnswerManager::init(cPointObject inputFloatStruct)
{
	c_MyUtiles MyHexFuncs;
	Point_Struct_Str cPointObjFloat;

	cPointObjFloat.posX_4byte = MyHexFuncs.floatToHEX(inputFloatStruct.posX);
	cPointObjFloat.posY_4byte = MyHexFuncs.floatToHEX(inputFloatStruct.posX);
	cPointObjFloat.posZ_4byte = MyHexFuncs.floatToHEX(inputFloatStruct.posX);
	cPointObjFloat.angle_4byte = MyHexFuncs.floatToHEX(inputFloatStruct.angle);

	return cPointObjFloat;
}

void c_DataAnswerManager::initArr(Point_Struct_Str objectStr, size_t IndexArray)
{
	if (IndexArray < m_data.size() - 1 && IndexArray >= 0)
		m_data[IndexArray] = objectStr;
}
  
std::string c_DataAnswer::createStr(float fDesign, const std::string HexNumberPackage, const std::string Hex)
{
	c_MyUtiles toHex;
	return toHex.floatToHEX(fDesign) + HexNumberPackage +  Hex;
}
