#pragma once
#include "MyUtiles.h"

#include <boost/shared_ptr.hpp>

#include "GameObject_List.h"

#include <functional>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <map>


class c_Vehicle
{
public:

	c_Vehicle(float  fServerID, float fModel, float x, float y, float z, float fAngle, float fSpeed, float color_1, float color_2);

	c_Vehicle(float fModel, float x, float y, float z, float fAngle, float fSpeed);

	void set(float x, float y, float z, float fAngle, float fSpeed, float color_1, float color_2);

	void initServerID(float serverID);

	float	m_fServerID;
	float	m_fModel;
	float	m_fX;
	float	m_fY;
	float	m_fZ;
	float	m_fAngle;
	float	m_fSpeed;
	float	m_fColor_1;
	float	m_fColor_2;
};


class c_VehicleManager
{
public:
	std::shared_ptr	<GameobjectDataBase> m_servListID;

public:
	c_VehicleManager();

	//void refresh_vehicle_map(float fServerID, float fModel, float x, float y, float z, float fAngle, float fSpeed);
	//void refresh_vehicle_map(int serverID, int model, float x, float y, float z, float fAngle, float fSpeed);
	/*c_Vehicle unBox_want_Possitions_for_Car_Spawn(std::stringstream& byteArr);*/
	//std::string getNewServerCarID(std::stringstream& byteArr, int messagaSize, int ByClientRemotePortKey);
	//std::string getInfoCarByServId(std::stringstream& byteArr, int messagaSize, int ByClientRemotePortKey);

	bool regVehicle(c_Vehicle Vehicle);

	std::string getHexInfoCarID(int serverID);

	c_Vehicle createWantCar(std::stringstream& byteArr);

	void printInfo(std::map <int, c_Vehicle>::iterator it);

	bool isVehicleInitCorrect(c_Vehicle & veh);

	void printInfoByKey(int key);

	int getCountVehicle();
private:
	bool isValidServerID(int id);
	bool isDefinedGameCarModel(int modelIndex);
	bool isPosittionsForCarSpawnTry();
	bool isInitVehicleColor(float color1, float color2);
private:
	std::map <int, c_Vehicle>	m_map_veh;

};

