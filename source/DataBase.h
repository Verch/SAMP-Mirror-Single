#pragma once
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>

#include <functional>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>



//#include "udpserver.h"


//class GameobjectDataBase
//{
//public:
//	void	setFreeId(int ServerId);
//	int		getServerId();
//	void	TEST_print_list_dim(int design);	// [debug]
//
//private:
//	int MAX_COUNT_ELEMENT;
//	std::list<int> list_work_serverId;
//	std::list<int> list_freeServerID;
//	std::list<int>::iterator it1;
//};
//





class cDataBase_Client_map
{
public:
	cDataBase_Client_map();
	~cDataBase_Client_map();

	void	refresh_ip_List(boost::asio::ip::udp::endpoint &ep); // refresh ping
	void	closeSocket_map(int port);

public:
	struct client
	{
		client(boost::asio::ip::udp::endpoint& _ep) : ep(_ep) {  }
		boost::asio::ip::udp::endpoint	ep;
		boost::posix_time::ptime		last_ping;
	};

	std::map <int, struct client>	m_map_client;

	// My Utiles
	std::string	toString(int number);
private:
};




