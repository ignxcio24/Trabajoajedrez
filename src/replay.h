#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "vector2D.h"
#include "pieza.h"

struct Movimiento {

	vector2D origen;
	vector2D destino;
	int piezaID;

};

class replay
{

private:

	std::vector<Movimiento> movimientos; //Lista de movimientos le�dos del archivo
	size_t indiceActual;				 //�ndice del movimiento actual en reproducci�n
	bool cargado;						 //Indica si se ha cargado correctamente un archivo

public:

	//Constructor por defecto:
	replay();

	//Carga los movimientos del archivo
	bool cargar(const std::string& ruta = "lastgame");

	//Indica si hay m�s movimientos para reproducir
	bool haySiguiente() const;

	//Devolver� el siguiente movimiento y avanza el �ndice interno
	Movimiento siguiente();

	//Reinicia el �ndice, para comenzar de nuevo
	void reiniciar();

	//Acceso de solo lectura a todos los movimientos
	const std::vector<Movimiento>& getMovimientos() const;


};

