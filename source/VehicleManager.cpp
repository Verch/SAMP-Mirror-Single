#pragma once 
#include "VehicleManager.h"
#include "PackageType.h"


c_Vehicle::c_Vehicle(float  fServerID, float fModel, float x, float y, float z, float fAngle, float fSpeed)
	:
	m_fServerID(fServerID)
	, m_fModel(fModel)
	, m_fX(x)
	, m_fY(y)
	, m_fZ(z)
	, m_fAngle(fAngle)
	, m_fSpeed(fSpeed)
{

}


void c_Vehicle::set(float x, float y, float z, float fAngle, float fSpeed)
{
	m_fX = x;
	m_fY = y;
	m_fZ = z;
	m_fSpeed = fSpeed;
	m_fAngle = fAngle;
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

	byteArr.read((char*)&unBox_model, 4);
	byteArr.read((char*)&unBox_xPos, 4);
	byteArr.read((char*)&unBox_yPos, 4);
	byteArr.read((char*)&unBox_zPos, 4);
	byteArr.read((char*)&unBox_angle, 4);
	byteArr.read((char*)&unBox_speed, 4);

	c_Vehicle wantCar(/*ahtung -1 = serverCArID */ -1, unBox_model, unBox_xPos, unBox_yPos, unBox_zPos, unBox_angle, unBox_speed);
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
			+ myUtites.floatToHEX((*it).second.m_fSpeed);

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
		&& isValidServerID((int)vehicle.m_fServerID))
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



//void c_VehicleManager::refresh_vehicle_map(float fServerID, float fModel, float x, float y, float z, float fAngle, float fSpeed)
//{
//	int serverID = (int)fServerID;
//
//	std::cout << "[c_VehicleManager::refresh_vehicle_map]" << "\n";
//	auto it = std::find_if(m_map_veh.begin(), m_map_veh.end(),
//		[&serverID](const std::pair<int, c_Vehicle> &p)
//	{
//		return p.first == serverID;
//	});
//
//	if (it != m_map_veh.end())
//	{// update 	 
//		(*it).second.set(x, y, z, fAngle, fSpeed);
//		std::cout << "update" << "\t";
//		printInfo(it);
//	}
//	else
//	{		// register 
//		c_Vehicle tmp(fServerID, fModel, x, y, z, fAngle, fSpeed);
//		m_map_veh.insert(std::pair<int, c_Vehicle>(serverID, tmp));
//		std::cout << "register car from Server Data Base" << "\n";
//	}
//}
//================================================

//std::string c_VehicleManager::getNewServerCarID(std::stringstream& byteArr, int messagaSize, int ByClientRemotePortKey)
//{
//	float fDesign = 666;
//
//	float servCarID = (float)m_ServIDVehList->getServerId();
//
//	c_MyUtiles myUtites;
//
//	std::string package = myUtites.floatToHEX(fDesign) + myUtites.floatToHEX(servCarID);
//
//	return package;
//}
//
//std::string c_VehicleManager::getInfoCarByServId(std::stringstream& byteArr, int messagaSize, int ByClientRemotePortKey)
//{
//	std::string answer("Unknow Answer");
//	return answer;
//}
//



//c_Vehicle::c_Vehicle(float fModel, float x, float y, float z, float fAngle, float fSpeed)
//	:
//	m_fModel(fModel)
//	, m_fX(x)
//	, m_fY(y)
//	, m_fZ(z)
//	, m_fAngle(fAngle)
//	, m_fSpeed(fSpeed)
//{
//	//std::cout << "[c_Vehicle::c_Vehicle] not init server Id" << "\n";
//	m_fServerID = -1;
//
//	std::cout << " " << m_fModel;
//	std::cout << " " << m_fX;
//	std::cout << " " << m_fY;
//	std::cout << " " << m_fZ;
//	std::cout << " " << m_fAngle;
//	std::cout << " " << m_fSpeed;
//
//}


//c_Vehicle c_VehicleManager::unBox_want_Possitions_for_Car_Spawn(std::stringstream& byteArr)
//{
//	// 4
//	// 8	
//	float unBox_model = 0;	// 12
//	float unBox_xPos = 0;	// 16
//	float unBox_yPos = 0;	// 20
//	float unBox_zPos = 0;	// 24
//	float unBox_angle = 0;	// 28
//	float unBox_speed = 0;	// 32
//
//	byteArr.read((char*)&unBox_model, 4); // not reliz
//	byteArr.read((char*)&unBox_xPos, 4);
//	byteArr.read((char*)&unBox_yPos, 4);
//	byteArr.read((char*)&unBox_zPos, 4);
//	byteArr.read((char*)&unBox_angle, 4);
//	byteArr.read((char*)&unBox_speed, 4);
//
//	c_Vehicle wantCar(unBox_model, unBox_xPos, unBox_yPos, unBox_zPos, unBox_angle, unBox_speed);
//	return wantCar;
//}

//possitions posCarSpawn(unBox_xPos, unBox_yPos, unBox_zPos);

//possitions posClient = m_Player_Manager->getPlayerPossitions(ByClientRemotePortKey);
/*	if (m_ComputeObj->DistanceStreamSee(posCarSpawn, posClient) < m_GameSetting.STREAM_DISTANCE )
	{
	float ServIDCar = (float)m_Veh_Manager->m_ServIDVehList->getServerId();
	}
	//	*/
//		
//
//	 
//}
//

//





//	//std::cout << "[c_Logic::unBox_want_Possitions_for_Car_Spawn]" << "\t";
//	if (sizeRecovByte != 32) // 8 prms
//		return;
//
//	//std::cout << "Try" << "\n";
//
//	float unBox_model = 0;
//	float unBox_xPos = 0;
//	float unBox_yPos = 0;
//	float unBox_zPos = 0;
//	float unBox_angle = 0;
//	float unBox_speed = 0;
//
//
//	byteArr.read((char*)&unBox_model, 4);
//	byteArr.read((char*)&unBox_xPos, 4);
//	byteArr.read((char*)&unBox_yPos, 4);
//	byteArr.read((char*)&unBox_zPos, 4);
//
//	byteArr.read((char*)&unBox_angle, 4);
//	byteArr.read((char*)&unBox_speed, 4);
//
//
//	possitions posCarSpawn(unBox_xPos, unBox_yPos, unBox_zPos);
//
//	possitions posClient = m_Player_Manager->getPlayerPossitions(ByClientRemotePortKey);
//
///*	if (m_ComputeObj->DistanceStreamSee(posCarSpawn, posClient) < m_GameSetting.STREAM_DISTANCE )
//	{
//		float ServIDCar = (float)m_Veh_Manager->m_ServIDVehList->getServerId();