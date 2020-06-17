#pragma once
#include <cmath>

class Vector3D
{
public:
	//public member data
	double x, y, z;
	
	//constructors
	Vector3D();
	Vector3D(double a, double b, double c);
	~Vector3D();

	//public member functions
	double Vlen() const;
	double VlenSq() const;
	void normalize();
	void rotate(const Vector3D &axis, double angle);
	void rotate(const Vector3D &axis, double ctheta, double stheta);

	//public operation definitions
	Vector3D operator+ (const Vector3D &v);  //vector addition
	Vector3D operator- (const Vector3D &v);  //vector subtraction
	Vector3D operator%(const Vector3D &v);  //cross product
	double operator* (const Vector3D &v);    //dot product
	Vector3D operator*(double s);      //scalar multiplication (case for vector * scalar)
	friend Vector3D operator*(double s, const Vector3D &v);  //scalar multiplication (case for scalar * vector)

private:
	//private member functions
	double Vlenyz() const;
};