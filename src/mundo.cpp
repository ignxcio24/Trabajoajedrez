#include "Mundo.h"
#include "freeglut.h"
#include <cmath>

void Mundo::rotarOjo()
{
	double dist=sqrt(x_ojo*x_ojo+z_ojo*z_ojo);
	double ang=atan2(z_ojo,x_ojo);
	ang+=0.05;
	x_ojo=dist*cos(ang);
	z_ojo=dist*sin(ang);
}
void Mundo::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
			0.0, 0, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    
	Tablero.dibuja();
	//aqui es donde hay que poner el codigo de dibujo
	//dibujo del suelo
	/*
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
		glColor3ub(255,0,0);
		glVertex3d(-5.0,0,-5.0);
		glVertex3d(-5.0,0,5.0);
		glColor3ub(255,255,0);
		glVertex3d(5.0,0,5.0);	
		glVertex3d(5.0,0,-5.0);
	glEnd();
	glEnable(GL_LIGHTING);
	*/

	float tam = Tablero.getTamCasilla();
	float offsetX = Tablero.getOffsetX();
	float offsetY = Tablero.getOffsetY();

	for (Pieza* p : Piezas)
		p->dibuja(tam, offsetX, offsetY);
}

void Mundo::mueve()
{

}

void Mundo::inicializa()
{
	x_ojo=0;
	y_ojo=10;
	z_ojo=20;
}

void Mundo::tecla(unsigned char key)
{

}

void Mundo::crearPiezas() {
	// Peones blancos
	for (int i = 0; i < 5; ++i)
		Piezas.push_back(new Peon(Vector3D(i, 1, 0), true));

	// Peones negros
	for (int i = 0; i < 5; ++i)
		Piezas.push_back(new Peon(Vector3D(i, 4, 0), true));

	// Puedes seguir con torres, alfiles, rey, etc.
}