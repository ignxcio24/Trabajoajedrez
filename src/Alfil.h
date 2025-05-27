#pragma once

#include "pieza.h"

class Alfil : public Pieza {
public:
    Alfil();//constructor
    virtual ~Alfil();//destructor

    virtual void dibujaIndividual() const;//dibuja la pieza
    bool mueve();//permite mover la pieza
};
