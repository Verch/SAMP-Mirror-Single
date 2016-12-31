#include "udpserver.h"


using namespace boost::posix_time;	//for millisec
using boost::asio::ip::udp;

cUDP_Server::cUDP_Server(boost::asio::io_service& io_service, int ListenPort) :
socket_(io_service, udp::endpoint(udp::v4(), ListenPort))
{
	std::cout << "cUDP_Server() create" << std::endl;
	std::cout << "[cUDP_Server::cUDP_Server] listen:" << ListenPort << "\n";

	int MAX_COUNT_OBJECT_VEHICLE = 66;

	m_DataBasa = std::make_shared<cDataBase_Client_map>();
	m_Veh_Manager = std::make_shared<c_VehicleManager>();

	m_Game_db_Car = std::make_shared<GameobjectDataBase>(MAX_COUNT_OBJECT_VEHICLE);
}


cUDP_Server::~cUDP_Server()
{
	std::cout << "[cUDP_Server::~cUDP_Server] destroy!" << std::endl;
}

void cUDP_Server::start()
{
	//boost::thread thrTimeOut(&cUDP_Server::thr_checkClientTimeOut, this);
	//thrTimeOut.detach();

	boost::thread thrrecov(&cUDP_Server::thrReceive, this);
	thrrecov.join(); //detach();
	// AHTUNG	thrrecov.join() <=> while(true)
}

void cUDP_Server::chekClientTimeOut()
{
	for (auto it = m_DataBasa->m_map_client.begin();
		it != m_DataBasa->m_map_client.end(); ++it)
	{
		ptime now = microsec_clock::local_time();
		long long ms = (now - (*it).second.last_ping).total_milliseconds();
		if (ms > 5000)
		{
			m_DataBasa->closeSocket_map((*it).second.ep.port());
			break;	// lol ? 
		}
	}
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

			// refresh ip list  
			m_DataBasa->refresh_ip_List(remote_endpoint);

			// Print Input Package
			std::cout << "[cUDP_Server::thrReceive] " << remote_endpoint.address() << remote_endpoint.port() << " <- \'"<< msg << "\'\n";
			 
			// create Answer
			std::string package = CreateAnswerForClient(msg);
			 
			// send All Answer
			sendAll(package);

			// call system kick  Client TimeOut
			chekClientTimeOut();

			//-----------------------------------------------------------------------------------
		}
		catch (std::exception &e) { std::cerr << "Exception: " << e.what() << "\n"; }
	}
}

std::string cUDP_Server::CreateAnswerForClient(const std::string& msg)
{
	std::string answer("Unknow Answer");

	unsigned int	unBox_clientPassport = 0; // not reliz
	float			unBox_design = 0;
	float			unBox_want_ModelCar = 0;
	float 			unBox_xPos = 0;
	float 			unBox_yPos = 0;
	float 			unBox_zPos = 0;

	if (msg.length() >= 8) // clientPasport + design = 8 (bytes)
	{
		if (msg.length() == 24) // count prms = 6
		{
			std::stringstream byteArr(msg);

			byteArr.read((char*)&unBox_clientPassport, 4);
			byteArr.read((char*)&unBox_design, 4);
			byteArr.read((char*)&unBox_want_ModelCar, 4);
			byteArr.read((char*)&unBox_xPos, 4);
			byteArr.read((char*)&unBox_yPos, 4);
			byteArr.read((char*)&unBox_zPos, 4);
			 
			//print Input Package
			printf("\n[cUDP_Server::CreateAnswerForClient] Decompose Package"
				" \n\tclientPassport = %d"
				" \n\tdesign = %f"
				" \n\tmodelCar = %f"
				" \n\tx = %f \n\ty = %f \n\tz = %f\n"
				"------------------------------\n"
				, unBox_clientPassport
				, unBox_design
				, unBox_want_ModelCar
				, unBox_xPos
				, unBox_yPos
				, unBox_zPos
				);
     
			// control valid data
			if (unBox_want_ModelCar >= 400 && unBox_want_ModelCar <= 602)
			{
				// get server info database
				int servCarID = m_Game_db_Car->getServerId();

				// refresh data vase
				m_Veh_Manager->refresh_vehicle_map(
					servCarID
					, (int)unBox_want_ModelCar
					, unBox_xPos
					, unBox_yPos
					, unBox_zPos
					);
				c_MyUtiles myUtites;

				std::string package = myUtites.floatToHEX(unBox_design) + m_Veh_Manager->getHexInfoCarID(servCarID);
				return package;
			}
		}
	}
	return answer;
}




void cUDP_Server::sendAll(const std::string& msg)
{
	for (auto it = m_DataBasa->m_map_client.begin(); it != m_DataBasa->m_map_client.end(); ++it)
	{

		//printf("[cUDP_Server::thrReceive] sendAnswer/'%s/'", msg.c_str());
		std::cout << "[cUDP_Server::sendAll] '" << msg  << "'\n";
		std::cout << "-------------------------" << "\n\n";
		boost::system::error_code ignored_error;
		socket_.send_to(boost::asio::buffer(msg), it->second.ep, 0, ignored_error);
	}
}

void cUDP_Server::send_for(udp::endpoint& ep, const std::string& msg)
{
	boost::system::error_code ignored_error;
	socket_.send_to(boost::asio::buffer(msg), ep, 0, ignored_error);
}


//std::shared_ptr<ExternStructSend> ptrSendStruct;	//	ptr
//ptrSendStruct = std::make_shared<ExternStructSend>();

//void cUDP_Server::send(std::shared_ptr<ExternStructSend> ptrSendStruct)
//{
//	if (ptrSendStruct->m_bAnswer) // если сообщение требует ответа
//	{
//		if (ptrSendStruct->m_bEverySend) // отправить каждому подключенному
//			for (auto it = m_DataBasa->m_map_client.begin(); it != m_DataBasa->m_map_client.end(); ++it)
//				send_for(/* кому */ it->second.ep, /* что */ ptrSendStruct->m_StrMsg);
//
//		else // отправить таму, от кого пришло
//			send_for(ptrSendStruct->m_byHost_ep, ptrSendStruct->m_StrMsg);
//
//	}
//}
//==================================================================================================
