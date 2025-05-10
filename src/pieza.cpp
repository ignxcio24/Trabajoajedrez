#include "pieza.h"
#include "freeglut.h"
#include <fstream>
#include <iostream>

#include "peon.h"
#include "torre.h"
#include "caballo.h"
#include "alfil.h"
#include "reina.h"
#include "rey.h"

#include "reglas.h"

Pieza::Pieza() :
    size(1.0f),
    color(none),
    posicion(0.0f, 0.0f),
    seleccion(-1, -1), board({}),
    othermode(false)
{}
Pieza::~Pieza() {}

std::array<std::array<int, 6>, 5>& Pieza::getBoard() {
    return board;
}

Pieza* Pieza::createPiece(int pieceValue) const {
    if (pieceValue == 0)
        return nullptr;
    int type = abs(pieceValue);
    Pieza* piece = nullptr;
    switch (type) {
    case 1:
        piece = new Peon;
        break;
    case 2:
        piece = new Torre;
        break;
    case 3:
        piece = new Caballo;
        break;
    case 4:
        piece = new Alfil;
        break;
    case 5:
        piece = new Reina;
        break;
    case 6:
        piece = new Rey;
        break;
    default:
        break;
    }
    if (piece) {
        if (pieceValue < 0)
            piece->setColor(black);
        else
            piece->setColor(white);
    }
    return piece;
}
void Pieza::dibuja() const {
    for (int x = 0; x < 5; ++x) {
        for (int z = 0; z < 6; ++z) {
            int value = board[x][z];
            if (value == 0)
                continue;
            // Coronazion del peon
            if (value == 1 && z == 5) {
				value = 5; // Reina
                const_cast<std::array<std::array<int, 6>, 5>&>(board)[x][z] = value;
			}
			else if (value == -1 && z == 0) {
				value = -5; // Reina
                const_cast<std::array<std::array<int, 6>, 5>&>(board)[x][z] = value;
            }
            Pieza* piece = createPiece(value);
            if (!piece)
                continue;
            piece->setPosicion(x + 1, z + 1);
            if (x == static_cast<int>(seleccion.x) && z == static_cast<int>(seleccion.z)) {
                Color c = piece->color;
                c.a = 150;
                piece->setColor(c);
            }
            piece->dibujaIndividual();
            delete piece;
        }
    }
}
