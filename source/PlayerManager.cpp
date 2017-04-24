#pragma once 
#include "PlayerManager.h"

#include "MyUtiles.h"



cPed::cPed(float x, float y, float z, float	fInterior, float fSpeed, int keyID, bool bInitPlayerPos)
	:
	m_Possitions(x, y, z)
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

	m_Possitions.Set(x, y, z);

/*
	m_fX = x;
	m_fY = y;
	m_fZ = z;
*/
	m_fInterior = fInterior;
	m_fSpeed = fSpeed;
}

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


CPoint3D cPed::GetPossitions()
{
	return m_Possitions;
}


void cPed::SetPossitions(CPoint3D pos)
{
	m_Possitions = pos;
}


bool cPed::isInitPlayerPossitions()
{
	return m_bInitPlayerPos;
}

/*
int c_PlayerManager::getCountPlayerActor()
{
if (m_map_player.empty())
{
return 0;
}
return m_map_player.size();
}*/

std::string cPed::getHexInfo()
{

	float fModel = 1;
	float fAngle = 1;
	float fServerId = 1;

	c_MyUtiles myUtites;

	std::string packageAnswer =
		/* other metod add ServerTick*/
		/* other metod add fDecision*/	
		myUtites.floatToHEX(m_iKeyID)
		+ myUtites.floatToHEX(fModel)
		+ myUtites.floatToHEX(GetPossitions().GetX())
		+ myUtites.floatToHEX(GetPossitions().GetY())
		+ myUtites.floatToHEX(GetPossitions().GetZ())
		+ myUtites.floatToHEX(fAngle)
		+ myUtites.floatToHEX(m_fSpeed)
		+ myUtites.floatToHEX(m_fInterior);

	myUtites.~c_MyUtiles();

	return packageAnswer;

}
