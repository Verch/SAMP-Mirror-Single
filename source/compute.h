#pragma once

#include "VehicleManager.h"
#include "PlayerManager.h"
#include "EventManager.h"

struct possitions
{
	possitions(float x, float y, float z, float angle, float speed);
	//void setPossitions(float x, float y, float z, float angle, float speed);
	float fModel;

	float x;
	float y;
	float z;

	float angle;
	float speed;
};

class IBase
{
public:
	virtual float GetX() const = 0;
	virtual float GetY() const = 0;
	virtual float GetZ() const = 0;

	virtual void setPossitions(float x, float y, float z, float angle, float speed) const = 0;
};

class c_PosVehicle : public IBase
{
public:
	float GetX() const override;
	float GetY() const override;
	float GetZ() const override;
	void setPossitions(float x, float y, float z, float angle, float speed);
private:

	float m_fPosX;
	float m_fPosY;
	float m_fPosZ;

	float m_angle;
	float m_speed;
};
 
class c_Compute
{
public:
	c_Compute();
	~c_Compute();
		    
	double Distance(cPed &pos_Player1, c_Event &myEvent);
	double Distance(cPed &pos_Player1, cPed &pos_Player2);

	double Distance(CPoint3D Point1, CPoint3D Point2);


	//double DistancePlayerActorToWantVehicle(c_Player pos_Player, c_Vehicle Veh);
	 
	double DistanceStreamSee(IBase &A, IBase &B);
};
