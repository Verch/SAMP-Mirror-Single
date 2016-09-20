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

using boost::asio::ip::udp;
 
 void handle_clients_thread(cUDP_Server *serv)
 {
	 while (true)
	 {
		 (*serv).recov();
		 boost::this_thread::sleep(millisec(11));
	 }
 }

 void theread_Chek_ClientTimeOut(cUDP_Server *serv)
 {
	 std::cout << "theread_Chek_ClientTimeOut" << "\n";
	 while (true)
	 {
		 (*serv).chekClientTimeOut();
		 boost::this_thread::sleep(millisec(11));
	 }
 }

 int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");

	try
	{
		boost::asio::io_service io_service;
		cUDP_Server server(io_service);
		boost::thread trd0(&handle_clients_thread,		&server);
		boost::thread trd1(&theread_Chek_ClientTimeOut, &server);
		trd0.join();
		trd1.join();

	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	  
	printf("\n");
	system("pause");
	return 0;
}
 






  