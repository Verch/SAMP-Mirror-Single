//udp_sync_echo_server.cpp
#include <iostream>
using namespace std;

#ifdef WIN32
#define _WIN32_WINNT 0x0501
#include <stdio.h>
#endif

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
using namespace boost::asio;
using namespace boost::posix_time;
io_service service;
void handle_connections() {
	char buff[1024];
	ip::udp::socket sock(service, ip::udp::endpoint(ip::udp::v4(), 8001));
	while (true) {
		ip::udp::endpoint sender_ep;
		int bytes = sock.receive_from(buffer(buff), sender_ep);
		std::string msg(buff, bytes);
		sock.send_to(buffer(msg), sender_ep);
	}
}
int main(int argc, char* argv[]) {
	std::cout << "udp_sync_echo_server.cpp port 8001" << endl;
	handle_connections();
}











//#define BOOST_ASIO_SEPARATE_COMPILATION 
/*

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iostream>

using namespace std;
using namespace boost::asio;
//io_service service;
*/







/*// Асинхроный вызов
void func(int i)
{
	std::cout << "func called, i= " << i << std::endl;
}
void worker_thread()
{
	service.run();
}

int main(int argc, char* argv[])
{
	for (int i = 0; i < 10; ++i)
		service.post(boost::bind(func, i));

	boost::thread_group threads;
	for (int i = 0; i < 3; ++i)
		threads.create_thread(worker_thread);
	// wait for all threads to be created
	boost::this_thread::sleep(boost::posix_time::millisec(500));
	threads.join_all();
	system("pause");
}
*/


/*// асинхроный последовательный вызов 
void func(int i)
{
	std::cout << "func called, i= " << i << "/" << boost::this_thread::get_id() << std::endl;
}
void worker_thread()
{
	service.run();
}
int main(int argc, char* argv[])
{
	io_service::strand strand_one(service), strand_two(service);
	for (int i = 0; i < 5; ++i)
		service.post(strand_one.wrap(boost::bind(func, i)));
	
	for (int i = 5; i < 10; ++i)
		service.post(strand_two.wrap(boost::bind(func, i)));
	
	boost::thread_group threads;
	for (int i = 0; i < 3; ++i)
		threads.create_thread(worker_thread);	// wait for all threads to be created

	boost::this_thread::sleep(boost::posix_time::millisec(500));
	threads.join_all();

	system("pause");
	return 1;
}*/




/*//посмотрим как service.dispatch влияет на результат :
void func(int i)
{
	std::cout << "func called, i= " << i << std::endl;
}

void run_dispatch_and_post()
{
	for (int i = 0; i < 10; i += 2)
	{
		service.dispatch(boost::bind(func, i));
		service.post(boost::bind(func, i + 1));
	}
}
int main(int argc, char* argv[])
{
	service.post(run_dispatch_and_post);
	service.run();
	system("pause");
	return 0;
}*/






/*//Теперь давайте поговорим об service.wrap(handler).wrap() возвращает функтор, который может быть использован 
//в качестве аргумента другой функции :
void dispatched_func_1()
{
	std::cout << "dispatched 1" << std::endl;
}
void dispatched_func_2()
{
	std::cout << "dispatched 2" << std::endl;
}
void test(boost::function<void()> func)
{
	std::cout << "test" << std::endl;
	service.dispatch(dispatched_func_1);
	func();
}
void service_run()
{
	service.run();
}
int main(int argc, char* argv[])
{
	test(service.wrap(dispatched_func_2));
	boost::thread th(service_run);
	boost::this_thread::sleep(boost::posix_time::millisec(500));
	th.join();
	system("pause");
	return 0; 
}*/



//Следующий код это простой асинхронный сервер :
/*using boost::asio;
typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
io_service service;
ip::tcp::endpoint ep(ip::tcp::v4(), 2001)); // listen on 2001
ip::tcp::acceptor acc(service, ep);
socket_ptr sock(new ip::tcp::socket(service));
start_accept(sock);
service.run();
void start_accept(socket_ptr sock)
{
	acc.async_accept(*sock, boost::bind(handle_accept, sock, _1));
}
void handle_accept(socket_ptr sock, const boost::system::error_code & err)
{
	if (err) return;
	// at this point, you can read/write to the socket
	socket_ptr sock(new ip::tcp::socket(service));
	start_accept(sock);
}*/


//-------------------------------------

 /*Например, следующее сообщение от вашего партнера должно прийти к вам через 100 миллисекунд:

bool read = false;
void deadline_handler(const boost::system::error_code &) 
{
    std::cout << (read ? "read successfully" : "read failed") << std::endl;
}
void read_handler(const boost::system::error_code &) 
{
    read = true;
}
ip::tcp::socket sock(service);
…
read = false;
char data[512];
sock.async_read_some(buffer(data, 512));
deadline_timer t(service, boost::posix_time::milliseconds(100));
t.async_wait(&deadline_handler);
service.run();
*/


/*
.run() всегда будет закончен, если больше нет операций для контроля
Если вы хотите, чтобы service.run() продолжил работать, вы должны предоставить ему больше работы. 
решения данной проблемы.  является увеличение нагрузки на connect_handler, запустив еще одну асинхронную операцию.
Второй способ заключается в имитации некоторой его работы, используя следующий код:
typedef boost::shared_ptr<io_service::work> work_ptr;
work_ptr dummy_work(new io_service::work(service_));

Приведенный выше код обеспечит постоянную работу service_.run() до тех пор пока вы не вызовете 
useservice_.stop() или dummy_work.reset(0); // destroy dummy_work.
*/