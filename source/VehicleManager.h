#pragma once
#include "MyUtiles.h"
#include "BaseType.h"

#include <boost/shared_ptr.hpp>

#include "GameObject_List.h"

#include "BaseType.h"

#include <functional>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <map>

class c_Vehicle
{

private:
	CPoint3D m_Possitions;

public:

	c_Vehicle(float  fServerID, float fModel, float x, float y, float z, float fAngle, float fSpeed, float color_1, float color_2);

	c_Vehicle(float fModel, float x, float y, float z, float fAngle, float fSpeed);

	c_Vehicle(float fModel, CPoint3D Possitions, float fAngle, float fSpeed, float fServerID);


	void set(float x, float y, float z, float fAngle, float fSpeed, float color_1, float color_2);

	CPoint3D GetPossitions();

	void  SetPossitions(CPoint3D pos);
	 
	void initServerID(float serverID);

	void DebugPrintInfo()
	{
		std::cout << "[c_Vehicle::DebugPrintInfo] ServerID" << m_fServerID << "\n";
		std::cout << "[c_Vehicle::DebugPrintInfo] ...\n";

		Log("[c_Vehicle::DebugPrintInfo] model %f", (m_fModel));
		Log("[c_Vehicle::DebugPrintInfo] serverID %f", (m_fServerID));
		Log("[c_Vehicle::DebugPrintInfo] Speed %f", (m_fSpeed));
		Log("[c_Vehicle::DebugPrintInfo] Angle %f", (m_fAngle));
		Log("[c_Vehicle::DebugPrintInfo] color1 %f", (m_fColor_1));
		Log("[c_Vehicle::DebugPrintInfo] color2 %f", (m_fColor_2));
		Log("[c_Vehicle::DebugPrintInfo] x %f", (m_Possitions.GetX()));
		Log("[c_Vehicle::DebugPrintInfo] y %f", (m_Possitions.GetY()));
		Log("[c_Vehicle::DebugPrintInfo] z %f", (m_Possitions.GetZ()));
	}

	float	m_fServerID;
	float	m_fModel;
	 
	float	m_fAngle;
	float	m_fSpeed;
	float	m_fColor_1 = -1;
	float	m_fColor_2 = -1;
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

	bool isRegVehicle(c_Vehicle Vehicle);


	std::string getHexInfoCarID(int serverID);

	c_Vehicle createWantCar(std::stringstream& byteArr);

	c_Vehicle createCar(std::stringstream& byteArr);

	void UpdateVehicle(c_Vehicle Vehicle );
	 



	void printInfo(std::map <int, c_Vehicle>::iterator it);

	bool isVehicleInitCorrect(c_Vehicle & veh);

	void printInfoByKey(int key);

	int getCountVehicle();



	std::map <int, c_Vehicle>  GetVehicleManager()
	{
		return m_map_veh;
	}

private:
	bool isValidServerID(int id);
	bool isDefinedGameCarModel(int modelIndex);
	bool isPosittionsForCarSpawnTry();
	bool isInitVehicleColor(float color1, float color2);
private:
	std::map <int, c_Vehicle> m_map_veh;

};

