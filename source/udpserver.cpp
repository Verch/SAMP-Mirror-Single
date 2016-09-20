#pragma once
#include <map>
#include <list>
#include <string>
#include <iostream>
#include <functional>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <exception>

#include <boost/bind.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "udpserver.h"


using namespace boost::posix_time;	//for millisec
using boost::asio::ip::udp;

cUDP_Server::cUDP_Server(boost::asio::io_service& io_service) :
socket_(io_service, udp::endpoint(udp::v4(), 7777))
{
	std::cout << "cUDP_Server() create" << std::endl;

	m_DataBasa = std::make_shared<cDataBase>();
	m_PacketDecompose = std::make_shared<cPacketDecompose>();
}

cUDP_Server::~cUDP_Server()
{
	std::cout << "~cUDP_Server() destroy" << std::endl;
}

void cUDP_Server::chekClientTimeOut()
{
	//-------------------------------------

	for (auto it = m_DataBasa->m_map_client.begin();
		it != m_DataBasa->m_map_client.end(); ++it)
	{
		ptime now = microsec_clock::local_time();
		long long ms = (now - (*it).second.last_ping).total_milliseconds();
		if (ms > 5000)
		{
			m_DataBasa->closeSocket_map((*it).second.ep.port());
			break;	//? 
		}
	}


}

