#pragma once


enum eTypeGameObject
{
	VEHICLE = 1
};

class c_Event
{
public:
	c_Event(int iType, int AttachToID, float x, float y, float z);

public:

	int m_iType;
	int m_AttachToID;

	float m_fPosX;
	float m_fPosY;
	float m_fPosZ;
};



//#include <vector>
	//int m_iType;
//c_Event(float x, float y, float z, int type);
//
//
//class c_EventManager
//{
//
//public:
//	c_EventManager();
//	 
//	void addEventVehiclePossitionsControl(c_Vehicle vehilce);
//
//	void sendEventEveryClient();
// 
//	void printMatrixEvent();
//
//	void send_Event();
//
//private:
//	void addEvent(c_Event GameEvent);
//
//	void printEvent(std::vector<c_Event> Event, int index);
// 
//private:
//	std::vector<c_Event> m_Event;
//};

