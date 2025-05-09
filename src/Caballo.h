#pragma once

#include "pieza.h"

class Caballo : public Pieza { // Uso de la HERENCIA
public:
    // CONSTRUCTOR
    Caballo();

    // DESTRUCTOR
    virtual ~Caballo();

    // FUNCION QUE DIBUJA LA PIEZA
    virtual void dibujaIndividual() const;

    // FUNCION QUE MUEVE LA PIEZA
    bool mueve();

};