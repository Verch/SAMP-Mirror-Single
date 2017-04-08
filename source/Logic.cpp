#pragma once 

#include "Logic.h"
 
#include "dataAnswer.h"
 
Game_setting::Game_setting(float stream_distance)
	: STREAM_DISTANCE(stream_distance)
{
	//std::cout << "[GameLogic::GameLogic()] create!" << "\n";
}

c_Logic::c_Logic()
{
	std::cout << "[c_Logic::c_Logic()]" << "\n";

	m_setting = std::make_shared <Game_setting>(50.0f);

	m_DataBase = std::make_shared <c_DataBaseClient_map>();
	 
	m_DataAnswerManager = std::make_shared <CDataAnswerManager>();

	//m_EventManagerDelegate = std::make_shared <c_EventManager>();
	//m_VehManager = std::make_shared <c_VehicleManager>();
	//m_ComputeObj = std::make_shared <c_Compute>();
	//m_Player_Manager = std::make_shared <c_PlayerManager>();
	//m_sender = std::make_shared <Sender>();
	//m_EventManager = std::make_shared <c_EventManager>(m_DataBase);
}


c_Logic::~c_Logic()
{
	//std::cout << "[c_Logic::~c_Logic()]" << "\n";
}

void c_Logic::parsing_package(const std::string & package, boost::asio::ip::udp::endpoint & remote_endpoint)
{
	std::stringstream byteArr(package);

	byteArr.read((char*)&m_unBox_uСlientPassport, 4);
	byteArr.read((char*)&m_unBox_fDesign, 4);

	switch ((int)m_unBox_fDesign)
	{

	case ePackageRecovSend::ADMINS_CMD:
		printSpecialAdminInputCmd(byteArr, package.length(), remote_endpoint.port());
		break;

	case ePackageRecovSend::RPC_VEHICLE_SPAWN:
		Log("[ePackageRecovSend::CAR_SPAWN]");
		eventSpawnVehicle(byteArr, package.length(), remote_endpoint.port());
		break;


	case ePackageRecovSend::PLAYER_ACTOR_NEW_POSSITIONS:
		// new!
		Log("[ePackageRecovSend::PLAYER_ACTOR_NEW_POSSITIONS]");
		std::cout << "ePackageRecovSend::PLAYER_ACTOR_NEW_POSSITIONS" << " ";
		refreshPlayerPossitions(byteArr, package.length(), remote_endpoint.port());

		//refreshPlayerPossitions(m_EventManagerDelegate, byteArr, package.length(), remote_endpoint.port());

		break;

	default:
		std::cout << "cmd от клиента не распознана " << "\n";
		break;
	}

	std::cout << "" << "\n";
}

void c_Logic::eventSpawnVehicle(std::stringstream& byteArr, int sizeRecovBy, int byClientID)
{
	if (sizeRecovBy != 40/*32*/) //  new ! color 4 + 4
	{
		Log("bad size recovery message SPAWN_CAR");
		return;
	}

	if (!m_DataBase->GameWorldClientInit(byClientID))
	{
		Log("AHTUNG Game World Client NOT Init");
		return;
	}

	int ServIDCar = m_DataBase->m_VehManager->m_servListID->getServerID();

	if (ServIDCar < 0)
	{
		Log("[c_Logic] AHTUNG ServerListCarID empty");
		return;
	}

	// waring, server ID not init
	c_Vehicle want_car = m_DataBase->m_VehManager->createWantCar(byteArr);

	// very important
	want_car.initServerID((float)ServIDCar);

	std::cout << "color_1 = " << want_car.m_fColor_1
		<< "color_2 = " << want_car.m_fColor_2 << "\n";

	if (!m_DataBase->m_VehManager->isVehicleInitCorrect(want_car))
	{
		Log("AHTUNG not correct init vehicle");
		return;
	}

	if (m_DataBase->m_VehManager->regVehicle(want_car))
	{
		std::cout << " ePackageRecovSend::CAR_SPAWN: " << "\t ";

		m_DataBase->addEventVehiclePossitionsControl(want_car);
	}
	else
	{
		Log("[void c_Logic::eventSpawnVehicle] m_DataBase->m_VehManager->regVehicle = false");
	}
}

void c_Logic::printSpecialAdminInputCmd(std::stringstream& byteArr,
	int sizeRecovByte, int ByClientRemotePortKey)
{
	//std::cout << "[c_Logic::printSpecialAdminInputCmd]" << "\t";
	if (sizeRecovByte > 1256)
		return;

	char buf[1256];

	byteArr.read(buf, sizeRecovByte - 8);

	std::string cmd(buf, sizeRecovByte - 8);

	std::cout << "\n\n Admin commands = " << cmd << "\n\n";

	if (cmd.find("print_db_player_info") == 0)
	{
		m_DataBase->printMapPlayer();
		return;
	}

	if (cmd.find("print_stat_db") == 0)
	{
		m_DataBase->printStat();
		return;
	}
}



// до поезда 
void c_Logic::refreshPlayerPossitions(std::stringstream& byteArr, int sizeRecovBy, int byClient)
{
	if (sizeRecovBy != 28)
	{
		std::cout << "[void c_PlayerManager::refreshPlayerActorPos] Add to log bad size msg." << " ";
		return;
	}

	cPed playerActor = m_DataBase->m_Player_Manager->createPlayer(byteArr, sizeRecovBy, byClient);
	 
	m_DataBase->refreshPlayerActor(playerActor);

	//m_DataBase->updateEventPlayerPossitions(playerActor);
}

/*
void c_Logic::refreshPlayerPossitions(std::shared_ptr <c_EventManager> EventManagerDelegate,
std::stringstream& byteArr, int sizeRecovBy, int byClient)
{
if (sizeRecovBy != 28)
{
std::cout << "[void c_PlayerManager::refreshPlayerActorPos] Add to log bad size msg." << " ";
return;
}



cPed playerActor = m_DataBase->m_Player_Manager->createPlayer(byteArr, sizeRecovBy, byClient);


int countEvent = EventManagerDelegate->getCountEvent();
EventManagerDelegate->updateEventPlayerPossitions(playerActor);

m_DataBase->refreshPlayerActor(playerActor);

std::cout << " [c_Logic::refreshPlayerPossitions] [ EventManagerDelegate->getCountEvent() = ]" << countEvent << "\n";
}
*/
