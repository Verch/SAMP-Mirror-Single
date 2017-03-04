#pragma once

//#include "udpserver.h"
//#include "EventManager.h"

#include "udpserver.h"
#include <iostream>

#include <ctime>

#include <chrono>
#include <windows.h>

//get the system time (unix)

	 
int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");
	 
	try
	{
		std::cout << "Server is start new build " << "\n";
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
 