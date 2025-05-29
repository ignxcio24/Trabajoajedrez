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
    indiceActual = 0;          //Reinicia el �ndice

    string linea;

    //Lee el archivo l�nea a l�nea
    while (getline(file, linea)) {

        std::istringstream ss(linea);
        Movimiento mov;
        float x1, y1, x2, y2;
        int id;

        //Espera leer: x1 y1 x2 y2 piezaID
        if (ss >> x1 >> y1 >> x2 >> y2 >> id) {
            mov.origen = vector2D(x1, y1);      //Posici�n inicial
            mov.destino = vector2D(x2, y2);     //Posici�n final
            mov.piezaID = id;                   //Identificador de la pieza
            movimientos.push_back(mov);         //Almacena el movimiento
        }

    }

    cargado = !movimientos.empty(); //Marca como cargado si hay datos. Ya que empty devuelve true si el 
                                    //vector est� vac�o

    return cargado;

}


//Devuelve true si quedan movimientos por reproducir:
bool replay::haySiguiente() const {
    return cargado && indiceActual < movimientos.size();
}

//Devuelve el siguiente movimiento y avanza el �ndice, si ha detectado true en haySiguiente:
Movimiento replay::siguiente() {
    if (!haySiguiente()) return Movimiento();
    return movimientos[indiceActual++];
}


//Reinicio del replay:
void replay::reiniciar() {

    indiceActual = 0; //Reinicio del �ndice a 0

}

//Devuelve una referencia a todos los movimientos cargados:
const std::vector<Movimiento>& replay::getMovimientos() const {
    return movimientos;
}