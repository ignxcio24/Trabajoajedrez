#pragma once
#include <math.h>
class vector2D
{
public:
	float x, z;

	// Constructor y destructor
	vector2D(float xi=0.0f, float zi=0.0f);
	virtual ~vector2D();

	// M�todos m�tem�ticos
	float modulo() const; 
	float argumento() const; 

	// Operadores de suma y resta
	vector2D operator + (vector2D v);
	vector2D operator - (vector2D v);
};