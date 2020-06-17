#include "Vector3D.h"



Vector3D::Vector3D()
{
}

Vector3D::Vector3D(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
}

Vector3D::~Vector3D()
{
}

double Vector3D::Vlen() const 
{
	return sqrt(x*x + y*y + z*z);
}

double Vector3D::VlenSq() const
{
	return (x*x + y*y + z*z);
}

double Vector3D::Vlenyz() const
{
	return sqrt(y*y + z*z);
}

void Vector3D::normalize()
{
	double norm = Vlen();
	x /= norm;
	y /= norm;
	z /= norm;
}

void Vector3D::rotate(const Vector3D &axis, double angle)
{
	double costheta = cos(angle);
	double sintheta = sin(angle);
	rotate(axis, costheta, sintheta);
}

void Vector3D::rotate(const Vector3D &axis, double ctheta, double stheta)
{
	double holdx, holdy, holdz;
	double d = axis.Vlenyz();

	/*rotation by Rx. Conditional for case rotation axis already on x-axis */
	if (d != 0)
	{
		holdx = x;
		holdy = (1.0 / d) * ((y * axis.z) - (z * axis.y));
		holdz = (1.0 / d) * ((y * axis.y) + (z * axis.z));
	}
	else
	{
		holdx = x;
		holdy = y;
		holdz = z;
	}

	//second rotation by Ry
	x = (holdx * d) - (axis.x * holdz);
	y = holdy;
	z = (holdx * axis.x) + (holdz * d);

	//rotation by theta (theta about z-axis --> z-axis has become axis of rotation)
	holdx = (x * ctheta) - (y * stheta);
	holdy = (x * stheta) + (y * ctheta);
	holdz = z;

	//inverse rotation of Ry
	x = (d * holdx) + (axis.x * holdz);
	y = holdy;
	z = (d * holdz) - (axis.x * holdx);

	//inverse rotation of Rx
	if (d != 0)
	{
		y = (1.0 / d) * ((axis.z * y) + (axis.y * z));
		z = (1.0 / d) *((z * axis.z) - (axis.y * holdy));
	}
}

Vector3D Vector3D::operator+(const Vector3D &v)
{
	return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D Vector3D::operator-(const Vector3D &v)
{
	return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D Vector3D::operator%(const Vector3D &v)
{
	double newx = y * v.z - z * v.y;
	double newy = z * v.x - x * v.z;
	double newz = x * v.y - y * v.x;
	return Vector3D(newx, newy, newz);
}

double Vector3D::operator*(const Vector3D &v)
{
	return (x*v.x + y*v.y + z*v.z);
}

Vector3D Vector3D::operator*(double s)
{
	return Vector3D(s*x, s*y, s*z);
}

Vector3D operator*(double s, const Vector3D &v)
{
	return Vector3D(s*v.x, s*v.y, s*v.x);
}
