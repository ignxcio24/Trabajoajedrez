#pragma once
class Vector3D
{
public:
	double x{}, y{}, z{};
	Vector3D() : x(), y(), z() {}
	Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}
	double modulo() const; //modulo del vector
	Vector3D unitario() const; //devuelve un vector unitari
	Vector3D operator - (const Vector3D&) const; //resta de vectores
	Vector3D operator + (const Vector3D&) const; //suma de vectores
	double operator *(const Vector3D&) const; // producto escalar
	Vector3D operator *(double) const; // producto por un escalar
	friend Vector3D operator * (double f, const Vector3D& v);
	friend Vector3D operator /(const Vector3D& v, double f);

};

