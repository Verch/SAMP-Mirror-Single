#pragma once

#include "GameObject_List.h"

#include "DataBase.h"

#include "VehicleManager.h"
#include "PlayerManager.h"

#include "PackageType.h"

//#include "EventManager.h"

//#include "MyUtiles.h"
//#include "compute.h"
//#include "sender.h"

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>

#include <functional>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string> 

class CDataAnswerManager;


struct Game_setting
{
	Game_setting(float stream_distance);
	float STREAM_DISTANCE;
};

using namespace boost::posix_time;	//for millisec

class c_Logic
{
public:
	c_Logic();		//c_Logic(Game_setting setting );

	~c_Logic();

public:

public:
	void parsing_package(const std::string & package, boost::asio::ip::udp::endpoint & remote_endpoint);

	void printSpecialAdminInputCmd(std::stringstream& byteArr, int sizeRecovBy, int ByClientRemotePortKey);

	void eventSpawnVehicle(std::stringstream& byteArr, int sizeRecovBy, int byClient);

	void refreshPlayerPossitions(std::stringstream& byteArr, int sizeRecovBy, int byClient);
	 

	void VehicleNewPossitions(std::stringstream& byteArr, int sizeRecovBy, int byClientID);
public:
	std::shared_ptr	<c_DataBaseClient_map> m_DataBase;
	 
	std::shared_ptr	<CDataAnswerManager> m_DataAnswerManager;
	 
private:
	std::shared_ptr	<Game_setting > m_setting;
	 
private:
	unsigned int	m_unBox_u—lientPassport;	 // not reliz
	float			m_unBox_fDesign;
};




/*std::shared_ptr	<c_PlayerManager> m_Player_Manager;

std::shared_ptr	<c_VehicleManager> m_VehManager;*/


//std::shared_ptr	<Sender> m_sender;

//std::shared_ptr	<c_EventManager> m_EventManager;

//std::shared_ptr	<c_Compute> m_ComputeObj;

/*struct c_Client
{
c_Client(boost::asio::ip::udp::endpoint& _ep);

boost::asio::ip::udp::endpoint	ep;
};*/



