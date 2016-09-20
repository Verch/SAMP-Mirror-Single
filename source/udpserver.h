#pragma once

#include <functional>
#include <algorithm>
#include <iostream>
#include <string>
#include <time.h>
#include <stack>
#include <list>
#include <map>



#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace boost::posix_time;	//for millisec
using boost::asio::ip::udp;


struct ExternStructSend
{
	bool						m_bAnswer;
	bool						m_bEverySend;
	std::string					m_StrMsg;
	udp::endpoint				m_byHost_ep;
};

class cDataBase
{
public:
	cDataBase();
	~cDataBase();

	void			refresh_map_client(udp::endpoint &ep); // refresh ping
	void			closeSocket_map(int port);

	struct db_client  
	{
		db_client(udp::endpoint& _ep) : ep(_ep) {  }
		udp::endpoint	ep;
		ptime			last_ping;
	};
	
	void			getAnswer(std::string paket, udp::endpoint &ep,
		std::shared_ptr<ExternStructSend> ptrSendStruct);


	void			setFreeId(int ServerId);
	int				getServerId();
	std::string		toString(int number);

	void			TEST_print_list_dim(int design);	// del

	std::map	<int, struct db_client>		m_map_client;

private:

	int MAX_COUNT_ELEMENT;
	std::list<int> list_work_serverId;
	std::list<int> list_freeServerID;
	std::list<int>::iterator it1;
};


class cPacketDecompose // not reliz
{
public:
	cPacketDecompose();
	~cPacketDecompose();
	void calculate_regular_parse_packed(std::string paket);
	//bool		packedDecomposeByClient(ClienInfo* forBox, udp::endpoint &ep, std::string packet);
	//bool		initializeStruct(ClienInfo* forBox, udp::endpoint &ep, std::string packet);
};

class cUDP_Server
{
public:
	cUDP_Server(boost::asio::io_service &io_service);
	cUDP_Server();
	~cUDP_Server();
	 
	void		recov();
	void		send(std::shared_ptr<ExternStructSend> ptrSendStruct);
	void		send_for(udp::endpoint &ep, const std::string& msg);
	void		sendAll(std::string msg);
	void		chekClientTimeOut();

	std::shared_ptr			<cDataBase>			m_DataBasa;
	std::shared_ptr		<cPacketDecompose>		m_PacketDecompose;

private:
	udp::socket									socket_;
};

void	 handle_clients_thread(cUDP_Server *curserv);
void	 theread_Chek_ClientTimeOut(cUDP_Server *curserv);