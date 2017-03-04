#pragma once 
#include "DataBase.h"
#include "dataAnswer.h"
#include <sstream>



c_Client::c_Client(boost::asio::ip::udp::endpoint& ep,
	boost::posix_time::ptime ping)
	: m_ep(ep)
	, m_last_ping(ping)
{

}


c_DataBaseClient_map::c_DataBaseClient_map()
{
	m_ComputeObj = std::make_shared <c_Compute>();
	//std::cout << "c_DataBaseClient_map() create" << "\n";

	m_sender = std::make_shared <Sender>();

	m_VehManager = std::make_shared <c_VehicleManager>();

	m_Player_Manager = std::make_shared <c_PlayerManager>();

	m_countPackage = 0;

	/*m_setting = std::make_shared <Game_setting>(50.0f);

	m_ComputeObj = std::make_shared <c_Compute>();

	m_DataBase = std::make_shared <c_DataBaseClient_map>();

	m_sender = std::make_shared <Sender>();*/
}

c_DataBaseClient_map::~c_DataBaseClient_map()
{
	//std::cout << "~c_DataBaseClient_map() destroy" << "\n";
}

bool c_DataBaseClient_map::refreshPlayer(cPed newInfoPlayerActor)
{
	int keyPort = newInfoPlayerActor.m_iKeyID;

	auto it = std::find_if(m_Client_map.begin(), m_Client_map.end(),
		[&keyPort](const std::pair<int, c_Client> &p)
	{
		return p.first == keyPort;
	});

	if (it != m_Client_map.end())
	{		// new info by c_Client	
		(*it).second.m_PlayerActor = newInfoPlayerActor;

		std::cout << "updatePossitions" << " ";
		printPlayerID(it);

		return true;
	}
	else
	{		// register 
		std::cout << "[c_DataBaseClient_map::refreshPlayerid] Ahtung Player not found." << "\n";
		return false;
	}
}

void c_DataBaseClient_map::refresh_ip_List(boost::asio::ip::udp::endpoint &ep)
{
	int keyPort = ep.port();
	auto it = std::find_if(m_Client_map.begin(), m_Client_map.end(),
		[&keyPort](const std::pair<int, c_Client> &p)
	{
		return p.first == keyPort;
	});

	if (it != m_Client_map.end())
	{		// new info by c_Client	
		std::cout << " update ping" << " ";
		(*it).second.m_last_ping = boost::posix_time::microsec_clock::local_time();	// update Ping
	}
	else
	{		// register 
		c_Client tmp(ep, boost::posix_time::microsec_clock::local_time());	// for box

		m_Client_map.insert(std::pair<int, c_Client>(keyPort, tmp));

		std::cout << "[c_DataBaseClient_map::refresh_ip_List] connect " << ep.address().to_string() << ":" << keyPort << std::endl;
	}
}

void c_DataBaseClient_map::closeSocket_map(int keyPort)
{
	auto it = std::find_if(m_Client_map.begin(),
		m_Client_map.end(), [&keyPort]
		(const std::pair<int, struct c_Client > &p)
	{
		return p.first == keyPort;
	});

	if (it != m_Client_map.end())
	{
		std::cout << "[c_DataBaseClient_map::closeSocket_map] Connection last" << (*it).second.m_ep.port() << " удален из очереди" << "\n";
		m_Client_map.erase(it);
	}
	else
	{
		std::cout << "[void c_DataBaseClient_map::closeSocket_map] AHTUNG" << "\n";
	}
}

bool c_DataBaseClient_map::OfflineUser(std::map <int, c_Client>::iterator it)
{
	if (it != m_Client_map.end())
	{
		using namespace boost::posix_time;	//for millisec
		ptime now = microsec_clock::local_time();

		long long ms = (now - (*it).second.m_last_ping).total_milliseconds();

		if (ms > 5000)
		{
			//std::cout << "[c_DataBaseClient_map::isKickOfflineUser]" << "\n";
			//closeSocket_map((*it).second.ep.port());
			return true;
		}
	}
	return false;
}

