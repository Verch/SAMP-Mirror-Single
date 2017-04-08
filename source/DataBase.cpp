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
	//std::cout << "c_DataBaseClient_map() create" << "\n";

	m_ComputeObj = std::make_shared <c_Compute>();

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
	std::cout << "~c_DataBaseClient_map() destroy" << "\n";
	Log("[c_DataBaseClient_map::~c_DataBaseClient_map()]");
}

std::map <int, c_Client>::iterator c_DataBaseClient_map::getClientByPort(int keyPort)
{
	auto it = std::find_if(m_Client_map.begin(), m_Client_map.end(),
		[&keyPort](const std::pair<int, c_Client> &p)
	{
		return p.first == keyPort;
	});

	//if (it != m_Client_map.end())

	return it;
}

bool c_DataBaseClient_map::refreshPlayerActor(cPed newInfoPlayerActor)
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

		//addEventPlayerActorPossitionsControl(newInfoPlayerActor);

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

bool c_DataBaseClient_map::isOfflineUser(std::map <int, c_Client>::iterator it)
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

			if (isOfflineUser(it))
			{
				//std::cout << " удали из очереди трупа (id port " << it->second.m_ep.port() << ")\n";
				continue;
			}

			cPed currClient = it->second.m_PlayerActor;

			if (isPlayerIDdistanceSeeOtherPlayerID(currClient, m_Event[i]))
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

					// нормально сделай, и нормально будет
				/*case  eTypeGameObject::PLAYER:
					msg = answer.createStr((float)ePackageRecovSend::PLAYER_ACTOR_NEW_POSSITIONS, Tohex.unsignetIntToHEX(m_countPackage), it->second.m_PlayerActor.getHexInfo());
					break;*/

				default:
					std::cout << "waring unknown game type object" << "\n";
					break;
				}
				m_countPackage++;
				//------------------------------------------------------------------------------------------------


				m_sender->send_for(it->second.m_ep, msg);

				std::cout 
					<< "Event[" << i << "]"
					<< " = " << m_Event[i].m_iType
					<< " size = " << msg.length()
					<< " for " << it->second.m_ep.address() << ":" << it->second.m_ep.port() << "\n";
			}
			else
			{
				Log("[c_DataBaseClient_map::updateEvent] bad distance with event[%d] and playerKeyPort %d",
					i, it->second.m_ep.port());
			}

		}
	}
}

std::string c_DataBaseClient_map::SEND_EVENT_PLAYER_ACTOR_POSSITIONS_AND_CreateAnswerForCurrrientEndPointClieent(int KeyPort)
{
	if (m_Client_map.empty())
		return "-1";

	std::map <int, c_Client>::iterator currEndPointPlayer = getClientByPort(KeyPort);

	/*if (currEndPointPlayer == m_Client_map.end())
		return;*/

	cPed ClientPlayerActor = currEndPointPlayer->second.m_PlayerActor;

	std::string msg = "";

	for (auto it = m_Client_map.begin(); it != m_Client_map.end(); ++it)
	{

		if (isOfflineUser(it))
			continue;	//std::cout << " удали из очереди трупа (id port " << it->second.m_ep.port() << ")\n";

		/*if (currEndPointPlayer == it)
			continue;*/

		cPed otherPlayerActor = it->second.m_PlayerActor;

		c_DataAnswer answer;
		c_MyUtiles Tohex;
		 
		if (isPlayerIDdistanceSeeOtherPlayerID(ClientPlayerActor, otherPlayerActor))
		{
			msg = answer.createStr((float)ePackageRecovSend::PLAYER_ACTOR_NEW_POSSITIONS
				, Tohex.unsignetIntToHEX(m_countPackage)
				, it->second.m_PlayerActor.getHexInfo());
 

			m_sender->send_for(currEndPointPlayer->second.m_ep, msg);
			std::cout << "Event PLAYER_ACTOR_NEW_POSSITIONS " << " size = " << msg.length() << " for " << currEndPointPlayer->second.m_ep.address() << ":" << currEndPointPlayer->second.m_ep.port() << "\n";

			m_countPackage++;
		}
	} 
	 



	return msg;

}// end f()


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
	std::string stat = "[c_DataBaseClient_map::printStat()]\n"
		"Servet Data Base stat: \\"
		"\nCount Vehicle: " + std::to_string(m_VehManager->getCountVehicle())
		+ "\nCount Event: " + std::to_string(getCountEvent());
	//+ "\nCount Client: " + std::to_string(m_Player_Manager->getCountPlayerActor());
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


void c_DataBaseClient_map::addEventPlayerActorPossitionsControl(cPed Ped)
{
	c_Event PlayerActorPossitions(eTypeGameObject::PLAYER, Ped.m_iKeyID, Ped.m_fX, Ped.m_fY, Ped.m_fZ);
	addEvent(PlayerActorPossitions);
}

bool c_DataBaseClient_map::updateEventPlayerPossitions(cPed ped)
{
	if (m_Event.empty())
		return false;

	for (int i = 0; i < m_Event.size(); i++)
	{
		if (m_Event[i].m_iType != eTypeGameObject::PLAYER)
			continue;

		if (m_Event[i].m_AttachToID == ped.m_iKeyID)
		{

			std::cout << "Yeah!!!" << "\n";

			m_Event[i].update(ped.m_fX, ped.m_fY, ped.m_fZ);

			return true;
		}


	}
}

bool c_DataBaseClient_map::isPlayerIDdistanceSeeOtherPlayerID(cPed &PlayerIDActor, c_Event &Event)
{
	float distance = m_ComputeObj->Distance(PlayerIDActor, Event);
	if (distance < 166.6f)
		return true;
	return false;
}

bool c_DataBaseClient_map::isPlayerIDdistanceSeeOtherPlayerID(cPed &PlayerIDActor1, cPed &PlayerIDActor2)
{
	float distance = m_ComputeObj->Distance(PlayerIDActor1, PlayerIDActor2);
	if (distance < 166.6f)
		return true;
	return false;
}
