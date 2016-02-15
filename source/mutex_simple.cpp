#include <iostream>
#include <cstdlib>
#include <ctime>
#include "RandString.h" 

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>

#include <sstream>
#include <algorithm>

#include <vector>
boost::mutex io_mutex;

struct MyStruct
{
	char *str;
	int priority;

	bool operator< (const MyStruct& a) const
	{
		return priority > a.priority;
	}
};


std::vector <MyStruct> v;  
MyStruct messages;  
RandString obj;

void show()
{
	for (std::vector<MyStruct>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << (it->priority) << "\t" << (it->str) << std::endl;
}


void ThereadDaTaArival()
{
	for (int i = 0; i < 10; i++)
	{
		obj.SerStrPriorityRand();
		obj.SetRandStr();

		messages.priority = obj.GetStrPriority();
		messages.str = obj.GetStr();
		v.push_back(messages);
	}

	std::cout << "до сортировки \n";
	show();

	std::cout << "\n\n\n\nпосле  сортировки \n";
	std::sort(v.begin(), v.end());    
	show();


} 

void Reader()
{
	 
}

  
int main()
{
	setlocale(LC_ALL, "Russian");

	// fake message
	boost::thread thrd(&ThereadDaTaArival);
	thrd.join();
	 
	system("pause");
}

//std::cout << "priority: " << obj.Get_StrPriority() << "\t" << obj.GetStr() << std::endl

 