  
#pragma once

#include "boost/asio.hpp"

#include <string>

class Sender
{
public:
	explicit Sender();
	 
	void send_for(boost::asio::ip::udp::endpoint& ep, const std::string& msg);
  
private:
	boost::asio::io_service        _service;
	boost::asio::ip::udp::endpoint _endpoint;
	boost::asio::ip::udp::socket   _socket;
};


