#include "RandString.h" 

#include <iostream>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <fstream>



RandString::RandString()
{
	passLenght = 32;
	srand(time(0));
	m_StrPriority = rand() % 3;
	SetRandStr();
}



RandString::RandString(int passLenght_, int m_StrPriority_)
{
	passLenght = passLenght_;
	m_StrPriority = m_StrPriority;
	SetRandStr();
}

char* RandString::SetRandStr()
{
	int i;
	for (i = 0; i < passLenght; ++i)
	{
		numOfChars(passLenght);
		passGenerator(passLenght);
		m_RandStr[i];
	}
	m_RandStr[i] = '\0';
	return m_RandStr;
}

void RandString::passGenerator(int passLenght)
{
	m_RandStr = new char[passLenght];

	for (int i = 0; i < numOfNumbers; ++i) 
	{
		m_RandStr[i] = char(rand() % 10 + 48);
	}
	for (int i = numOfNumbers; i < numOfNumbers + numOfBigChars; ++i) 
	{
		m_RandStr[i] = char(rand() % 26 + 65);
	}
	for (int i = numOfNumbers + numOfBigChars; i < passLenght; ++i) 
	{
		m_RandStr[i] = char(rand() % 26 + 97);
	}
	std::random_shuffle(m_RandStr, m_RandStr + passLenght);
}

void RandString::numOfChars(int passLenght)
{
	numOfSmallChars = rand() % passLenght;
	int charRandEnd = passLenght - numOfSmallChars;
	numOfBigChars = rand() % charRandEnd;
	numOfNumbers = passLenght - numOfSmallChars - numOfBigChars;
}

char*	RandString::GetStr()
{
	return m_RandStr;
}

int RandString::GetStrPriority()
{
	return m_StrPriority;
}

void RandString::SerStrPriority(int prms)
{
	m_StrPriority = prms;
}
void RandString::SerStrPriorityRand()
{
	m_StrPriority = rand() % 3;
}