void c_DataBaseClient_map::kickOfflineUser()
{
	using namespace boost::posix_time;	//for millisec

	for (auto it = m_Client_map.begin();
		it != m_Client_map.end(); ++it)
	{
		ptime now = microsec_clock::local_time();
		long long ms = (now - (*it).second.m_last_ping).total_milliseconds();
		if (ms > 5000)
		{
			closeSocket_map((*it).second.m_ep.port());
			break;	// lol ? control diapozon iterraot
		}
	}
}

void c_DataBaseClient_map::printMapPlayer()
{
	//system("cls");
	std::cout << "[void c_DataBaseClient_map] \t Online:" << "\n";
	for (auto it = m_Client_map.begin(); it != m_Client_map.end(); ++it)
	{
		printPlayerID(it);
		std::cout << std::endl;
	}
}

void c_DataBaseClient_map::printPlayerID(std::map <int, c_Client>::iterator it)
{
	std::cout << " " << it->second.m_ep.address() << ":" << it->second.m_ep.port() << " ";
	std::cout << " key = " << it->second.m_PlayerActor.m_iKeyID << " ";
	std::cout << " x = " << it->second.m_PlayerActor.m_fX << " ";
	std::cout << " y = " << it->second.m_PlayerActor.m_fY << " ";
	std::cout << " z = " << it->second.m_PlayerActor.m_fZ << " ";
	std::cout << " fInterior = " << it->second.m_PlayerActor.m_fInterior << " ";
	std::cout << " speed = " << it->second.m_PlayerActor.m_fSpeed << "";

}

bool c_DataBaseClient_map::GameWorldClientInit(int ID)
{
	auto it = std::find_if(m_Client_map.begin(),
		m_Client_map.end(), [&ID]
		(const std::pair<int, struct c_Client > &p)
	{
		return p.first == ID;
	});

	if (it != m_Client_map.end())
	{
		return it->second.m_PlayerActor.m_bInitPlayerPos;
	}
	return false;
}

cPed c_DataBaseClient_map::getPlayerID(int ID)
{
	auto it = std::find_if(m_Client_map.begin(),
		m_Client_map.end(), [&ID]
		(const std::pair<int, struct c_Client > &p)
	{
		return p.first == ID;
	});

	if (it != m_Client_map.end())
	{
		return it->second.m_PlayerActor;
	}
}

void c_DataBaseClient_map::updateEvent()
{
	std::cout << "\n[void c_DataBaseClient_map::updateEvent]	" << " \n";

	std::string msg = "";


	if (m_Event.empty())
		return;

	if (m_Client_map.empty())
		return;

	c_MyUtiles Tohex;
	c_DataAnswer answer;

	printStat();




	for (int i = 0; i < m_Event.size(); i++)
	{
		for (auto it = m_Client_map.begin(); it != m_Client_map.end(); ++it)
		{

			if (OfflineUser(it))
			{
				//std::cout << " удали из очереди трупа (id port " << it->second.m_ep.port() << ")\n";
				continue;
			}

			cPed currClient = it->second.m_PlayerActor;

			if (isPlayerIDdistanceSeeEvent(currClient, m_Event[i]))
			{

				// init dim Answer for client
				//-------------------------------------------------------------------------------------------------
				switch (m_Event[i].m_iType)
				{

				case eTypeGameObject::VEHICLE:

					msg = answer.createStr(
						(float)ePackageRecovSend::RPC_SERVER_VEHICLE_CAR_POSSITIONS
						, Tohex.unsignetIntToHEX(m_countPackage)
						, m_VehManager->getHexInfoCarID(m_Event[i].m_AttachToID));
					break;
					 
				default:
					std::cout << "waring unknown game type object" << "\n";
					break;
				}
				m_countPackage++;
				//------------------------------------------------------------------------------------------------

				  
				m_sender->send_for(it->second.m_ep, msg);

				//std::cout << "Event[" << i << "] size = " << msg.length() << " for "<< it->second.m_ep.address() << ":" << it->second.m_ep.port() << "\n";
			}
			else
			{
				Log("[c_DataBaseClient_map::updateEvent] bad distance with event[%d] and playerKeyPort %d",
					i, it->second.m_ep.port());
			}

		}
	}
}


