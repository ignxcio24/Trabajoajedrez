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

	std::vector<Movimiento> movimientos; //Lista de movimientos leídos del archivo
	size_t indiceActual;				 //Índice del movimiento actual en reproducción
	bool cargado;						 //Indica si se ha cargado correctamente un archivo

public:

	//Constructor por defecto:
	replay();

	//Carga los movimientos del archivo
	bool cargar(const std::string& ruta = "lastgame");

	//Indica si hay más movimientos para reproducir
	bool haySiguiente() const;

	//Devolverá el siguiente movimiento y avanza el índice interno
	Movimiento siguiente();

	//Reinicia el índice, para comenzar de nuevo
	void reiniciar();

	//Acceso de solo lectura a todos los movimientos
	const std::vector<Movimiento>& getMovimientos() const;


};

