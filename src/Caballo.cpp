#include "caballo.h"
#include "freeglut.h"


// Constructor de la clase Caballo
Caballo::Caballo()
{
	size = 1.0f;
}


// Destructor de la clase Caballo
Caballo::~Caballo(){}


// Funcion para mover el caballo
bool Caballo mueve() {
	return true;
}


// Funcion para dibujar el caballo
void Caballo::dibujaIndividual() const {
    glPushMatrix();
    glTranslatef(posicion.x, 0.4f, posicion.z);
    glColor4ub(color.r, color.g, color.b, color.a);
    GLUquadric* quad = getSharedQuadric();
    glRotatef(90, 0, -1, 0);
    glRotatef(90, -1, 0, 0);
    gluDisk(quad, 0.0f, size * 0.32f, 8, 1);
    gluCylinder(quad, size * 0.32f, size * 0.32f, size * 0.08f, 8, 8);
    glTranslatef(0.0f, 0.0f, size * 0.08f);
    gluDisk(quad, 0.0f, size * 0.32f, 8, 1);
    gluCylinder(quad, size * 0.26f, size * 0.26f, size * 0.08f, 8, 8);
    glTranslatef(0.0f, 0.0f, size * 0.08f);
    gluDisk(quad, 0.0f, size * 0.26f, 8, 1);
    gluCylinder(quad, size * 0.2f, size * 0.112f, size * 0.56f, 8, 8);
    glTranslatef(0.0f, 0.0f, size * 0.56f);
    gluDisk(quad, 0.0f, size * 0.112f, 8, 1);
    glRotatef(-90, -1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glTranslatef(0.0f, 0.0f, -size * 0.04f);

    if ((color.r == black.r) && (color.g == black.g) && (color.b == black.b)) {
        glTranslatef(0.0f, 0.0f, size * 0.08f);
        glRotatef(180, 0, -1, 0);
    }

}


