#include "Vector3D.h"
#include <cmath>
#include <iostream>
double Vector3D::modulo() const {
	return (sqrt(x * x + y * y + z * z));
}

Vector3D Vector3D::unitario() const
{
	auto mod = modulo();
	if (mod > 0.00001) {
		return { x / mod, y / mod, z / mod };
	}
	else
		return { x, y, z };
}

Vector3D Vector3D::operator - (const Vector3D& v) const
{
	return { x - v.x , y - v.y , z - v.z};
}
Vector3D Vector3D::operator + (const Vector3D& v) const
{
	return { x + v.x , y + v.y, z + v.z };
}
double Vector3D::operator *(const Vector3D& v) const {
	return{ x * v.x + y * v.y + z * v.z };
}
Vector3D Vector3D::operator *(double p) const {
	return{ p * x,p * y,p * z };
}
Vector3D operator * (double f, const Vector3D& v) {
	return { v.x * f, v.y * f ,v.z * f};
}
Vector3D operator /(const Vector3D& v, double f) {
	return { v.x / f,v.y / f, v.z / f };
}