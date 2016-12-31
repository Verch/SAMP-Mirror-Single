#pragma once
#include "MyUtiles.h"

#include <functional>
#include <algorithm>
#include <iostream>
#include <string>
#include <list>
#include <map>

/*

GameobjectDataBase
GameObj_DataBase
GameObjectDataBase

*/


class GameobjectDataBase
{
public:
	GameobjectDataBase(int MAX_COUNT_OBJECT);

	void	setFreeId(int ServerId);
	int		getServerId();
	void	TEST_print_list_dim(int design);	// [debug]

private:
	int MAX_COUNT_OBJECT;
	std::list<int> list_work_serverId;
	std::list<int> list_freeServerID;
	std::list<int>::iterator it1;
};



class c_Vehicle
{
public:
	c_Vehicle();
 
	int serverID;

	int iModel;
	int fHealth;

	float fX;
	float fY;
	float fZ;
};


class c_VehicleManager
{
public:
	c_VehicleManager();
	std::map <int, c_Vehicle>	m_map_veh;

	void refresh_vehicle_map(int serverID, int model, float x, float y, float z);
	std::string getHexInfoCarID(int serverID);

};

