#pragma once
#include "Vector3D.h"

class HRing
{
public:
	//public member data
	Vector3D atoms[6];
	//constructors & destructors
	HRing();
	HRing(const Vector3D &p1, const Vector3D &p2, const Vector3D &perp);
	~HRing();

	//operations on ring
	void update(const Vector3D &p1, const Vector3D &p2, const Vector3D &perp, double rot_angle);
	Vector3D pass_perp();
	Vector3D pass_new_pos1();
	Vector3D pass_new_pos2();

private:
	//private member data
	Vector3D perpendicularV;
	//private member functions
	void calc_positions();
};