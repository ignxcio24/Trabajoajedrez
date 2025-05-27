#include "tablero.h"
#include "color.h"
#include "freeglut.h"
#include <vector>
#include "losa.h"
#include <array>

// Constructor del tablero
Tablero::Tablero(): 
color(border), limite({ 6, 7 }) 
{
	for (int j = 0; j < 6; ++j) {
		for (int i = 0; i < 5; ++i) {
			tiles[i][j].setPosicion(i, j);
			bool isBtile = (i + j) % 2 == 0; 
			if (isBtile) {
				tiles[i][j].setColor({ btile.r, btile.g, btile.b, btile.a });
			}
			else {
				tiles[i][j].setColor({ wtile.r, wtile.g, wtile.b, wtile.a });
			}
		}
	}
}

// Destructor del tablero
Tablero::~Tablero() {}


// M�todo que dibuja el tablero
void Tablero::dibuja() const {
	
	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fondo.png").id);
	glDisable(GL_LIGHTING);
	glTexCoord2d(0, 1); glVertex2d(-10, 0);
	glTexCoord2d(1, 1); glVertex2d(10, 0);
	glTexCoord2d(1, 0); glVertex2d(10, 15);
	glTexCoord2d(0, 0); glVertex2d(-10, 15);
	glBegin(GL_QUADS);
	// Abajo
	glNormal3f(0.0f, -1.0f, 0.0f);
	glColor4ub(color.r, color.g, color.b, color.a);
	glVertex3f(0, 0, limite.z);
	glVertex3f(limite.x, 0, 0);
	glVertex3f(limite.x, 0, limite.z);
	glVertex3f(0, 0, limite.z);
	// Arriba
	glNormal3f(0.0f, 1.0f, 0.0f);
	glColor4ub(color.r+7, color.g+7, color.b+7, color.a);
	glVertex3f(0, 0.39f, 0);
	glVertex3f(limite.x, 0.39f, 0);
	glVertex3f(limite.x, 0.39f, limite.z);
	glVertex3f(0, 0.39f, limite.z);
	// Adelante
	glNormal3f(0.0f, 0.0f, 1.0f);
	glColor4ub(color.r-7, color.g-7, color.b-7, color.a);
	glVertex3f(0, 0, limite.z);
	glVertex3f(limite.x, 0, limite.z);
	glVertex3f(limite.x, 0.39f, limite.z);
	glVertex3f(0, 0.39f, limite.z);
	// Atras
	glNormal3f(0.0f, 0.0f, -1.0f);
	glColor4ub(color.r-7, color.g-7, color.b-7, color.a);
	glVertex3f(0, 0, 0);
	glVertex3f(limite.x, 0, 0);
	glVertex3f(limite.x, 0.39f, 0);
	glVertex3f(0, 0.39f, 0);
	// Izquierda
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glColor4ub(color.r-7, color.g-7, color.b-7, color.a);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, limite.z);
	glVertex3f(0, 0.39f, limite.z);
	glVertex3f(0, 0.39f, 0);
	// Derecha
	glNormal3f(1.0f, 0.0f, 0.0f);
	glColor4ub(color.r-7, color.g-7, color.b-7, color.a);
	glVertex3f(limite.x, 0, 0);
	glVertex3f(limite.x, 0, limite.z);
	glVertex3f(limite.x, 0.39f, limite.z);
	glVertex3f(limite.x, 0.39f, 0);
	glEnd();
	for (const auto& i : tiles) {
        for (const auto& tile : i) {
            tile.dibuja();
        }
    }
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

// M�todo que devuelve una referencia a la matriz de losas del tablero
std::array<std::array<Losa, 6>, 5>& Tablero::getTiles() {
	return tiles;
}

// M�todo que restablece los colores de las losas de informaci�n de movimiento del tablero
void Tablero::resetTileColors() {
	for (int j = 0; j < 6; ++j) {
		for (int i = 0; i < 5; ++i) {
			bool isBtile = (i + j) % 2 == 0;
			if (isBtile) {
				tiles[i][j].setColor({ btile.r, btile.g, btile.b, btile.a });
			}
			else {
				tiles[i][j].setColor({ wtile.r, wtile.g, wtile.b, wtile.a });
			}
		}
	}
}