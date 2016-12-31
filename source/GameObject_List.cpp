#pragma once 
#include "GameObject_List.h"

GameobjectDataBase::GameobjectDataBase(int MAX_count_obj) : MAX_COUNT_OBJECT(MAX_count_obj)
{
	std::cout << "[GameobjectDataBase] Create" << "\n";
	std::cout << "[GameobjectDataBase] MAX_COUNT_OBJECT = " << MAX_COUNT_OBJECT << "\n";
	for (int i = 0; i < MAX_COUNT_OBJECT; i++)
		list_freeServerID.push_back(i);
}

int GameobjectDataBase::getServerId()
{
	int serverId;
	if (!list_freeServerID.empty())
	{
		it1 = list_freeServerID.begin();		// �������� �� ������ ��-�
		serverId = *it1;						// �������� �������� 
		it1 = list_freeServerID.erase(it1);		// ������� �� "������ �������" 
		list_work_serverId.push_back(serverId);	// ������������ �� ������ �������
		return serverId;						// � ��� ����� ��������� �������
	}
	else
	{
		return -1;
	}
}

void GameobjectDataBase::setFreeId(int ServerId)
{
	for (std::list<int>::iterator it = list_work_serverId.begin();
		it != list_work_serverId.end(); ++it)
	{
		if (*it == ServerId)
		{
			if (!list_work_serverId.empty())
			{
				std::cout << "�������� " << *it << " ������\n";
				it = list_work_serverId.erase(it);
				list_freeServerID.push_back(ServerId);
			}
		}
	}
}

void GameobjectDataBase::TEST_print_list_dim(int design)
{
	if (design == 1)
	{
		std::cout << "list_work_serverId: \t";
		for (std::list<int>::iterator it = list_work_serverId.begin();
			it != list_work_serverId.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
	if (design == 2)
	{
		std::cout << "list_freeServerID: \t";
		for (std::list<int>::iterator it = list_freeServerID.begin();
			it != list_freeServerID.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
}


//===============================================

c_Vehicle::c_Vehicle()
{

	iModel = 0;
	fHealth = 0;
	fX = 0;
	fY = 0;
	fZ = 0;
}

c_VehicleManager::c_VehicleManager()
{
	std::cout << "[c_VehicleManager] create!" << "\n";
}

void c_VehicleManager::refresh_vehicle_map(int serverID, int model, float x, float y, float z)
{
	std::cout << "[c_VehicleManager::refresh_vehicle_map]" << "\n";
	auto it = std::find_if(m_map_veh.begin(), m_map_veh.end(),
		[&serverID](const std::pair<int, c_Vehicle> &p)
	{
		return p.first == serverID;
	});

	if (it != m_map_veh.end())
	{// update 	 
		(*it).second.fX = x;
		(*it).second.fY = y;
		(*it).second.fZ = z;

		printf("Update x=%f y=%f z=%f \n"
			"---------------------------\n"
			, x
			, y
			, z
			);
	}
	else
	{		// register 
		c_Vehicle tmp; 	// for box
		tmp.serverID = serverID;
		tmp.iModel = model;
		tmp.fX = x;
		tmp.fY = y;
		tmp.fZ = z;
		m_map_veh.insert(std::pair<int, c_Vehicle>(serverID, tmp));

		printf("Update iServerID=%d iModel%d x=%f y=%f z=%f\n"
			"---------------------------\n"
			, serverID
			, model
			, x
			, y
			, z
			);

	}
}

std::string c_VehicleManager::getHexInfoCarID(int serverID)
{
	auto it = std::find_if(m_map_veh.begin(), m_map_veh.end(),
		[&serverID](const std::pair<int, c_Vehicle> &p)
	{
		return p.first == serverID;
	});

	if (it != m_map_veh.end())
	{// update 	 
		std::cout << "\n[c_VehicleManager::getHexInfoCarID]" << "\n";
		std::cout << " serverID " << (*it).second.serverID << " ";
		std::cout << " iModel  " << (*it).second.iModel << " ";
		std::cout << " pos " << (*it).second.fX;
		std::cout << " pos " << (*it).second.fY;
		std::cout << " pos " << (*it).second.fZ;
		std::cout << "\n-----------------------\n";
		std::cout << "\n";

		c_MyUtiles myUtites;
		std::string packageAnswer =
			myUtites.IntToHEX((*it).second.serverID)
			+ myUtites.IntToHEX((*it).second.iModel)
			+ myUtites.floatToHEX((*it).second.fX)
			+ myUtites.floatToHEX((*it).second.fY)
			+ myUtites.floatToHEX((*it).second.fZ);
		myUtites.~c_MyUtiles();

		return packageAnswer;
	}
	else
	{		// register  
		std::cout << "add log client hack" << "\n";
	}
	return "0";
}




///* input: ptr struct		output init. struct for send */
//void cDataBase_Client_map::getAnswer(std::string paket, udp::endpoint &ep,
//	std::shared_ptr<ExternStructSend> ptrSendStruct)
//{
//	ptrSendStruct->m_byHost_ep = ep;					// ip ������a �� �������� ��� ������ �����
//
//	// ���� ��������� ������ �� ��������� �� � ��� �������� ������ ��������� ���� �����������
//	// ����� m_StrMsg �������������
//	ptrSendStruct->m_StrMsg = toString(ep.port()) + " " + paket;		// � ������ ������ ����� �� ������, ������ "65512 "
//	ptrSendStruct->m_bEverySend = true;
//	ptrSendStruct->m_bAnswer = true;
//
//	//	��� ����� ����������� ����
//	std::shared_ptr<std::list <double>> sharedLIst;						//	��� ���������� ���������
//	sharedLIst = std::make_shared<std::list <double>>();				/* ����������� ��� ���� ����� ����� ptr */
//
//	boost::regex reg("(-+|)\\d+(,\\d+)*");								// ����� �������� �����: ( ������������� ) �����, �������
//	for (boost::sregex_iterator it(paket.begin(), paket.end(), reg);
//		it != boost::sregex_iterator(); ++it)
//		sharedLIst->push_back(atof((*it).str().c_str()));				// ����� ������������ ��������� � ������
//
//	std::list<double>::iterator it = sharedLIst->begin();				// �������� �� ������ ������ 
//
//	std::string strRez;
//	if (!sharedLIst->empty())
//	{
//		int count_prms = sharedLIst->size();
//
//		switch (count_prms)												// ���� �� ���-�� ����������
//		{
//		case 1:
//
//			// int design = *it;
//			if ((int)(*it) == 100)										// if � ��� ������ serverID 
//			{
//				ptrSendStruct->m_StrMsg = "Answer " + toString(getServerId());
//				ptrSendStruct->m_bEverySend = false;
//			}
//
//			if ((int)(*it) == 0)										// 0 - ������ ���������� 0 ������� � ��� ��� �� 0-nline	 
//			{
//				std::cout << "[void] online" << ep.port() << "\n";
//				ptrSendStruct->m_bAnswer = false;
//			}
//			break;
//			//-------------------------------------
//
//		case 2:
//			if ((int)(*it) == 99)										// del �� ����� �������� ��������� �� ������ �������
//			{
//				it++;
//				std::cout << "serverID " << *it << " free\n";
//			}
//
//			break;
//			//-------------------------------------
//
//		default: std::cout << "AHTUNG:" << "\n";  break;
//
//		}
//	}
//}
