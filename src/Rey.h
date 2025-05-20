#pragma once

#include "pieza.h"

class Rey : public Pieza {
public:
    // Contructor y destructor
    Rey();
    virtual ~Rey();

    // Métodos para dibujarse y moverse
    virtual void dibujaIndividual() const;
    bool mueve();
};