void cUDP_Server::recov()
{
	try
	{

		char buff[1024];
		boost::asio::ip::udp::endpoint remote_endpoint;

		boost::system::error_code error;// Receive client query
		size_t len = socket_.receive_from(boost::asio::buffer(buff), remote_endpoint, 0, error);
		std::string msg(buff, len);

		if (error && error != boost::asio::error::message_size)
			throw boost::system::system_error(error);

		// ----------------------------------------------------------------------------------
		m_DataBasa->refresh_map_client(remote_endpoint); 	// refresh ip list  


		std::shared_ptr<ExternStructSend> ptrSendStruct;	//	ptr
		ptrSendStruct = std::make_shared<ExternStructSend>();

		m_DataBasa->getAnswer(msg, remote_endpoint, ptrSendStruct);

		send(ptrSendStruct);

		std::cout << "<- " << remote_endpoint.address() << remote_endpoint.port() << "  " << msg << "\n";
		//-----------------------------------------------------------------------------------
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}

void cUDP_Server::sendAll(std::string msg)
{
	for (auto it = m_DataBasa->m_map_client.begin(); it != m_DataBasa->m_map_client.end(); ++it)
	{
		boost::system::error_code ignored_error;
		socket_.send_to(boost::asio::buffer(msg), it->second.ep, 0, ignored_error);
	}
}



void cUDP_Server::send(std::shared_ptr<ExternStructSend> ptrSendStruct)
{
	if (ptrSendStruct->m_bAnswer) // если сообщение требует ответа
	{
		if (ptrSendStruct->m_bEverySend) // отправить каждому подключенному
			for (auto it = m_DataBasa->m_map_client.begin(); it != m_DataBasa->m_map_client.end(); ++it)
				send_for(/* кому */ it->second.ep, /* что */ ptrSendStruct->m_StrMsg);

		else // отправить таму, от кого пришло
			send_for(ptrSendStruct->m_byHost_ep, ptrSendStruct->m_StrMsg);

	}
}

void cUDP_Server::send_for(udp::endpoint& ep, const std::string& msg)
{
	boost::system::error_code ignored_error;
	socket_.send_to(boost::asio::buffer(msg), ep, 0, ignored_error);
}

//==================================================================================================

// конструктор
cDataBase::cDataBase()
{
	MAX_COUNT_ELEMENT = 1000; // serverID 

	for (int i = 0; i < MAX_COUNT_ELEMENT; i++)
		list_freeServerID.push_back(i);

	std::cout << "cDataBase() create" << "\n";
}

// деструктор
cDataBase::~cDataBase()
{
	std::cout << "~cDataBase() destroy" << "\n";
}

int cDataBase::getServerId()
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

void cDataBase::setFreeId(int ServerId)
{
	for (std::list<int>::iterator it = list_work_serverId.begin();
		it != list_work_serverId.end(); ++it)
	{
		if (*it == ServerId)
		{
			if (!list_work_serverId.empty())
			{
				std::cout << "найденно " << *it << " удаляю\n";
				it = list_work_serverId.erase(it);
				list_freeServerID.push_back(ServerId);
			}
		}
	}
}

void cDataBase::TEST_print_list_dim(int design)
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

std::string		cDataBase::toString(int number)
{
	int _forAitoaRadix = 10;
	char _forbuffer[20];
	char *p = _itoa(number, _forbuffer, _forAitoaRadix);
	//std::string rez = (std::string)p
	return (std::string)p;
}

/* input: ptr struct		output init. struct for send */
void cDataBase::getAnswer(std::string paket, udp::endpoint &ep,
	std::shared_ptr<ExternStructSend> ptrSendStruct)
{
	ptrSendStruct->m_byHost_ep = ep;					// ip клиентa от которого нам пришел пакет

	// если обработка пакета не требуется то к его значению просто добавится хост отправителя
	// иначе m_StrMsg перезапишется
	ptrSendStruct->m_StrMsg = toString(ep.port()) + " " + paket;		// в начале пакета пишем от письмо, пример "65512 "
	ptrSendStruct->m_bEverySend = true;
	ptrSendStruct->m_bAnswer = true;

	//	тут будут пропарсеная инфа
	std::shared_ptr<std::list <double>> sharedLIst;						//	тут объявления указателя
	sharedLIst = std::make_shared<std::list <double>>();				/* конструктор для типа через умный ptr */

	boost::regex reg("(-+|)\\d+(,\\d+)*");								// умеет получать числа: ( отрицательные ) целые, дробные
	for (boost::sregex_iterator it(paket.begin(), paket.end(), reg);
		it != boost::sregex_iterator(); ++it)
		sharedLIst->push_back(atof((*it).str().c_str()));				// ложим пропарсенные параметры в список

	std::list<double>::iterator it = sharedLIst->begin();				// итератор на начало списка 

	std::string strRez;
	if (!sharedLIst->empty())
	{
		int count_prms = sharedLIst->size();

		switch (count_prms)												// свич по кол-ву аргументов
		{
		case 1:

			// int design = *it;
			if ((int)(*it) == 100)										// if у нас просят serverID 
			{
				ptrSendStruct->m_StrMsg = "отдать serverID " + toString(getServerId());
				ptrSendStruct->m_bEverySend = false;
			}

			if ((int)(*it) == 0)										// 0 - клиент приславший 0 говорит о том что он 0-nline	 
			{
				std::cout << "[void] флаг присутствия от: " << ep.port() << "\n";
				ptrSendStruct->m_bAnswer = false;
			}

			break;

			//-------------------------------------

		case 2:
			if ((int)(*it) == 99)										// del по идеии итератор указывает на первый элемент
			{
				std::cout << "нас просят освободить серверИд" << "\n";
				it++;
				std::cout << "его значение есть: " << *it << "\n";
			}

			break;

			//-------------------------------------

		default: std::cout << "чет сломалось:" << "\n";  break;

		}
		}
	}

	void cDataBase::refresh_map_client(udp::endpoint &ep)
	{
		int keyPort = ep.port();
		auto it = std::find_if(m_map_client.begin(), m_map_client.end(),
			[&keyPort](const std::pair<int, struct db_client> &p)
		{
			return p.first == keyPort;
		});

		if (it != m_map_client.end())
		{	// new info by client	
			(*it).second.last_ping = microsec_clock::local_time(); // update Ping
		}
		else
		{// register 
			db_client tmp(ep); // for box
			tmp.last_ping = microsec_clock::local_time();
			m_map_client.insert(std::pair<int, struct db_client>(keyPort, tmp));

			std::cout << "connect " << ep.address().to_string()
				<< ":" << keyPort << std::endl;
		}
	}

	void cDataBase::closeSocket_map(int keyPort)
	{
		auto it = std::find_if(m_map_client.begin(),
			m_map_client.end(), [&keyPort]
			(const std::pair<int, struct db_client > &p)
		{
			return p.first == keyPort;
		});

		if (it != m_map_client.end())
		{
			std::cout << "socket" << (*it).second.ep.port() << " удален из очереди" << "\n";
			m_map_client.erase(it);
		}

	}
	//==================================================================================================

	cPacketDecompose::cPacketDecompose()
	{
		std::cout << "cPacketDecompose() create" << "\n";
	}

	cPacketDecompose::~cPacketDecompose()
	{
		std::cout << "~cPacketDecompose() destroy" << "\n";
	}

	void cPacketDecompose::calculate_regular_parse_packed(std::string paket)
	{



	}

	/*
	int cUDP_Server::generateServerId()
	{
	// rand number
	unsigned long int  min = 0, max = 4294967294;
	int newServerID = rand() % (max - min + 1) + min;

	if (!findServerCarId(newServerID)) // number !E
	{
	if (isCarCountNorm())	// if  Count Car < const
	{
	// Register
	serverVehicle veh;							// for box
	veh.keyServerId = newServerID;			// box prms
	m_ServerCarMap.insert(std::pair<int, serverVehicle>(newServerID, veh));	// push
	return  newServerID;
	}
	else
	{
	std::cout << "нет свободных слотов!" << "\n";
	return -2;
	}
	}
	else
	{
	std::cout << "загаданный id уже занят" << "\n";
	return -1;
	}
	}
	bool cUDP_Server::findServerCarId(unsigned long int key) // isFindServerCarId = false if id E
	{
	auto it = std::find_if(m_ServerCarMap.begin(), m_ServerCarMap.end(),
	[&key](const std::pair<int, serverVehicle> &p)
	{
	return p.first == key;
	});

	if (it != m_ServerCarMap.end())// new info by client
	return true;
	else
	{
	// register
	return false;
	}
	}//-------------------------------------


	void cUDP_Server::incServerIdCarCount()
	{
	m_curServerIdCarCount++;		//std::cout << "bool incCurServerIdCarCount() \t m_curServerIdCarCount=" << m_curServerIdCarCount << "\n";
	}

	bool	cUDP_Server::isCarCountNorm()
	{
	if (m_curServerIdCarCount <= m_MAX_SERVER_CAR_ID)
	return true;
	return false;
	}
	*/
