#include "Tablero.h"
#include "Pieza.h"
#include "Peon.h"
#include "Torre.h"
#include <vector>

class Mundo
{
public: 
	int jugador = 0;//si es 0, es el jugador 1, si es 1 es el 2
	Tablero Tablero;
	std::vector<Pieza*> Piezas; // Como Pieza, es una clase abstracta (para que podamos usar la clase sin 
								//saber el tipo de pieza a utilizar 
	
	void tecla(unsigned char key);
	void inicializa();
	void rotarOjo();
	void mueve();
	void dibuja();
	void crearPiezas();

	double x_ojo;
	double y_ojo;
	double z_ojo; 
};
