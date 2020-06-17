#include "HRing.h"

HRing::HRing()
{
}

HRing::HRing(const Vector3D &p1, const Vector3D &p2, const Vector3D &perp)
{
	atoms[0] = p1;
	atoms[1] = p2;
	perpendicularV = perp;
	calc_positions();
}

HRing::~HRing()
{
}

void HRing::update(const Vector3D &p1, const Vector3D &p2, const Vector3D &perp, double rot_angle)
{
	atoms[0] = p1;
	atoms[1] = p2;
	perpendicularV = perp;
	
	//update perp vector with rotation angle to get new plane of ring
	Vector3D rot_axis = atoms[1] - atoms[0];
	perpendicularV.rotate(rot_axis, rot_angle);
	perpendicularV.normalize();

	//calculate new positions
	calc_positions();
}

Vector3D HRing::pass_perp()
{
	Vector3D across = atoms[5] - atoms[1];
	across.normalize();
	return across;
}

Vector3D HRing::pass_new_pos1()
{
	return atoms[5];
}

Vector3D HRing::pass_new_pos2()
{
	return atoms[4];
}

void HRing::calc_positions()
{
	//rotation constants
	double ctheta = 0.5;        //cos(60)
	double stheta = 0.8660254;  //sin(60)

	//orientations of ring
	Vector3D rotation_axis, addVector;

	//initial add vector initialization
	addVector = atoms[1] - atoms[0];
	
	//adding add vector 4 times to get all 6 atom positions
	rotation_axis = addVector % perpendicularV;
	rotation_axis.normalize();
	for (int i = 2; i < 6; i++)
	{
		addVector.rotate(rotation_axis, ctheta, stheta);
		addVector.normalize();
		atoms[i] = atoms[i - 1] + addVector;
	}
}