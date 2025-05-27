#pragma once
#include "vector2D.h"
#include "color.h"
#include "losa.h"
#include <vector>
#include <array>
#include "ETSIDI.h"
class Tablero
{
private:
	vector2D limite;
	Color color;
	std::array<std::array<Losa, 6>, 5> tiles;

public:
	// Constructor y destructor
	Tablero();
	virtual ~Tablero();

	// Método que devuelve el tamaño del tablero
	std::array<std::array<Losa, 6>, 5>& getTiles();

	// Métodos para dibujar y resetear el color de las casillas del tablero
	void dibuja() const;
	void resetTileColors();
};