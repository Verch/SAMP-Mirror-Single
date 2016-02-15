#pragma once
#include <string>
#include <vector>
#include <memory>
#include <thread>

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

class Server
{
public:
	void initialize();
	void run();

private:
	std::vector<std::thread> m_thread_group;
	std::vector<Client>      m_clients;
	boost::asio::ip::tcp::socket m_socket;
	boost::asio::io_service  m_service;
};