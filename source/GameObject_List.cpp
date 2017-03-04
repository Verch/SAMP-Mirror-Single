#pragma once 
#include "GameObject_List.h"

GameobjectDataBase::GameobjectDataBase(int MAX_count_obj) : MAX_COUNT_OBJECT(MAX_count_obj)
{
	//std::cout << "[GameobjectDataBase] Create" << "\n";
	//std::cout << "[GameobjectDataBase] MAX_COUNT_OBJECT = " << MAX_COUNT_OBJECT << "\n";
	for (int i = 0; i < MAX_COUNT_OBJECT; i++)
		list_freeServerID.push_back(i);
}

int GameobjectDataBase::getServerID()
{
	int serverId;
	if (!list_freeServerID.empty())
	{
		it1 = list_freeServerID.begin();		// итератор на первый эл-т
		serverId = *it1;						// получили значение 
		it1 = list_freeServerID.erase(it1);		// удалили из "первой очереди" 
		list_work_serverId.push_back(serverId);	// переброслили во вторую очередь
		return serverId;						// а это можно отправить клиенту
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
				//std::cout << "найденно " << *it << " удаляю\n";
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
		//std::cout << "list_work_serverId: \t";
		for (std::list<int>::iterator it = list_work_serverId.begin();
			it != list_work_serverId.end(); ++it)
			std::cout << ' ' << *it;
		//std::cout << '\n';
	}
	if (design == 2)
	{
		//std::cout << "list_freeServerID: \t";
		for (std::list<int>::iterator it = list_freeServerID.begin();
			it != list_freeServerID.end(); ++it)
			std::cout << ' ' << *it;
		//std::cout << '\n';
	}
}

 

 