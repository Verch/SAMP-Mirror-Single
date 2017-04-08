#pragma once
#include "MyUtiles.h"

#include <functional>
#include <algorithm>
#include <iostream>
#include <string>
#include <list>
#include <map>
 
class GameobjectDataBase
{
public:
	GameobjectDataBase(int MAX_COUNT_OBJECT);

	void	setFreeId(int ServerId);
	int		getServerID();
	void	TEST_print_list_dim(int design);	// [debug]

private:
	int MAX_COUNT_OBJECT;
	std::list<int> list_work_serverId;
	std::list<int> list_freeServerID;
	std::list<int>::iterator it1;
};

  


