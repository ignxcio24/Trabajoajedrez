#pragma once
#include "Pieza.h"
class Torre :public Pieza
{
public:
	// Constructor y destructor
	Torre();
	virtual ~Torre();

	// Métodos, el primero derivación de la clase Pieza
	virtual void dibujaIndividual() const;
	bool mueve();

};

