#pragma once
#include "Pieza.h"
class Torre :public Pieza
{
public:
	// Constructor y destructor
	Torre();
	virtual ~Torre();

	// M�todos, el primero derivaci�n de la clase Pieza
	virtual void dibujaIndividual() const;
	bool mueve();

};

