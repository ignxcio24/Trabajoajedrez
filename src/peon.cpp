#include "Peon.h"
#include "Tablero.h"
Peon::Peon(Vector3D pos, bool blanca) : Pieza(pos, blanca) {}

void Peon::dibuja(float tam_casilla, float offset_x, float offset_y) const {
    glPushMatrix();

    glTranslatef(posicion.x * tam_casilla + tam_casilla / 2 + offset_x,
        posicion.y * tam_casilla + tam_casilla / 2 + offset_y,
        0.1f);

    if (es_blanca)
        glColor3f(1.0f, 1.0f, 1.0f);
    else
        glColor3f(0.1f, 0.1f, 0.1f);

    glutSolidCube(0.8f);
    glPopMatrix();
}


bool Peon::movimiento_valido(Vector3D destino) const {
    // Movimiento simple hacia adelante (sin capturas ni primer doble paso)
    if (es_blanca)
        return (destino.x == posicion.x) && (destino.y == posicion.y + 1);
    else
        return (destino.x == posicion.x) && (destino.y == posicion.y - 1);
}
