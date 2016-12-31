#pragma once

//#include <map>
//#include <string>
//#include <iostream>
//#include <functional>
//
//#include <boost/array.hpp>
//#include <boost/asio.hpp>
//#include <exception>
//
//#include <boost/bind.hpp>
//#include <boost/thread.hpp>
//#include <boost/shared_ptr.hpp>

#include "udpserver.h"
#include "GameObject_List.h"
#include "MyUtiles.h"

using boost::asio::ip::udp;



int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");

	try
	{
		boost::asio::io_service io_service;
		cUDP_Server server(io_service, 7778);
		server.start();
	}

	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}


	printf("\n");
	system("pause");
	return 0;
}

