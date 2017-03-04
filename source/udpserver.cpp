#include "udpserver.h"


using namespace boost::posix_time;	//for millisec
using boost::asio::ip::udp;

cUDP_Server::cUDP_Server(boost::asio::io_service& io_service, int ListenPort) :
socket_(io_service, udp::endpoint(udp::v4(), ListenPort))
{
	std::cout << "[cUDP_Server::cUDP_Server()] Create! ListenPort = " << ListenPort << std::endl;

	//Game_setting gameSetting(50);
	//m_GameLogic = std::make_shared<cGameLogic>();
	//m_DataBasa = std::make_shared<c_DataBaseClient_map>();

	m_Logic = std::make_shared<c_Logic>();
}

cUDP_Server::~cUDP_Server()
{
	std::cout << "[cUDP_Server::~cUDP_Server] destroy!" << std::endl;
}

void cUDP_Server::start()
{
	boost::thread thrrecov(&cUDP_Server::thrReceive, this);
	thrrecov.join(); //detach();	// AHTUNG	thrrecov.join() <=> while(true)

	//boost::thread thrTimeOut(&cUDP_Server::thr_checkClientTimeOut, this);
	//thrTimeOut.detach();
}


void cUDP_Server::thrReceive()
{
	while (true)
	{
		try
		{
			char buff[1024];

			boost::asio::ip::udp::endpoint remote_endpoint;
			boost::system::error_code error;

			size_t len = socket_.receive_from(boost::asio::buffer(buff), remote_endpoint, 0, error);
			std::string msg(buff, len);

			if (error && error != boost::asio::error::message_size)
				throw boost::system::system_error(error);

			// ----------------------------------------------------------------------------------
			std::cout << "<- " << remote_endpoint.address() << ":" << remote_endpoint.port()
				<< " ( receiver size byte = " << msg.length() << ") ";

			m_Logic->m_DataBase->refresh_ip_List(remote_endpoint);

			m_Logic->parsing_package(msg, remote_endpoint);

			m_Logic->m_DataBase->updateEvent();

			std::string answer = "Hello KRACHIK";

			sendByServer(remote_endpoint, answer);

			//-----------------------------------------------------------------------------------
		}
		catch (std::exception &e) { std::cerr << "KRACHIK Exception: " << e.what() << "\n"; }
	}
}

//void cUDP_Server::sendAll(const std::string& msg)
//{
//printf("[cUDP_Server::thrReceive] sendAnswer/'%s/'", msg.c_str());
/*std::cout << "[cUDP_Server::sendAll] '" << msg << "'\n";
std::cout << "-------------------------" << "\n\n";*/

/*for (auto it = m_DataBasa->m_Client_map.begin(); it != m_DataBasa->m_Client_map.end(); ++it)
{
boost::system::error_code ignored_error;
socket_.send_to(boost::asio::buffer(msg), it->second.ep, 0, ignored_error);
}*/
//}

void cUDP_Server::sendByServer(udp::endpoint& ep, const std::string& msg)
{
	boost::system::error_code ignored_error;
	socket_.send_to(boost::asio::buffer(msg), ep, 0, ignored_error);
}


//
//void cUDP_Server::chekClientTimeOut()
//{
//	for (auto it = m_DataBasa->m_Client_map.begin();
//		it != m_DataBasa->m_Client_map.end(); ++it)
//	{
//		ptime now = microsec_clock::local_time();
//		long long ms = (now - (*it).second.last_ping).total_milliseconds();
//		if (ms > 5000)
//		{
//			m_DataBasa->closeSocket_map((*it).second.ep.port());
//
//			//m_GameLogic->m_Player_Manager->remove_Player_Game_Info((*it).second.ep.port());
//			break;	// lol ? 
//		}
//	}
//}