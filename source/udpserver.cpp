#pragma once

#include <map>
#include <string>
#include <iostream>
#include <functional>
  
#include <boost/array.hpp>
#include <boost/asio.hpp>
 #include <exception>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
 
#include "udpserver.h"


using namespace boost::posix_time;	//for millisec
using boost::asio::ip::udp;
 
cUDP_Server::cUDP_Server(boost::asio::io_service& io_service) :
socket_(io_service, udp::endpoint(udp::v4(), 7777))
{
	std::cout << "Starting UDP server..." << std::endl;
}

void cUDP_Server::deleteSocket(int keyPort)
{
	auto it = std::find_if(m_map_remote_endpoint.begin(), m_map_remote_endpoint.end(), [&keyPort]
		(const std::pair<int, udp::endpoint> &p)
	{
		return p.first == keyPort;
	});

	if (it != m_map_remote_endpoint.end())
	{
		std::cout << "socket" << (*it).second.port() << " удален из очереди" << "\n";
		m_map_remote_endpoint.erase(it);
	}
}

void cUDP_Server::chekClientTimeOut()
{
	for (auto it = m_struct_map.begin(); it != m_struct_map.end(); ++it)
	{
		ptime now = microsec_clock::local_time();
		long long ms = (now - (*it).second.last_ping).total_milliseconds();
		if (ms > 5000)
		{
			deleteSocket((*it).second.port);
			it = m_struct_map.erase(it);
			break;	//? 
		}
	}
}

void cUDP_Server::refresh_map_remote_endpoint(udp::endpoint &ep)
{
	int _port = ep.port();
	auto it = std::find_if(m_map_remote_endpoint.begin(), m_map_remote_endpoint.end(),
		[&_port](const std::pair<int, udp::endpoint > &p)
	{
		return p.first == _port;
	});

	if (it != m_map_remote_endpoint.end())	{}
	else
	{ // element not found
		m_map_remote_endpoint.insert(std::pair<int, udp::endpoint >(_port, ep));
		std::cout << "connect " << ep.address().to_string() << ":" << _port << std::endl;
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
		refresh_map_remote_endpoint(remote_endpoint);
		refreshMapPingByIp(remote_endpoint);

		sendAll(msg);
		//-----------------------------------------------------------------------------------
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}

void cUDP_Server::refreshMapPingByIp(udp::endpoint &ep)
{
	int keyPort = ep.port();
	auto it = std::find_if(m_struct_map.begin(), m_struct_map.end(),
		[&keyPort](const std::pair<int, struct ClienInfo> &p)
	{
		return p.first == keyPort;
	});

	if (it != m_struct_map.end())
	{	// new info by client	
		(*it).second.last_ping = microsec_clock::local_time(); // update Ping
	}
	else
	{// register 
		m_clienInfoStruct.ip = ep.address().to_string();
		m_clienInfoStruct.port = keyPort;
		m_clienInfoStruct.last_ping = microsec_clock::local_time();

		m_struct_map.insert(std::pair<int, struct ClienInfo>(keyPort, m_clienInfoStruct));
	}
}

void cUDP_Server::sendAll(std::string msg)
{
	socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
	for (auto it = m_map_remote_endpoint.begin(); it != m_map_remote_endpoint.end(); ++it)
	{
		boost::system::error_code ignored_error;
		socket_.send_to(boost::asio::buffer(msg), it->second, 0, ignored_error);

		//	ahtung, logic error
		//	if (ignored_error && ignored_error != boost::asio::error::not_connected)
		//	throw boost::system::system_error(ignored_error);
	}
}

