#pragma once

#include "pieza.h"

class Peon : public Pieza {
public:
    Peon();
    virtual ~Peon();

    virtual void dibujaIndividual() const;//dibuja peon
    bool mueve();
};