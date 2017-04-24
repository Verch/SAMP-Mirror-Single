#include "EventManager.h"
 
#include "PlayerManager.h"
#include "VehicleManager.h"
#include <iostream>

   
/*
class c_CLEO_Object_pool
{
public:
c_CLEO_Object_pool();

void register_By_key_ServId(const c_ClientVehicle & _obj);

void del(const c_ClientVehicle & _obj);

bool empty() { return m_Vehicle_vec.empty(); }

private:

std::vector<c_ClientVehicle> m_Vehicle_vec;
int m_curr_index;
};
*/


c_Event::c_Event(int iType, int AttachToID, float x, float y, float z)
		: m_iType(iType)
	, m_AttachToID(AttachToID)
	, m_fPosX(x)
	, m_fPosY(y)
	, m_fPosZ(z)
{

}
  
void c_EventManager::Event_push_back(c_Event GameEvent)
{
	m_Event.push_back(GameEvent);
}

void c_EventManager::printEvent(std::vector<c_Event> Event, int index)
{
	std::cout << "" << Event[index].m_fPosX << "\n";
	std::cout << "" << Event[index].m_fPosY << "\n";
	std::cout << "" << Event[index].m_fPosZ << "\n";
}

void c_EventManager::addEventVehiclePossitionsControl(c_Vehicle vehilce)
{
	c_Event Vehicle(eTypeGameObject::VEHICLE, vehilce.m_fServerID, vehilce.GetPossitions().GetX(), vehilce.GetPossitions().GetY(), vehilce.GetPossitions().GetZ());

	Event_push_back (Vehicle);
}

void c_EventManager::addEventPlayerActorPossitionsControl(cPed Ped)
{
	std::cout << "?"  << "\n";
	/*c_Event PlayerActorPossitions(eTypeGameObject::PLAYER, Ped.m_iKeyID, Ped.m_fX, Ped.m_fY, Ped.m_fZ);

	Event_push_back(PlayerActorPossitions);*/
}

bool c_EventManager::updateEventPlayerPossitions(cPed ped)
{
	if (m_Event.empty())
		return false;

	for (int i = 0; i < m_Event.size(); i++)
	{
		if (m_Event[i].m_iType != eTypeGameObject::PLAYER)
			continue;

		if (m_Event[i].m_AttachToID == ped.m_iKeyID)
		{

			std::cout << "Yeah!!!" << "\n";

			m_Event[i].update(ped.GetPossitions().GetX(), ped.GetPossitions().GetY(), ped.GetPossitions().GetZ());

			return true;
		}
	}

}


int c_EventManager::getCountEvent()
{
	if (m_Event.empty())
		return 0;
	return m_Event.size();
}

void c_EventManager::DebugprintMatrixEvent()
{
	for (int i = 0; i < m_Event.size(); i++)
	{
		printEvent(m_Event, i);
	}
}
