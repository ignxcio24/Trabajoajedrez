#include "menu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Menu::Menu(MenuScreen screen) : currentScreen(screen) {
    setScreen(screen); // Asigna y carga el menú activo (inicio o fin)
}

// Cambia el estado del menú (inicio o game over) y actualiza los elementos visuales
void Menu::setScreen(MenuScreen screen) {
    currentScreen = screen;
    items.clear(); // Limpia los textos anteriores
    (currentScreen == MENU_INICIO) ? menuStart() : menuGameOver();
}

// Dibuja una línea de texto en pantalla con posicionamiento y escalado
void Menu::renderText(float y, const std::string& text, bool titleStyle) {
    glPushMatrix();
    glTranslatef(-0.6f, y, 0.0f);   // Alineación a la izquierda del centro
    if (titleStyle)
        glScalef(0.0011f, 0.002f, 0.002f); // Tamaño mayor para títulos
    else
        glScalef(0.0005f, 0.001f, 0.001f);  // Tamaño estándar
    for (char c : text) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, c); // Dibuja cada carácter
    }
    glPopMatrix();
}

// Dibuja el menú en pantalla (texto en 2D)
void Menu::dibuja() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1); // Proyección ortográfica para modo 2D

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST); // Desactiva profundidad para que el texto se vea sobre todo
    glColor3f(1.0f, 1.0f, 1.0f); // Texto en blanco
     
    float y = 0.5f;
    float dy = -0.15f;  // Espaciado entre líneas
    int i = 0;
    for (const auto& line : items) { 
        renderText(y, line, false); // Dibuja cada línea del menú
        y += dy;
        i++;
    }
    glEnable(GL_DEPTH_TEST); // Reactiva test de profundidad
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
// Define los textos que aparecerán en el menú de inicio
void Menu::menuStart() {
<<<<<<< HEAD
    items.reserve(13);
    if (!mostrarInstrucciones) {
    items.push_back("  AJEDREZ");
    items.push_back(" ");
    items.push_back("GUERRA-SANTA");
    items.push_back(" ");
        if (vsMaquina)
            items.push_back("    Jugador VS Maquina");
        else
            items.push_back("    Jugador VS Jugador");
        if (modoPetty)
            items.push_back("    Modo Petty");
        else
            items.push_back("    Modo Esquinas opuestas");
        items.push_back("    I: instrucciones");
        items.push_back("    ENTER para comenzar");
        items.push_back("    ESC para salir");
    }
    else{
        items.push_back("  AJEDREZ");
        items.push_back(" ");
        items.push_back("INSTRUCCIONES");
        items.push_back("Click izq | dcho : seleccionar | mover");
        items.push_back(" - G : guardar tablero actual");
        items.push_back(" - C : cargar ultimo tablero");
        items.push_back(" - V : vista 2D o 3D");
        items.push_back(" - M : cambiar VS");
        items.push_back(" - T : cambiar modo tablero");
        items.push_back(" - P : pausar");
    }
   
        
=======
    items.clear();
    mostrarInstrucciones
        ? (items.reserve(8), 
            items.push_back("INSTRUCCIONES:"),
            items.push_back("Click izq | dcho : seleccionar | mover"),
            items.push_back("- G : guardar tablero actual"),
            items.push_back("- C : cargar ultimo tablero"),
            items.push_back("- V : vista 2D o 3D"), 
            items.push_back("- M : cambiar VS"),
            items.push_back("- T : cambiar modo tablero"), 
            items.push_back("- P : pausar"))
        : (items.reserve(8), 
            items.push_back("AJEDREZ"),
            items.push_back("GUERRA-SANTA"),
            items.push_back(" "),
            items.push_back(vsMaquina ? "Jugador VS Maquina" : "Jugador VS Jugador"),
            items.push_back(modoPetty ? "Modo Petty" : "Modo Esquinas Opuestas"),
            items.push_back("I : instrucciones"),
            items.push_back("ENTER para comenzar"),
            items.push_back("ESC para salir"));
>>>>>>> parent of 500db1d (AÃ‘ADIR INTERACCION TECLA A POR TECLADO)
}
// Asigna el nombre del jugador ganador para mostrar en el menú final
void Menu::setWinner(const std::string& winner) {
    winnerText = winner;
}
// Guarda las puntuaciones acumuladas en un archivo externo
void Menu::guardarScores(int whiteScore, int blackScore) {
    std::ofstream out("scores.txt");
    if (out.is_open()) {
        out << whiteScore << " " << blackScore;
        out.close();
    }
}
// Carga las puntuaciones desde el archivo. Si no existe, pone a cero ambas
void Menu::cargarScores(int& whiteScore, int& blackScore) {
    std::ifstream in("scores.txt");
    if (in.is_open()) {
        in >> whiteScore >> blackScore;
        in.close();
    }
    else {
        //std::cerr << "Error al cargar las puntuaciones.\n";
        whiteScore = 0;
        blackScore = 0;
    }
}
// Suma la puntuación al jugador ganador y guarda los resultados actualizados
void Menu::setScores() {
    cargarScores(whiteScore, blackScore);
    if (winnerText == "BLANCO")
        whiteScore++;
    else if (winnerText == "NEGRO")
        blackScore++;
    //std::cout << "Blanco " << whiteScore << " : " << blackScore << " Negro" << std::endl;
    guardarScores(whiteScore, blackScore);
}
// Define los textos a mostrar cuando se termina la partida
void Menu::menuGameOver() {
    items.clear();
    items.reserve(7);
    items.push_back("FIN DEL JUEGO");
    items.push_back("GANADOR: " + winnerText);
    items.push_back(" ");
    items.push_back("BLANCO " + std::to_string(whiteScore) + " : " + std::to_string(blackScore) + " NEGRO");
    items.push_back(" ");
<<<<<<< HEAD
    items.push_back("  ENTER para jugar de nuevo");
    items.push_back("       ESC para salir");
=======
    items.push_back("ENTER para jugar de nuevo");
    items.push_back("ESC para salir");
>>>>>>> parent of 500db1d (AÃ‘ADIR INTERACCION TECLA A POR TECLADO)
}