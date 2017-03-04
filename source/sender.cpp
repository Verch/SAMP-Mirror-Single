#include "sender.h"

#include <iostream>
#include <fstream>
#include <string>

Sender::Sender()
	: _service()
	, _endpoint(boost::asio::ip::udp::v4(), 0)
	, _socket(_service, _endpoint)
{
	//std::cout << "[Sender::Sender()]" << "\n";
	//_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 13666);
}

//void Sender::set_address(const std::string & ip, int port)
//{
//	_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ip), port);
//}
  
//void Sender::set_address_ep(boost::asio::ip::udp::endpoint&  ep) 
//{
//	_endpoint = ep;
//	//_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ip), port);
//}

//void Sender::send(const char * data, size_t length)
//{
//	//std::cout << "[void Sender::send( )] " << _endpoint.address() << _endpoint << ":" << _endpoint.port() << "\n";
//	_socket.send_to(boost::asio::buffer(data, length), _endpoint);
//}

//int Sender::getRemotePortCuurClient()
//{
//	return _endpoint.port();
//}
  
void Sender::send_for(boost::asio::ip::udp::endpoint& ep, const std::string& msg) 
{
	boost::system::error_code ignored_error;
	_socket.send_to(boost::asio::buffer(msg), ep, 0, ignored_error);
}

//void Sender::myBindEndpoint(boost::asio::ip::udp::endpoint& ep)
//{
//	//_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ep.address().from_string()), ep.port());
//}

//#include <boost/shared_ptr.hpp>
//#include <boost/array.hpp>
//#include <boost/asio.hpp>
//#include <boost/bind.hpp>
//#include <iostream>
//#include <string>
//#include <ctime>
// 
//using boost::asio::ip::udp;
//
//std::string make_daytime_string()
//{
//	using namespace std; // For time_t, time and ctime;
//	time_t now = time(0);
//	return ctime(&now);
//}
//
////c_Sender::c_Sender(boost::asio::io_service& io_service)
////	: socket_(io_service, udp::endpoint(udp::v4(), 7778))
// 
////
////void c_Sender::start_receive()
////{
////	//std::cout << "[start_receive]" << "\n";
////
////	socket_.async_receive_from(
////		boost::asio::buffer(recv_buffer_), remote_endpoint_,
////		boost::bind(&c_Sender::handle_receive, this,
////		boost::asio::placeholders::error,
////		boost::asio::placeholders::bytes_transferred));
////}
//
//void c_Sender::handle_receive(const boost::system::error_code& error, std::size_t  bytes_transferred)
//{
//	//std::cout << "[handle_receive]" << "\n";
//
//	if (!error || error == boost::asio::error::message_size)
//	{
//		boost::shared_ptr<std::string> message(new std::string(make_daytime_string()));
//		 	
//		//std::cout << "IP" << remote_endpoint_.address() << ":" << remote_endpoint_.port()
//			<< data << " size = " << bytes_transferred << "\n";
//
//		 
//		socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
//			boost::bind(&c_Sender::handle_send, this, message,
//			boost::asio::placeholders::error,
//			boost::asio::placeholders::bytes_transferred));
//
//		start_receive();
//	}
//}
//
//
//void c_Sender::handle_send(boost::shared_ptr<std::string>  message,
//	const boost::system::error_code&  error,
//	std::size_t  bytes_transferred)
//{
//
//}
//
//
