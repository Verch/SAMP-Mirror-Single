#pragma once 
#include "VehicleManager.h"
#include "PackageType.h"
#include <assert.h>


c_Vehicle::c_Vehicle(float  fServerID, float fModel, float x, float y, float z, float fAngle, float fSpeed, float color_1, float color_2)
	:
	m_fServerID(fServerID)
	, m_fModel(fModel)
	, m_fX(x)
	, m_fY(y)
	, m_fZ(z)
	, m_fAngle(fAngle)
	, m_fSpeed(fSpeed)
	, m_fColor_1(color_1)
	, m_fColor_2(color_2)
{

}


void c_Vehicle::set(float x, float y, float z, float fAngle, float fSpeed, float color_1, float color_2)
{
	m_fX = x;
	m_fY = y;
	m_fZ = z;
	m_fSpeed = fSpeed;
	m_fAngle = fAngle;

	m_fColor_1 = (color_1);
	m_fColor_2 = (color_2);
}

void c_Vehicle::initServerID(float serverID)
{
	m_fServerID = serverID;
}

c_VehicleManager::c_VehicleManager()
{
	//std::cout << "[c_VehicleManager] create!" << "\n";

	int MAX_COUNT_OBJECT_VEHICLE = 50;
	m_servListID = std::make_shared<GameobjectDataBase>(MAX_COUNT_OBJECT_VEHICLE);

}

bool c_VehicleManager::regVehicle(c_Vehicle Vehicle)
{
	int serverID = (int)Vehicle.m_fServerID;

	auto it = std::find_if(m_map_veh.begin(), m_map_veh.end(),
		[&serverID](const std::pair<int, c_Vehicle> &p)
	{
		return p.first == serverID;
	});

	if (it != m_map_veh.end())
	{// update 	 
		Log("[void c_VehicleManager::refresh_vehicle_map(c_Vehicle Vehicle)] CAR yje zaregan");
		std::cout << "[void c_VehicleManager::refresh_vehicle_map(c_Vehicle Vehicle)] CAR yje zaregan" << "\n";
		return false;
	}
	else
	{		// register 
		m_map_veh.insert(std::pair<int, c_Vehicle>(serverID, Vehicle));
		return true;
	}
}

c_Vehicle c_VehicleManager::createWantCar(std::stringstream& byteArr)
{
	// 4
	// 8	
	float unBox_model = 0;	// 12
	float unBox_xPos = 0;	// 16
	float unBox_yPos = 0;	// 20
	float unBox_zPos = 0;	// 24
	float unBox_angle = 0;	// 28
	float unBox_speed = 0;	// 32

	float unBoxColor_1 = 0;	// 36
	float unBoxColor_2 = 0;	// 40


	byteArr.read((char*)&unBox_model, 4);
	byteArr.read((char*)&unBox_xPos, 4);
	byteArr.read((char*)&unBox_yPos, 4);
	byteArr.read((char*)&unBox_zPos, 4);
	byteArr.read((char*)&unBox_angle, 4);
	byteArr.read((char*)&unBox_speed, 4);

	byteArr.read((char*)&unBoxColor_1, 4);
	byteArr.read((char*)&unBoxColor_2, 4);


	c_Vehicle wantCar(/*ahtung -1 = serverCArID */ -1, unBox_model, unBox_xPos, unBox_yPos, unBox_zPos, unBox_angle, unBox_speed
		, unBoxColor_1, unBoxColor_2);

	return wantCar;
}

std::string c_VehicleManager::getHexInfoCarID(int serverID)
{
	auto it = std::find_if(m_map_veh.begin(), m_map_veh.end(),
		[&serverID](const std::pair<int, c_Vehicle> &p)
	{
		return p.first == serverID;
	});

	if (it != m_map_veh.end())
	{
		c_MyUtiles myUtites;

		std::string packageAnswer =
			myUtites.floatToHEX((*it).second.m_fServerID)
			+ myUtites.floatToHEX((*it).second.m_fModel)
			+ myUtites.floatToHEX((*it).second.m_fX)
			+ myUtites.floatToHEX((*it).second.m_fY)
			+ myUtites.floatToHEX((*it).second.m_fZ)
			+ myUtites.floatToHEX((*it).second.m_fAngle)
			+ myUtites.floatToHEX((*it).second.m_fSpeed)
			+ myUtites.floatToHEX((*it).second.m_fColor_1)
			+ myUtites.floatToHEX((*it).second.m_fColor_2);

		myUtites.~c_MyUtiles();

		return packageAnswer;
	}
	else
	{		// register  

		Log("[add log c_Client hack 0xqw23]");
	}
	return "0";
}

void c_VehicleManager::printInfo(std::map <int, c_Vehicle>::iterator it)
{
	std::cout << " serverID " << (*it).second.m_fServerID;
	std::cout << " fModel  " << (*it).second.m_fModel;
	std::cout << " x " << (*it).second.m_fX;
	std::cout << " y " << (*it).second.m_fY;
	std::cout << " z " << (*it).second.m_fZ;
	std::cout << " angle " << (*it).second.m_fAngle;
	std::cout << " speed " << (*it).second.m_fSpeed;

	/*Log("[c_VehicleManager::printInfo] ");
	Log(" serverID %f", (*it).second.m_fServerID);
	Log(" fModel  %f", (*it).second.m_fModel);
	Log(" x %f", (*it).second.m_fX);
	Log(" y %f", (*it).second.m_fY);
	Log(" z %f", (*it).second.m_fZ);
	Log(" angle %f", (*it).second.m_fAngle);
	Log(" speed %f", (*it).second.m_fSpeed);*/

}

void c_VehicleManager::printInfoByKey(int key)
{
	int serverID = key;

	auto it = std::find_if(m_map_veh.begin(), m_map_veh.end(),
		[&serverID](const std::pair<int, c_Vehicle> &p)
	{
		return p.first == serverID;
	});

	if (it != m_map_veh.end())
		printInfo(it);
	else
		Log("[c_VehicleManager::printInfoByKey(int key)]  key not search");
}




int c_VehicleManager::getCountVehicle()
{
	if (m_map_veh.empty())
		return 0;
	return m_map_veh.size();
}

bool c_VehicleManager::isVehicleInitCorrect(c_Vehicle &vehicle)
{
	if (isDefinedGameCarModel((int)vehicle.m_fModel)
		&& isValidServerID((int)vehicle.m_fServerID)
		&& isInitVehicleColor(vehicle.m_fColor_1, vehicle.m_fColor_2))
		return true;

	return false;
}

bool c_VehicleManager::isValidServerID(int id)
{
	if (id < 0) return false;
	return true;
}

bool c_VehicleManager::isDefinedGameCarModel(int modelIndex)
{
	if (modelIndex >= 400 && modelIndex <= 611)
	{
		return true;
	}

	std::cout << "[bool c_VehicleManager::isDefineGameCarModel] AHTUNG, HAX, false" << "\n";

	Log("[bool c_VehicleManager::isDefineGameCarModel] AHTUNG, HAX, false");

	return false;
}
 
bool c_VehicleManager::isInitVehicleColor(float color1, float color2)
{
	if (color1 >= 0 && color2 >= 0)
		return true;

	Log("[c_VehicleManager::isInitVehicleColor] AHTUNG, false");

	return false;
}
