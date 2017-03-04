#pragma once

#include "MyUtiles.h"

#include "GameObject_List.h"

#include <boost/shared_ptr.hpp>



#include <functional>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <map>

class cPed
{
public:
	cPed(float x, float y, float z, float	fInterior, float fSpeed, int keyID, bool bInitPlayerPos);
	cPed();

	void set(float x, float y, float z, float fInterior, float fSpeed);

	float	m_fX;
	float	m_fY;
	float	m_fZ;
	float	m_fInterior;
	float	m_fSpeed;

	int		m_iKeyID;
	bool	m_bInitPlayerPos;
};
 
class c_PlayerManager
{
public:
	c_PlayerManager();

	/*void refresh_Player_map(int ByClientRemotePortKey, float x, float y, float z, float fInterior, float fSpeed);

	void remove_Player_Game_Info(int ByClientRemotePortKey);

	void print_data_base();

	*/
	void refreshPlayerActorPos(std::stringstream& UnBoxBytePos, int messagaSize, int ByClientRemotePortKey);

	cPed createPlayer(std::stringstream& byteArr, int messagaSize, int ByClientRemotePortKey);

	int getCountPlayerActor();
	//void createPlayer(std::stringstream& byteArr, int messagaSize, int ByClientRemotePortKey);

	/*possitions getPlayerPossitions(int KeyClient);

	void computeStreamZona();*/
 
private:

	void printInfo(std::map <int, cPed>::iterator &it);
	 
public:
	std::shared_ptr	<GameobjectDataBase> m_PlayerActorServIDList;
private:
	std::map <int, cPed>	m_map_player;
};





