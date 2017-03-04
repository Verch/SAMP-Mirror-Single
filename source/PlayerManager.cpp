#pragma once 
#include "PlayerManager.h"


cPed::cPed(float x, float y, float z, float	fInterior, float fSpeed, int keyID, bool bInitPlayerPos)
	: m_fX(x)
	, m_fY(y)
	, m_fZ(z)
	, m_fInterior(fInterior)
	, m_fSpeed(fSpeed)
	, m_iKeyID(keyID)
	, m_bInitPlayerPos(bInitPlayerPos)
{

}

cPed::cPed(){}

void cPed::set(float x, float y, float z, float fInterior, float fSpeed)
{
	/*std::cout << " x " << x << "\n";
	std::cout << " y " << y << "\n";
	std::cout << " z " << z << "\n";
	std::cout << " speed " << fSpeed << "\n";*/

	m_fX = x;
	m_fY = y;
	m_fZ = z;
	m_fInterior = fInterior;
	m_fSpeed = fSpeed;
}

//==============================================
  
//
//void c_PlayerManager::refresh_Player_map(int ByClientRemotePortKey, float x, float y, float z, float fInterior, float fSpeed)
//{
//	//std::cout << "[c_PlayerManager::refresh_Player_map]  ";
//
//	auto it = std::find_if(m_map_player.begin(), m_map_player.end(),
//		[&ByClientRemotePortKey](const std::pair<int, c_Player> &p)
//	{
//		return p.first == ByClientRemotePortKey;
//	});
//
//	if (it != m_map_player.end())
//	{// update 	 
//		std::cout << "update" << " ";
//		(*it).second.set(x, y, z, fInterior, fSpeed);
//		printInfo(it);
//	}
//	else
//	{	// register 
//		std::cout << "register " << "\n";
//		c_Player tmp(x, y, z, fInterior, fSpeed, ByClientRemotePortKey);
//		m_map_player.insert(std::pair<int, c_Player>(ByClientRemotePortKey, tmp));
//		//std::cout << "register " << ByClientRemotePortKey << "\n";
//	}
//}
////  
//void c_PlayerManager::remove_Player_Game_Info(int ByClientRemotePortKey)
//{
//	//std::cout << "[c_PlayerManager::remove_Player_Game_Info] " << "\n";
//	auto it = std::find_if(m_map_player.begin(),
//		m_map_player.end(), [&ByClientRemotePortKey]
//		(const std::pair<int, c_Player > &p)
//	{
//		return p.first == ByClientRemotePortKey;
//	});
//
//	if (it != m_map_player.end())
//	{
//		std::cout << "delete" << "\n";
//		printInfo(it);
//		m_map_player.erase(it);
//	}
//}
//
//void c_PlayerManager::print_data_base()
//{
//	//std::cout << "[c_PlayerManager::print_data_base()]" << "\n";
//	for (auto it = m_map_player.begin(); it != m_map_player.end(); it++)
//		printInfo(it);
//}
//
//
//void c_PlayerManager::printInfo(std::map <int, c_Player>::iterator &it)
//{
//	std::cout << " key = " << it->second.m_iKeyID << " ";
//	std::cout << " x = " << it->second.m_fX << " ";
//	std::cout << " y = " << it->second.m_fY << " ";
//	std::cout << " z = " << it->second.m_fZ << " ";
//	std::cout << " fInterior = " << it->second.m_fInterior << " ";
//	std::cout << " speed = " << it->second.m_fSpeed << " ";
//	//std::cout << "\-----------------------" << "\n";
//}
//
//possitions c_PlayerManager::getPlayerPossitions(int KeyClient)
//{
//	auto it = std::find_if(m_map_player.begin(),
//		m_map_player.end(), [&KeyClient]
//		(const std::pair<int, c_Player > &p)
//	{
//		return p.first == KeyClient;
//	});
//
//	possitions player_pos(-999999, -99999, -999999, -999999, -9999999);
//
//	if (it != m_map_player.end())
//	{
//		player_pos.x = (*it).second.m_fX;
//		player_pos.y = (*it).second.m_fY;
//		player_pos.z = (*it).second.m_fZ;
//
//		//printInfo(it);
//	}
//	else
//		std::cout << " Not info by player posstions" << "\n";
//
//	return player_pos;
//}
//
 
