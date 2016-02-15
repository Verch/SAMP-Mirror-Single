#pragma once


class RandString
{
public:
	RandString();
	RandString(int passLenght, int StrPriority);

	char*	SetRandStr();


	char*	GetStr();
	int 	GetStrPriority();

	void	SerStrPriority(int);
	void	SerStrPriorityRand();

	void	passGenerator(int);
	void	numOfChars(int);
private:
	int		passLenght;
	int		numOfSmallChars;
	int		numOfBigChars;
	int		numOfNumbers;

	char*	m_RandStr;
	int		m_StrPriority;
};