#pragma once 
#include "DataBase.h"
          
cDataBase_Client_map::cDataBase_Client_map()
{
 	std::cout << "cDataBase_Client_map() create" << "\n";
}

cDataBase_Client_map::~cDataBase_Client_map()
{
	std::cout << "~cDataBase_Client_map() destroy" << "\n";
}
  
std::string cDataBase_Client_map::toString(int number)
{
	int _forAitoaRadix = 10;
	char _forbuffer[20];
	char *p = _itoa(number, _forbuffer, _forAitoaRadix);
	return (std::string)p;
}
 
void cDataBase_Client_map::refresh_ip_List(boost::asio::ip::udp::endpoint &ep)
{
	int keyPort = ep.port();
	auto it = std::find_if(m_map_client.begin(), m_map_client.end(),
		[&keyPort](const std::pair<int, struct client> &p)
	{
		return p.first == keyPort;
	});

	if (it != m_map_client.end())
	{		// new info by client	
		(*it).second.last_ping = boost::posix_time::microsec_clock::local_time();	// update Ping
	}
	else
	{		// register 
		client tmp(ep);	// for box
		tmp.last_ping = boost::posix_time::microsec_clock::local_time();
		m_map_client.insert(std::pair<int, struct client>(keyPort, tmp));
		std::cout << "[cDataBase_Client_map::refresh_ip_List] connect " << ep.address().to_string() << ":" << keyPort << std::endl;
	}
}


void cDataBase_Client_map::closeSocket_map(int keyPort)
{
	auto it = std::find_if(m_map_client.begin(),
		m_map_client.end(), [&keyPort]
		(const std::pair<int, struct client > &p)
	{
		return p.first == keyPort;
	});

	if (it != m_map_client.end())
	{
		std::cout << "[cDataBase_Client_map::closeSocket_map] socket" << (*it).second.ep.port() << " удален из очереди" << "\n";
		m_map_client.erase(it);
	}
}


//==================================================================================================




//#pragma once
//
//#include <functional>
//#include <algorithm>
//#include <iostream>
//#include <string>
//#include <map>
//
//#include <boost/enable_shared_from_this.hpp>
//#include <boost/shared_ptr.hpp>
//#include <boost/asio.hpp>
//
//#include <boost/bind.hpp>
//#include <boost/regex.hpp>
//#include <boost/thread.hpp>
//#include <boost/shared_ptr.hpp>
//#include <boost/enable_shared_from_this.hpp>

//#include "udpserver.h"

//
//GameobjectDataBase::GameobjectDataBase()
//{
////MAX_COUNT_ELEMENT = 1000; // serverID 
//
////for (int i = 0; i < MAX_COUNT_ELEMENT; i++)
////	list_freeServerID.push_back(i);
//}



//					CLASS	GameobjectDataBase
//int GameobjectDataBase::getServerId()
//{
//	int serverId;
//	if (!list_freeServerID.empty())
//	{
//		it1 = list_freeServerID.begin();		// итератор на первый эл-т
//		serverId = *it1;						// получили значение 
//		it1 = list_freeServerID.erase(it1);		// удалили из "первой очереди" 
//		list_work_serverId.push_back(serverId);	// переброслили во вторую очередь
//		return serverId;						// а это можно отправить клиенту
//	}
//	else
//	{
//		return -1;
//	}
//}
//
//void GameobjectDataBase::setFreeId(int ServerId)
//{
//	for (std::list<int>::iterator it = list_work_serverId.begin();
//		it != list_work_serverId.end(); ++it)
//	{
//		if (*it == ServerId)
//		{
//			if (!list_work_serverId.empty())
//			{
//				std::cout << "найденно " << *it << " удаляю\n";
//				it = list_work_serverId.erase(it);
//				list_freeServerID.push_back(ServerId);
//			}
//		}
//	}
//}
//
//void GameobjectDataBase::TEST_print_list_dim(int design)
//{
//	if (design == 1)
//	{
//		std::cout << "list_work_serverId: \t";
//		for (std::list<int>::iterator it = list_work_serverId.begin();
//			it != list_work_serverId.end(); ++it)
//			std::cout << ' ' << *it;
//		std::cout << '\n';
//	}
//	if (design == 2)
//	{
//		std::cout << "list_freeServerID: \t";
//		for (std::list<int>::iterator it = list_freeServerID.begin();
//			it != list_freeServerID.end(); ++it)
//			std::cout << ' ' << *it;
//		std::cout << '\n';
//	}
//}
//




 //===============================================
 






///* input: ptr struct		output init. struct for send */
//void cDataBase_Client_map::getAnswer(std::string paket, udp::endpoint &ep,
//	std::shared_ptr<ExternStructSend> ptrSendStruct)
//{
//	ptrSendStruct->m_byHost_ep = ep;					// ip клиентa от которого нам пришел пакет
//
//	// если обработка пакета не требуется то к его значению просто добавится хост отправителя
//	// иначе m_StrMsg перезапишется
//	ptrSendStruct->m_StrMsg = toString(ep.port()) + " " + paket;		// в начале пакета пишем от письмо, пример "65512 "
//	ptrSendStruct->m_bEverySend = true;
//	ptrSendStruct->m_bAnswer = true;
//
//	//	тут будут пропарсеная инфа
//	std::shared_ptr<std::list <double>> sharedLIst;						//	тут объявления указателя
//	sharedLIst = std::make_shared<std::list <double>>();				/* конструктор для типа через умный ptr */
//
//	boost::regex reg("(-+|)\\d+(,\\d+)*");								// умеет получать числа: ( отрицательные ) целые, дробные
//	for (boost::sregex_iterator it(paket.begin(), paket.end(), reg);
//		it != boost::sregex_iterator(); ++it)
//		sharedLIst->push_back(atof((*it).str().c_str()));				// ложим пропарсенные параметры в список
//
//	std::list<double>::iterator it = sharedLIst->begin();				// итератор на начало списка 
//
//	std::string strRez;
//	if (!sharedLIst->empty())
//	{
//		int count_prms = sharedLIst->size();
//
//		switch (count_prms)												// свич по кол-ву аргументов
//		{
//		case 1:
//
//			// int design = *it;
//			if ((int)(*it) == 100)										// if у нас просят serverID 
//			{
//				ptrSendStruct->m_StrMsg = "Answer " + toString(getServerId());
//				ptrSendStruct->m_bEverySend = false;
//			}
//
//			if ((int)(*it) == 0)										// 0 - клиент приславший 0 говорит о том что он 0-nline	 
//			{
//				std::cout << "[void] online" << ep.port() << "\n";
//				ptrSendStruct->m_bAnswer = false;
//			}
//			break;
//			//-------------------------------------
//
//		case 2:
//			if ((int)(*it) == 99)										// del по идеии итератор указывает на первый элемент
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
