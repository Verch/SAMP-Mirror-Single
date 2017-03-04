#pragma once
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>

#include <functional>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>

#include "VehicleManager.h"
#include "PlayerManager.h"
#include "EventManager.h"
#include "PackageType.h"
#include "MyUtiles.h"
#include "compute.h"
#include "sender.h"




class c_Client
{
public:
	c_Client(boost::asio::ip::udp::endpoint& ep, boost::posix_time::ptime ping);

public:
	boost::asio::ip::udp::endpoint	m_ep;
	boost::posix_time::ptime m_last_ping;

	cPed m_PlayerActor;
private:
};




class c_DataBaseClient_map
{

public:

	std::shared_ptr	<c_Compute> m_ComputeObj;

	std::shared_ptr	<Sender> m_sender;

	std::shared_ptr	<c_VehicleManager> m_VehManager;

	std::shared_ptr	<c_PlayerManager> m_Player_Manager;
	 
public:
	std::map <int, c_Client> m_Client_map;

public:
	c_DataBaseClient_map();
	~c_DataBaseClient_map();

	void refresh_ip_List(boost::asio::ip::udp::endpoint &ep); // refresh ping
	void closeSocket_map(int port);
	bool OfflineUser(std::map <int, c_Client>::iterator it);
	void kickOfflineUser();

	bool refreshPlayer(cPed);

	void printMapPlayer();

	bool GameWorldClientInit(int ID);

	cPed getPlayerID(int ID);

	void updateEvent();

	void deltest();

private:

	void printPlayerID(std::map <int, c_Client>::iterator it);

	//-------------------------------------------------------------------
	// class c_EventManager
public:
	void addEventVehiclePossitionsControl(c_Vehicle vehilce);
	void sendEventEveryClient();

private:
	bool isPlayerIDdistanceSeeEvent(cPed &PlayerIDActor, c_Event &Event);

	void printEvent(std::vector<c_Event> Event, int index);
	void printMatrixEvent();
private:
	std::vector<c_Event> m_Event;
	void addEvent(c_Event GameEvent);
	int getCountEvent();
	//-----------------------------------------------------------------------
public:
	void printStat();

	unsigned int m_countPackage;
};
	 


//
//
//std::shared_ptr	<c_DataBaseClient_map> m_DataBase;
//
//std::shared_ptr	<Sender> m_sender;



/*struct c_Client
{
c_Client(boost::asio::ip::udp::endpoint& _ep)
: ep(_ep)
{
}

boost::asio::ip::udp::endpoint	ep;
boost::posix_time::ptime		last_ping;
bool initGameWorld = false;

c_Player PayerActor;
};*/
