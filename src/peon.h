#pragma once

#include "Pieza.h"

class Peon : public Pieza {

public:
    Peon(Vector3D pos, bool blanca);

    void dibuja(float tam_casilla, float offset_x, float offset_y) const override;

    bool movimiento_valido(Vector3D destino) const override;

};

