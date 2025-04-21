#pragma once
#pragma once
#include "Vector3D.h"
#include <freeglut.h>

class Pieza {
protected:

    Vector3D posicion;  // Posición en el tablero
    bool es_blanca;     // true = blanca, false = negra
	friend class Peon; // Permite que la clase Peon acceda a los miembros protegidos de Pieza
    friend class Torre;// Permite que la clase torre acceda a los miembros protegidos de Pieza
public:
    Pieza(Vector3D pos, bool blanca) : posicion(pos), es_blanca(blanca) {}

    virtual void dibuja(float tam_casilla, float offset_x, float offset_y) const = 0; // Método abstracto para dibujar la pieza
    virtual bool movimiento_valido(Vector3D destino) const = 0; // A implementar en cada tipo de pieza

    Vector3D get_posicion() const { return posicion; }
    void set_posicion(Vector3D pos) { posicion = pos; }
    bool esBlanca() const { return es_blanca; }

    virtual ~Pieza() = default;
};

