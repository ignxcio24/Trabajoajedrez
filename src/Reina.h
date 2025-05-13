#pragma once

#include "pieza.h"

class Reina : public Pieza {
public:
	// CONSTRUCTOR
    Reina();

	// DESTRUCTOR
    virtual ~Reina();

	// FUNCION QUE DIBUJA LA REINA
    virtual void dibujaIndividual() const;

	// FUNCION QUE MUEVE LA REINA
    bool mueve();
};
