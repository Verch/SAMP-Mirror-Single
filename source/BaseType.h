#pragma once 
  
class CPoint3D
{
public:
	CPoint3D() {};

	CPoint3D(float x, float y, float z);

	void Set(float x, float y, float z)
	{
		m_X = x;
		m_Y = y;
		m_Z = z;
	}

	void Set(CPoint3D point3D)
	{
		m_X = point3D.m_X;
		m_Y = point3D.m_Y;
		m_Z = point3D.m_Z;
	}


	CPoint3D Get() { return *this; }

	float GetX() { return m_X; }
	float GetY() { return m_Y; }
	float GetZ() { return m_Z; }


private:
	float m_X = 0.0f;
	float m_Y = 0.0f;
	float m_Z = 0.0f;

};
 