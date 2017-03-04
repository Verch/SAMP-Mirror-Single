#include <iostream>

#include "compute.h"
#include <math.h>


//float c_PosObject::GetX() const{ return m_fPosX; }
//float c_PosObject::GetY() const { return m_fPosY; }
//float c_PosObject::GetZ() const { return m_fPosZ; }

float  c_PosVehicle::GetX() const { return m_fPosX; }
float  c_PosVehicle::GetY() const { return m_fPosY; }
float  c_PosVehicle::GetZ() const { return m_fPosZ; }

void c_PosVehicle::setPossitions(float x, float y, float z, float angle, float speed)
{
	m_fPosX = x;
	m_fPosY = y;
	m_fPosZ = z;

	m_speed = speed;
	m_angle = angle;
}




possitions::possitions(float _x, float _y, float _z, float _angle, float _speed)
	: x(_x), y(_y), z(_z), angle(_angle), speed(_speed)
{	}

c_Compute::c_Compute(){}

c_Compute::~c_Compute(){}

double c_Compute::Distance(cPed &pos_Player1, c_Event &myEvent)
{
	
	double Distance =
		sqrt(pow((pos_Player1.m_fX -   myEvent.m_fPosX), 2.0))
		+ sqrt(pow((pos_Player1.m_fY - myEvent.m_fPosY), 2.0))
		+ sqrt(pow((pos_Player1.m_fZ - myEvent.m_fPosZ), 2.0));
	return Distance;
}

double c_Compute::DistanceStreamSee(IBase &pos_A, IBase &pos_B)
{
	//std::cout << "[cGameLogic::ComputeDistanceStreamSee]" << "\t";
	double Distance =
		sqrt(pow((pos_A.GetX() - pos_B.GetX()), 2.0))
		+ sqrt(pow((pos_A.GetY() - pos_B.GetY()), 2.0))
		+ sqrt(pow((pos_A.GetZ() - pos_B.GetZ()), 2.0));

	//std::cout << " Distance  = " << Distance << "\n";


	return Distance;
}


//
//double c_Compute::DistancePlayerActorToWantVehicle(c_Player pos_Player, c_Vehicle posVeh)
//{
//
//	double Distance =
//		sqrt(pow((pos_Player.m_fX - posVeh.m_fX), 2.0))
//		+ sqrt(pow((pos_Player.m_fY - posVeh.m_fY), 2.0))
//		+ sqrt(pow((pos_Player.m_fZ - posVeh.m_fZ), 2.0));
//	return Distance;
//}
//
//double c_Compute::DistanceWithPlayerSeePlayer(c_Player &pos_Player1, c_Player &pos_Player2)
//{
//
//	double Distance =
//		sqrt(pow((pos_Player1.m_fX - pos_Player2.m_fX), 2.0))
//		+ sqrt(pow((pos_Player1.m_fY - pos_Player2.m_fY), 2.0))
//		+ sqrt(pow((pos_Player1.m_fZ - pos_Player2.m_fZ), 2.0));
//
//	return Distance;
//}

//std::cout << "[cGameLogic::ComputeDistanceStreamSee]" << "\t";
//std::cout << " Distance  = " << Distance << "\n";