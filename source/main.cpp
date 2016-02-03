#ifdef WIN32
#define _WIN32_WINNT 0x0501
#include <stdio.h>
#endif


#include <boost/thread.hpp>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
using namespace boost::asio;
using namespace boost::posix_time;
using boost::system::error_code;

io_service service;
size_t read_complete(char * buff, const error_code & err, size_t bytes) {
	if (err) return 0;
	bool found = std::find(buff, buff + bytes, '\n') < buff + bytes;
	// we read one-by-one until we get to enter, no buffering
	return found ? 0 : 1;
}
/*
void handle_connections() {
	ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8001));
	char buff[1024];
	while (true) {
		ip::tcp::socket sock(service);
		acceptor.accept(sock);
	
		int bytes = read(sock, buffer(buff),boost::bind(read_complete, buff, _1, _2));
		std::string msg(buff, bytes);
		sock.write_some(buffer(msg));
		std::cout << "<-" << msg << "\n";
		sock.close();
	}
}*/

int main(int argc, char* argv[]) {
	std::cout << "Server is start\n";



	//SOCKET usersList[MAX_CLIENTS];   massiv dlia spiska soketov podcliuchenny`kh clientov

	//acceptor.accept(sock);
	//usersList[usersCount] = clientSocket;

	/*for (int i = 0; i<MAX_CLIENTS; i++) //funktciia peressy`lki soobshchenii` vsem, krome sebia 
	{
		if (usersList[i] != INVALID_SOCKET) // && usersList[i]!=arr[i]
			send(usersList[i], buffer, strlen(buffer), 0); //* 
	}*/



	ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8001));
	char buff[1024];
	while (true) {
		ip::tcp::socket sock(service);
		acceptor.accept(sock);

		int bytes = read(sock, buffer(buff), boost::bind(read_complete, buff, _1, _2));
		std::string msg(buff, bytes);
		sock.write_some(buffer(msg));
		std::cout << "<-" << msg << "\n";
		sock.close();
	}

//	handle_connections();
}
