#pragma once
#include <vector>
#include <string>
#include "MyUtiles.h"

class c_Vehicle;
class  cPed;
  	   
enum eTypeGameObject
{
	VEHICLE = 1,
	PLAYER = 2
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

public:

	void update(float x, float y, float z)
	{
		m_fPosX = x;
		m_fPosY = y;
		m_fPosZ = z;

	}
};

  
//-------------------------------------------------------------------
class c_EventManager
{ 
public:
	c_EventManager()
	{
		Log("[c_EventManager::c_EventManager] Create!");
	}

	void Event_push_back(c_Event GameEvent);

	int  getCountEvent();
	 
	void  DebugprintMatrixEvent();

	void  printEvent(std::vector<c_Event> Event, int index);

	void  addEventVehiclePossitionsControl(c_Vehicle vehilce);

	void  addEventPlayerActorPossitionsControl(cPed Ped);

	bool  updateEventPlayerPossitions(cPed ped);
	 
   
private:
	std::vector<c_Event> m_Event;
 
};

//-----------------------------------------------------------------------

 