void c_DataBaseClient_map::deltest()
{

	/*c_MyUtiles Tohex;

	std::string msg;

	msg = Tohex.floatToHEX(2.0f);

	std::stringstream byteArr(msg);

	float eba;

	byteArr.read((char*)&eba, 4);

	std::cout << "\neba =" << eba << "\n";*/
}

//
//void c_DataBaseClient_map::send_all(const std::string & msg)
//{
//	std::cout << "[void c_DataBaseClient_map::send_all]" << "\n";
//
//	/*for (auto it = m_Client_map.begin(); it != m_Client_map.end(); ++it)
//	{ 
//		std::cout << "send for " << it->second.ep.address() << ":" << it->second.ep.port() << "\n";
//
//		boost::system::error_code ignored_error;
//		socket_.send_to(boost::asio::buffer(msg), it->second.ep, 0, ignored_error);
//	}*/
//}

////
////void c_Network::chekClientTimeOut()
////{
////	for (auto it = m_DataBasa->m_Client_map.begin();
////		it != m_DataBasa->m_Client_map.end(); ++it)
////	{
////		ptime now = microsec_clock::local_time();
////		long long ms = (now - (*it).second.last_ping).total_milliseconds();
////		if (ms > 5000)
////		{
////			m_DataBasa->closeSocket_map((*it).second.ep.port());
////			
////			m_GameLogic->m_Player_Manager->remove_Player_Game_Info((*it).second.ep.port());
////
////			break;	// lol ? 
////		}
////	}
////}
//==================================================================================================

//сClient_GameInfo::сClient_GameInfo(float  fPos_x, float fPos_y, float fPos_z, float fInterior)
//	:m_fPos_x(fPos_x), m_fPos_y(fPos_y), m_fPos_z(fPos_z), m_fInterior(fInterior)
//{
//}




void c_DataBaseClient_map::addEvent(c_Event GameEvent)
{
	m_Event.push_back(GameEvent);
}

int c_DataBaseClient_map::getCountEvent()
{
	if (m_Event.empty())
		return 0;

	return m_Event.size();
}


void c_DataBaseClient_map::printStat()
{
	//system("cls");
	std::string stat = "[c_DataBaseClient_map::printStat()]\n"
		"Servet Data Base stat: \\"
		"\nCount Vehicle: " + std::to_string(m_VehManager->getCountVehicle())
		+ "\nCount Event: " + std::to_string(getCountEvent())
		+ "\nCount Client: " + std::to_string(m_Player_Manager->getCountPlayerActor());
}

void c_DataBaseClient_map::printMatrixEvent()
{
	for (int i = 0; i < m_Event.size(); i++)
	{
		printEvent(m_Event, i);
	}
}

void c_DataBaseClient_map::printEvent(std::vector<c_Event> Event, int index)
{
	std::cout << "" << Event[index].m_fPosX << "\n";
	std::cout << "" << Event[index].m_fPosY << "\n";
	std::cout << "" << Event[index].m_fPosZ << "\n";
}

void c_DataBaseClient_map::addEventVehiclePossitionsControl(c_Vehicle vehilce)
{
	c_Event Vehicle(eTypeGameObject::VEHICLE, vehilce.m_fServerID, vehilce.m_fX, vehilce.m_fY, vehilce.m_fZ);

	addEvent(Vehicle);
}

bool c_DataBaseClient_map::isPlayerIDdistanceSeeEvent(cPed &PlayerIDActor, c_Event &Event)
{
	float distance = m_ComputeObj->Distance(PlayerIDActor, Event);
	if (distance < 166.6f)
		return true;
	return false;
}



