#pragma once

#include <functional>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace boost::posix_time;	//for millisec
using boost::asio::ip::udp;

class cUDP_Server
{
public:
	cUDP_Server(boost::asio::io_service &io_service);
	cUDP_Server();
	// global dim
	struct ClienInfo
	{
		std::string		ip;
		int				port;
		ptime			last_ping;

		float			speed[2];
		float			pos[2];
	};

	//					funcs	 
	void		recov();
	void		refresh_map_remote_endpoint(udp::endpoint &ep);
	void		refreshMapPingByIp(udp::endpoint &ep);
	void		deleteSocket(int keyPortforMap);
	void		chekClientTimeOut();
	void		sendAll(std::string msg);

private:
	//boost::asio::io_service		&io_service;
	udp::socket								socket_;
	std::map	<int, udp::endpoint>		m_map_remote_endpoint;
	std::map	<int, struct ClienInfo>		m_struct_map;

	ClienInfo	m_clienInfoStruct;
};


void	 handle_clients_thread(cUDP_Server *curserv);
void	 theread_Chek_ClientTimeOut(cUDP_Server *curserv);


