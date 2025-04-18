#pragma once
class Tablero
{
private:
	//Declaramos los atributos de las filas y las columnas 6x5(es fijo)
	int filas;
	int columnas;
	//Declaramos las variables que nos ayudaran a situarlo en el espacio
	//Son algo as� como "las referencias de las coordenadas en el tablero", es 
	//un punto en base al que construir el tablero
	double x_offset;
	double y_offset;
	//Declaramos la variable que nos dir� el tama�o de cada casilla
	double tam_casilla;

public:
	//Inicializamos un constructor
	//He puesto los valores que me han dado la gana, se pueden cambiar
	Tablero(int filas = 6, int columnas = 5, float x = 0.0f, float y = 0.0f, float tam = 1.0f);
	//Declaramos el m�todo dibuja que dibujar� nuestro tablero
	//Esta funci�n solo va a dibujar, por lo tanto, la declaro constante
	//Para que los datos de nuestro constructor no cambien
	void dibuja() const;


};

