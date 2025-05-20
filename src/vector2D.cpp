#include "vector2D.h"

// Constructor
vector2D::vector2D(float xi, float zi){
	x = xi;
	z = zi;
}

// Destructor
vector2D::~vector2D() {}

// Funcion de operador del modulo
float vector2D::modulo() const{
	return (float)sqrt(x * x + z * z);
}

// Funcion de operador del argumento
float vector2D::argumento() const{
	return (float)atan2(x, z);
}

// Funcion de operador de suma
vector2D vector2D::operator + (vector2D v) {
	return { x + v.x, z + v.z };
	/*
	vector2D res;
	res.x = x + v.x;
	res.z = z + v.z;
	return res;
	*/
}

// Funcion de operador de resta
vector2D vector2D::operator - (vector2D v){
	return { x - v.x, z - v.z };
}