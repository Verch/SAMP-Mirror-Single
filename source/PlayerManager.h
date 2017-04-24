#pragma once

#include "MyUtiles.h"

#include "GameObject_List.h"

#include <boost/shared_ptr.hpp>



#include <functional>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <map>

#include "BaseType.h"
 
class cPed
{
private:
	CPoint3D m_Possitions;

public:
	cPed(float x, float y, float z, float	fInterior, float fSpeed, int keyID, bool bInitPlayerPos);

	cPed();

	void set(float x, float y, float z, float fInterior, float fSpeed);

	CPoint3D GetPossitions();
	void SetPossitions(CPoint3D pos);
	 
	bool isInitPlayerPossitions();
	  
	float	m_fInterior = -1.0f;
	float	m_fSpeed = -1.0f;

	int		m_iKeyID = -1;;

	bool	m_bInitPlayerPos = false;

public:
	std::string getHexInfo();

};

class c_PlayerManager
{
public:
	c_PlayerManager();

	cPed createPlayer(std::stringstream& byteArr, int messagaSize, int ByClientRemotePortKey);

private:

	void printInfo(std::map <int, cPed>::iterator &it);

public:

	std::shared_ptr	<GameobjectDataBase> m_PlayerActorServIDList;
private:
	std::map <int, cPed> m_map_player;
};