//void c_PlayerManager::refreshPlayerActorPos(std::stringstream& UnBoxBytePos, int messagaSize, int ByClientRemotePortKey)
//{
//	if (messagaSize != 28)
//	{
//		return;
//		std::cout << "[void c_PlayerManager::refreshPlayerActorPos] Add to log bad size msg." << "\n";
//	}
//	  
//	/* 4 */ //unsigned int unBox_clientPassport = 0;		// not reliz
//	/* 8 */ //float unBox_design = 0;					
//	/* 16 */ float unBox_xPos = 0;
//	/* 20 */ float unBox_yPos = 0;
//	/* 24 */ float unBox_zPos = 0;
//	/* 28 */ float unBoxInterior = 0;
//	/* 32 */ float unBoxSpeed = 0;
//
//	UnBoxBytePos.read((char*)&unBox_xPos, 4);
//	UnBoxBytePos.read((char*)&unBox_yPos, 4);
//	UnBoxBytePos.read((char*)&unBox_zPos, 4);
//	UnBoxBytePos.read((char*)&unBoxInterior, 4);
//	UnBoxBytePos.read((char*)&unBoxSpeed, 4);
//
//	refresh_Player_map(ByClientRemotePortKey, unBox_xPos, unBox_yPos, unBox_zPos, unBoxInterior, unBoxSpeed);
//}
//
//void c_PlayerManager::computeStreamZona()
//{
//	//std::cout << "[void c_PlayerManager::computeStreamZona()]" << "\n";
//	std::map <int, c_Player>::iterator i = m_map_player.begin();
//	std::map <int, c_Player>::iterator j = m_map_player.begin();
//
//	for (i = m_map_player.begin(); i != m_map_player.end(); i++)
//	{
//		for (j = m_map_player.begin(); j != m_map_player.end(); j++)
//		{
//			//std::cout << "сравниваю " << i->second.m_iKeyID << " c " << j->second.m_iKeyID << "\n";
//		}
//		//std::cout << "\n";
//	}
//
//
//
//
//}

c_PlayerManager::c_PlayerManager()
{
	//std::cout << "[c_VehicleManager] create!" << "\n";
	int MAX_COUNT_OBJECT_PLAYER_ACTOR = 50;
	m_PlayerActorServIDList = std::make_shared<GameobjectDataBase>(MAX_COUNT_OBJECT_PLAYER_ACTOR);
}

cPed c_PlayerManager::createPlayer(std::stringstream& UnBoxBytePos, int messagaSize, int ByClientRemotePortKey)
{ 
	/* 4 */ //unsigned int unBox_clientPassport = 0;		// not reliz
	/* 8 */ //float unBox_design = 0;					
	/* 16 */ float unBox_xPos = 0;
	/* 20 */ float unBox_yPos = 0;
	/* 24 */ float unBox_zPos = 0;
	/* 28 */ float unBoxInterior = 0;
	/* 32 */ float unBoxSpeed = 0;

	UnBoxBytePos.read((char*)&unBox_xPos, 4);
	UnBoxBytePos.read((char*)&unBox_yPos, 4);
	UnBoxBytePos.read((char*)&unBox_zPos, 4);
	UnBoxBytePos.read((char*)&unBoxInterior, 4);
	UnBoxBytePos.read((char*)&unBoxSpeed, 4);
	 
	cPed tmp(unBox_xPos, unBox_yPos, unBox_zPos, unBoxInterior, unBoxSpeed, ByClientRemotePortKey, true);
	return tmp;
}

int c_PlayerManager::getCountPlayerActor()
{
	if (m_map_player.empty())
	{
		return 0;
	}
	return m_map_player.size();
}
