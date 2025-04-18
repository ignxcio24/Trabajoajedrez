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
	gluLookAt(2.5f, 2.0f, 11.0f,  // posicion del ojo
			2.5f, 2.15f, 0.0f,      // hacia que punto mira  (0,0,0) 
			0.0f, 1.0f, 0.0f);      // definimos hacia arriba (eje Y)    

	//LLamamos al tablero
	tablero.dibuja();
	
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
