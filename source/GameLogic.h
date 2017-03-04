////#pragma once
////
////#include "GameObject_List.h"
////#include "VehicleManager.h"
////#include "PlayerManager.h"
////#include "MyUtiles.h"
////#include "compute.h"
////
////#include <boost/shared_ptr.hpp>
////
////#include <functional>
////#include <algorithm>
////#include <iostream>
////#include <sstream>
////#include <string>
////#include <math.h>
////
////struct Game_setting
////{
////	Game_setting(float stream_distance);
////	float STREAM_DISTANCE;
////};
//
//class cGameLogic
//{
//public:
//	cGameLogic();
//
//
//	// main funcs
//	std::string createAnswerForClient();
//	void parsing_package(const std::string & package, int ByClient);
//	 
//
//	void printSetting();
//	bool isPosittionsForCarSpawnTry();
//	void string_input_prms(std::stringstream& byteArr, int sizeRecovByte, int ByClient);
//	void createPlayer(std::stringstream& byteArr, int messagaSize, int ByClient);
//	void unBox_want_Possitions_for_Car_Spawn(std::stringstream& byteArr, int messagaSize, int ByClient);
//	std::string retNewServerCarID(std::stringstream& byteArr, int messagaSize, int ByClient);
//	std::string retInfoCarByServId(std::stringstream& byteArr, int messagaSize, int ByClient);
//
//	  
//public:
//	/*std::shared_ptr	<c_PlayerManager> m_Player_Manager;
//	std::shared_ptr	<c_VehicleManager> m_Veh_Manager;
//	std::shared_ptr	<c_Compute> m_ComputeObj;*/
//	
//private:
//	Game_setting m_GameSetting;
//};
////
////
////
////
