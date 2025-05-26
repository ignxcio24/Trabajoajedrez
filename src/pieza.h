#pragma once

#include "vector2D.h"
#include "color.h"
#include "tablero.h"    
#include <array>
#include <string>
#include <memory>
#include <cmath>

GLUquadric* getSharedQuadric(); // Esta función apunta a un objeto para figuras curvas, 
                                //y además gracias a getSharedQuadric, reutilizamos el objeto.

class Pieza {
protected: // Con este parámetro pueden acceder nuestras clases derivadas
    float size;              // Tamaño de la pieza
    Color color;             // Color de la pieza (blanco o negro)
    vector2D posicion;       // Posición en el tablero

    std::array<std::array<int, 6>, 5> board;  // Representación del tablero
    vector2D seleccion;      // Posición seleccionada
    bool othermode;          // Modo de juego

public: // Miembros accesibles desde cualquier parte en la que se añade la clase.
    Pieza(); //Constructor por defecto
    virtual ~Pieza();

    inline void setColor(const Color& c) { color = c; } //Aportamos color
    inline void setPosicion(float ix, float iz) { //Aportamos posición
        posicion.x = ix;
        posicion.z = iz;
    }
    virtual void dibujaIndividual() const {}//Función virtual que puede ser sobreescrita por las hijas para dibujar la pieza

    std::array<std::array<int, 6>, 5>& getBoard(); //Devuelve el tablero (5x6)
    vector2D getSeleccion() const;// Devuelve la posición seleccionada como vector2D
    void deseleccionar();
    void seleccionar(int ix, int iz, int turnFlag, Tablero& platform);

    void guardarTablero(const std::string& filename, bool turnFlag, bool openingFlag);//Guarda el tablero en un archivo
    void cargarTablero(const std::string& filename, bool& turnFlag, bool& openingFlag);//Carga el tablero desde archivo
    void setMode(bool omod); //Cambia el contenido de la matriz según el modo que elija el jugador

    Pieza* createPiece(int pieceValue) const;//Nueva pieza
    void dibuja() const; //Dibuja la pieza
};