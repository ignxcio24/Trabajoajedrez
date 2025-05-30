#pragma once

#include "vector2D.h"
#include "color.h"
#include "plataforma.h"    
#include <array>
#include <string>
#include <memory>
<<<<<<< Updated upstream
#include <math.h>
=======
#include <cmath>
#include "ETSIDI.h"
>>>>>>> Stashed changes

GLUquadric* getSharedQuadric(); //Dbuja primitivas curvas. La funci�n definida getSharedQuadric, permite reutilizar el puntero.

class Pieza {
protected: //Miembros accesibles por las clases derivadas.
    float size;              //Tama�o de la pieza
    Color color;             //Color de la pieza (ej. blanco o negro)
    vector2D posicion;       //Posici�n (x, y) en el tablero

<<<<<<< Updated upstream

    std::array<std::array<int, 6>, 5> board;  //Representaci�n del tablero
    vector2D seleccion;                       //Posici�n seleccionada               
    bool othermode;                           //Tipo de modo                  
=======
    std::array<std::array<int, 6>, 5> board;  // Representaci�n del tablero
    vector2D seleccion;      // Posici�n seleccionada
    bool othermode;          // Modo de juego
    ETSIDI::SpriteSequence sprite{ "imagenes/pangPlayer.png", 5 };
public: // Miembros accesibles desde cualquier parte en la que se a�ade la clase.
    Pieza(); //Constructor por defecto
    virtual ~Pieza();
>>>>>>> Stashed changes

public: //Miembros accesibles desde cualquier parte en la que se a�ade la clase.

    Pieza();                    //Constructor por defecto
    virtual ~Pieza();           //Destructor virtual

    Pieza* crear(int pieceValue) const;     //Crea una nueva pieza
    inline void setColor(const Color& c) { color = c; } //Settea el color
    inline void setPosicion(float ix, float iz) { posicion = { ix, iz }; }  //Settea la posici�n
    virtual void dibuja() const {}      //Dibuja. Como es virtual, puede ser sobrescrita

    inline std::array<std::array<int, 6>, 5>& getBoard() { return board; }
    inline vector2D getSeleccion() const { return seleccion; }      //Devuelve la posici�n tipo vector2D

    void seleccionar(int ix, int iz, int turnFlag, Plataforma& platform); //Selecciona una posici�n en el tablero
    void deseleccionar();

    void setMode(bool omod);        //Cambia el modo de juego, cambiando la matriz que define el tablero
    void guardarTablero(const std::string& filename, bool turnFlag); //Guarda el tablero en un archivo
    void cargarTablero(const std::string& filename, bool& turnFlag); //Carga el tablero desde el archivo
    void dibujarTablero() const;
};