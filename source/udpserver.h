#pragma once
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <exception>

#include <iostream>
#include <string>

#include "DataBase.h"
#include "GameObject_List.h" 
#include "MyUtiles.h"


using namespace boost::posix_time;	//for millisec
using boost::asio::ip::udp;

class cUDP_Server
{
public:
	cUDP_Server(boost::asio::io_service &io_service, int ListenPort);
	~cUDP_Server();
	void start();

	void thrReceive();
	void chekClientTimeOut();

	std::string CreateAnswerForClient(const std::string& msg);

	std::shared_ptr	<cDataBase_Client_map> m_DataBasa;

	std::shared_ptr	<GameobjectDataBase> m_Game_db_Car;

	std::shared_ptr	<c_VehicleManager> m_Veh_Manager;
	  
private:
	void send_for(udp::endpoint &ep, const std::string& msg);
	void sendAll(const std::string& msg);

private:
	udp::socket	socket_;
};
