////#pragma once 
////#include "GameLogic.h"
////
////
////
////Game_setting::Game_setting(float stream_distance)
////	: STREAM_DISTANCE(stream_distance){
////}
////
////
////cGameLogic::cGameLogic(Game_setting GameSetting) : m_GameSetting(GameSetting)
////{
////	std::cout << "[GameLogic::GameLogic()] create!" << "\n";
////	m_Veh_Manager = std::make_shared<c_VehicleManager>();
////	m_Player_Manager = std::make_shared<c_PlayerManager>();
////	m_ComputeObj = std::make_shared< c_Compute >();
////
////	 
////}
////
////void cGameLogic::createPlayer(std::stringstream& byteArr, int sizeRecovByte, int ByClient)
////{
////	std::cout << "[cGameLogic::createPlayer]" << "\t";
////
////	if (sizeRecovByte != 24)
////		return;
////
////	std::cout << "try" << "\n";
////	float unBoxInterior = 0;
////	float unBox_xPos = 0;
////	float unBox_yPos = 0;
////	float unBox_zPos = 0;
////
////	byteArr.read((char*)&unBox_xPos, 4);
////	byteArr.read((char*)&unBox_yPos, 4);
////	byteArr.read((char*)&unBox_zPos, 4);
////	byteArr.read((char*)&unBoxInterior, 4);
////
////	m_Player_Manager->refresh_Player_map(ByClient, unBox_xPos, unBox_yPos, unBox_zPos, unBoxInterior);
////}
////
////
////
////
////void cGameLogic::unBox_want_Possitions_for_Car_Spawn(std::stringstream& byteArr, int sizeRecovByte, int ByClient)
////{
////	std::cout << "[cGameLogic::unBox_want_Possitions_for_Car_Spawn]" << "\t";
////	if (sizeRecovByte != 32) // 8 prms
////		return;
////
////	std::cout << "Try" << "\n";
////
////	float unBox_model = 0;
////	float unBox_xPos = 0;
////	float unBox_yPos = 0;
////	float unBox_zPos = 0;
////	float unBox_angle = 0;
////	float unBox_speed = 0;
////
////
////	byteArr.read((char*)&unBox_model, 4);
////	byteArr.read((char*)&unBox_xPos, 4);
////	byteArr.read((char*)&unBox_yPos, 4);
////	byteArr.read((char*)&unBox_zPos, 4);
////
////	byteArr.read((char*)&unBox_angle, 4);
////	byteArr.read((char*)&unBox_speed, 4);
////
////
////	possitions posCarSpawn(unBox_xPos, unBox_yPos, unBox_zPos);
////
////	possitions posClient = m_Player_Manager->getPlayerPossitions(ByClient);
////
////	if (m_ComputeObj->DistanceStreamSee(posCarSpawn, posClient) < m_GameSetting.STREAM_DISTANCE )
////	{
////		float ServIDCar = (float)m_Veh_Manager->m_Serv_id_Veh_List->getServerId();
////	}
////		
////
////	 
////}
////
////
////void cGameLogic::string_input_prms(std::stringstream& byteArr, int sizeRecovByte, int ByClient)
////{
////	std::cout << "[cGameLogic::string_input_prms]" << "\n";
////	if (sizeRecovByte > 256)
////		return;
////
////	char buf[256];
////
////	byteArr.read(buf, sizeRecovByte - 8);
////
////	std::string cmd(buf, sizeRecovByte - 8);
////
////	std::cout << "\n\n Admin commands = " << cmd << "\n\n";
////
////	if (cmd.find("print_db_player_info") == 0)
////		m_Player_Manager->print_data_base();
////
////}
////
////
////void cGameLogic::parsing_package(const std::string& msg, int ByClient)
////{
////	unsigned int unBox_clientPassport = 0; // not reliz
////	float unBox_design = 0;
////
////	if (msg.length() >= 8) // clientPasport + design = 8 (bytes)
////	{
////		std::stringstream byteArr(msg);
////
////		byteArr.read((char*)&unBox_clientPassport, 4);
////		byteArr.read((char*)&unBox_design, 4);
////
////		printf("unBox_clientPassport = %d unBox_design = %d", unBox_clientPassport, unBox_design);
////
////
////		switch ((int)unBox_design)
////		{
////		case -18:
////			string_input_prms(byteArr, msg.size(), ByClient);
////			break;
////
////		case  2:
////			break;
////		case  3:
////			break;
////		case  4:
////			break;
////		case  5:
////			break;
////		case  6:
////			break;
////
////		case 7:
////			createPlayer(byteArr, msg.size(), ByClient);
////			break;
////
////		case 8:
////			unBox_want_Possitions_for_Car_Spawn(byteArr, msg.size(), ByClient);
////			break;
////
////		default:
////			break;
////		}
////	}
////}
////
////std::string cGameLogic::createAnswerForClient()
////{
////	return "UnKnow Answer";
////}
////
////
//////std::string cGameLogic::retNewServerCarID(std::stringstream& byteArr, int ByClient)
//////{
//////	float fDesign = 666;
//////
//////	float servCarID = (float)m_Veh_Manager->m_Serv_id_Veh_List->getServerId();
//////
//////	c_MyUtiles myUtites;
//////
//////	std::string package = myUtites.floatToHEX(fDesign) + myUtites.floatToHEX(servCarID);
//////
//////	return package;
//////}
//////
//////std::string cGameLogic::retInfoCarByServId(std::stringstream& byteArr, int ByClient)
//////{
//////	std::string answer("Unknow Answer");
//////	return answer;
//////}
////
////
////void cGameLogic::printSetting()
////{
////	std::cout << "[cGameLogic::printSetting()]" << "\n";
////	std::cout << "m_GameSetting.STREAM_DISTANCE = " << m_GameSetting.STREAM_DISTANCE << "\n";
////}
////
////
//////
//////std::string cUDP_Server::CreateAnswerForClient(const std::string& msg)
//////{
//////	std::string answer("Unknow Answer");
//////
//////	unsigned int	unBox_clientPassport = 0; // not reliz
//////	float			unBox_design = 0;
//////	float			unBox_want_ModelCar = 0;
//////	float 			unBox_xPos = 0;
//////	float 			unBox_yPos = 0;
//////	float 			unBox_zPos = 0;
//////	float			unBoxInterior = 0;
//////	//void sendSelfPositions(float design, float interior, float x, float y, float z);
//////
//////	if (msg.length() >= 8) // clientPasport + design = 8 (bytes)
//////	{
//////		if (msg.length() == 24) // count prms = 6
//////		{
//////			std::stringstream byteArr(msg);
//////
//////			byteArr.read((char*)&unBox_clientPassport, 4);
//////			byteArr.read((char*)&unBox_design, 4);
//////
//////			switch ((int)unBox_design)
//////			{
//////
//////			case  2:
//////				break;
//////
//////			case 7:
//////				void refresh_PlayerPositions(std::stringstream& byteArr);
//////				break;
//////
//////			default:
//////				break;
//////			}
//////
//////			byteArr.read((char*)&unBox_want_ModelCar, 4);
//////			byteArr.read((char*)&unBox_xPos, 4);
//////			byteArr.read((char*)&unBox_yPos, 4);
//////			byteArr.read((char*)&unBox_zPos, 4);
//////
//////			//print Input Package
//////			printf("\n[cUDP_Server::CreateAnswerForClient] Decompose Package"
//////				" \n\tclientPassport = %d"
//////				" \n\tdesign = %f"
//////				" \n\tmodelCar = %f"
//////				" \n\tx = %f \n\ty = %f \n\tz = %f\n"
//////				"------------------------------\n"
//////				, unBox_clientPassport
//////				, unBox_design
//////				, unBox_want_ModelCar
//////				, unBox_xPos
//////				, unBox_yPos
//////				, unBox_zPos
//////				);
//////
//////			// control valid data
//////			if (unBox_want_ModelCar >= 400 && unBox_want_ModelCar <= 602)
//////			{
//////				// get server info database
//////				int servCarID = m_Game_db_Car->getServerId();
//////
//////				// refresh data vase
//////				m_Veh_Manager->refresh_vehicle_map(
//////					servCarID
//////					, (int)unBox_want_ModelCar
//////					, unBox_xPos
//////					, unBox_yPos
//////					, unBox_zPos
//////					);
//////				c_MyUtiles myUtites;
//////
//////				std::string package = myUtites.floatToHEX(unBox_design) + m_Veh_Manager->getHexInfoCarID(servCarID);
//////				return package;
//////			}
//////		}
//////	}
//////	return answer;
//////}
//////
