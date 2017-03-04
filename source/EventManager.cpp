#include "EventManager.h"
//
//#include <iostream>
//


c_Event::c_Event(int iType, int AttachToID, float x, float y, float z)
		: m_iType(iType)
	, m_AttachToID(AttachToID)
	, m_fPosX(x)
	, m_fPosY(y)
	, m_fPosZ(z)
{

}
		
//c_EventManager::c_EventManager()
//{
//}
//
//void c_EventManager::addEvent(c_Event GameEvent)
//{
//	m_Event.push_back(GameEvent);
//}
//
//void c_EventManager::printMatrixEvent()
//{
//	for (int i = 0; i < m_Event.size(); i++)
//	{
//
//		printEvent(m_Event, i);
//	}
//}
//
//void c_EventManager::printEvent(std::vector<c_Event> Event, int index)
//{
//	std::cout << "" << Event[index].m_fPosX << "\n";
//	std::cout << "" << Event[index].m_fPosY << "\n";
//	std::cout << "" << Event[index].m_fPosZ << "\n";
//}
//
//void c_EventManager::addEventVehiclePossitionsControl(c_Vehicle vehilce)
//{
//	c_Event VehPos(vehilce.m_fX, vehilce.m_fY, vehilce.m_fZ);
//	addEvent(VehPos);
//}
//
//void c_EventManager::send_Event()
//{
//	for (int i = 0; i < m_Event.size(); i++)
//	{
//		
//	}
//}