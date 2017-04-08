#pragma once
 
#include "udpserver.h"
#include <iostream>
#include "MyUtiles.h"

/*#include <ctime>

#include <chrono>
#include <windows.h>
 */ 	 
int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");
	 
	try
	{
		
		std::cout << "Server MirrorSync3 is start [04.04.2017 gl steep, 08:32]" << "\n";
		std::cout << "dir: " << getMeDirectory () << "\n\n";
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
 