#include "Mundo.h"
#include "freeglut.h"
#include <cmath>

void Mundo::rotarOjo()
{
	// probar rotacion en eje z
	/*double ang = atan2(y_ojo, x_ojo); // Plano XY 
	double dist = sqrt(x_ojo * x_ojo + y_ojo * y_ojo);
	ang += 0.05;
	x_ojo = dist * cos(ang);
	y_ojo = dist * sin(ang);*/

	if (jugador == 0) {
		x_ojo = 0;
		y_ojo = -10;
		z_ojo = 5;
	}
	else {
		x_ojo = 0;
		y_ojo = 10;
		z_ojo = 5;
	}
		
}
void Mundo::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
			0.0, 0, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 0.0, 1.0);      // definimos hacia arriba (eje Z)    
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
	y_ojo=-10;
	z_ojo=5;
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

	// Puedes seguir con torre, alfile, rey, etc.
	Piezas.push_back(new Torre(Vector3D(0, 0, 0), true));
	Piezas.push_back(new Torre(Vector3D(4, 5, 0), true));
}