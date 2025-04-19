#include "Tablero.h"
#include "Pieza.h"
#include "Peon.h"
#include <vector>

class Mundo
{
public: 
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
