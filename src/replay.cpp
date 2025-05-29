#include "replay.h"
#include <sstream>
#include <iostream>

using namespace std;

//Constructor:
replay::replay() : indiceActual(0), cargado(false) {}

//Carga de los movimientos del archivo:

bool replay::cargar(const string& ruta) {

    ifstream file(ruta); //Abre el archivo

    if (!file.is_open()) {      //Comprobamos si el archivo se pudo abrir

        std::cerr << "No se pudo abrir el archivo: " << ruta << std::endl;
        return false;           //Devuelve false si falla la apertura

    }

    movimientos.clear();       //Limpia cualquier replay anterior
    indiceActual = 0;          //Reinicia el índice

    string linea;

    //Lee el archivo línea a línea
    while (getline(file, linea)) {

        std::istringstream ss(linea);
        Movimiento mov;
        float x1, y1, x2, y2;
        int id;

        //Espera leer: x1 y1 x2 y2 piezaID
        if (ss >> x1 >> y1 >> x2 >> y2 >> id) {
            mov.origen = vector2D(x1, y1);      //Posición inicial
            mov.destino = vector2D(x2, y2);     //Posición final
            mov.piezaID = id;                   //Identificador de la pieza
            movimientos.push_back(mov);         //Almacena el movimiento
        }

    }

    cargado = !movimientos.empty(); //Marca como cargado si hay datos. Ya que empty devuelve true si el 
                                    //vector está vacío

    return cargado;

}