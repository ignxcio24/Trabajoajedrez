#include "Torre.h"
#include "Tablero.h"
Torre::Torre(Vector3D pos, bool blanca) : Pieza(pos, blanca) {}

void Torre::dibuja(float tam_casilla, float offset_x, float offset_y) const {
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


bool Torre::movimiento_valido(Vector3D destino) const {
    // Movimiento simple hacia adelante y atras
    if (es_blanca)
        return ((destino.x == posicion.x) && (destino.y != posicion.y)) || ((destino.x != posicion.x) && (destino.y == posicion.y));
    else
        return ((destino.x == posicion.x) && (destino.y != posicion.y)) || ((destino.x != posicion.x) && (destino.y == posicion.y));
}