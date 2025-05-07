#pragma once

#include "pieza.h"

class Caballo: public Pieza // Uso de la HERENCIA
{

public:
	// Constructor
	Caballo();

	// Destructor
	virtual ~Caballo();
	

	// Funcion que dibuja la pieza
	virtual void dibujaIndividual() const;

	// Funcion que mueve la pieza
	bool mueve();

};

