#include "Tablero.h"
#include <freeglut.h>


//Incicializamos el constructor:
Tablero::Tablero(int f, int c, float x, float y, float tam):
    filas(f), 
    columnas(c), 
    x_offset(-(c * tam) / 2.0),
    y_offset(-(f * tam) / 2.0),
    tam_casilla(tam)
{}

void Tablero::dibuja() const {
    //"algoritmia" para la creación del tablero
    //Seleccionamos una fila y creamos las columnas
    for (int fila = 0; fila < filas; ++fila) {
        //Con este bucle vamos dibujando las casillas
        for (int col = 0; col < columnas; ++col) {
            //Si el número de fila + columna es par se pinta de blanco
            if ((fila + col) % 2 == 0)
                glColor3f(1.0f, 1.0f, 1.0f); // blanco
            //Si el número de fila más columna es impar se pinta de verde oscuro
            //(paa que se parezca a la foto)
            else
                glColor3f(0.2f, 0.5f, 0.2f); // verde oscuro

            //Estas dos operaciones calculan donde se van a dibujar las casillas
            //El x_offset es el punto de referencia
            double x_pos = col * tam_casilla + x_offset;
            double y_pos = fila * tam_casilla + y_offset;

            
            //Al ser en 2D, elegimos los cuadrados para dibujar las casillas
            //Va iterando según las posiciones de x_pos
            glBegin(GL_QUADS);
            glVertex2f(x_pos, y_pos); //Vértice inferior izquierdo
            glVertex2f(x_pos + tam_casilla, y_pos); //vértice inferior derecho
            glVertex2f(x_pos + tam_casilla, y_pos + tam_casilla); //Vértice superior derecho
            glVertex2f(x_pos, y_pos + tam_casilla); //Vértice superior izquierdo
            glEnd();

            //A continuación vamos a crear "los bordes" que delimitan cada casilla
            
            
            //Así queda más limpio y parecido al de la foto
            glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);         // Calidad máxima
            glLineWidth(1.5f);                              // Grosor de línea

            glColor3f(0.0f, 0.0f, 0.0f);                    // Color negro para los bordes
            glBegin(GL_LINE_LOOP);
            glVertex2f(x_pos, y_pos);
            glVertex2f(x_pos + tam_casilla, y_pos);
            glVertex2f(x_pos + tam_casilla, y_pos + tam_casilla);
            glVertex2f(x_pos, y_pos + tam_casilla);
            glEnd();
            
        }
    }
}
