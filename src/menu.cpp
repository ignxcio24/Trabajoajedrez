#include "menu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Constructor del menú.
// Inicializa el menú con la pantalla indicada (inicio o game over) y configura los elementos a mostrar.
Menu::Menu(MenuScreen screen) : currentScreen(screen) {
    setScreen(screen); // Asigna y carga el menú activo (inicio o fin)
}

<<<<<<< Updated upstream
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
=======
// Cambia la pantalla actual del menú (inicio o game over) y actualiza los elementos a mostrar.
// Si es el menú de inicio, muestra las instrucciones y opciones iniciales.
// Si es el menú de fin de juego, muestra el ganador y las puntuaciones.
void Menu::setScreen(MenuScreen screen) {
    currentScreen = screen;      // Actualiza el estado de la pantalla actual.
    items.clear();               // Limpia los elementos del menú.
    (currentScreen == MENU_INICIO) ? menuStart() : menuGameOver(); // Selecciona qué menú mostrar.
}

// Dibuja una línea de texto en la pantalla en la posición vertical indicada.
// Se utiliza para mostrar cada línea del menú en pantalla.
void Menu::renderText(float y, const std::string& text) {
    glPushMatrix();
    glTranslatef(-0.7f, y, 0.0f);  // Alinea el texto a la izquierda.
    glScalef(0.0005f, 0.001f, 0.001f);  // Escala el texto para que se vea correctamente.
    for (char c : text) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, c); // Dibuja cada carácter.
>>>>>>> Stashed changes
    }
    glPopMatrix();
}

<<<<<<< Updated upstream
// Dibuja el menú en pantalla (texto en 2D)
=======
// Dibuja el menú completo en pantalla, mostrando todas las líneas almacenadas en 'items'.
// Cada línea corresponde a una instrucción, título o información relevante del menú.
>>>>>>> Stashed changes
void Menu::dibuja() {
    // Configura la proyección ortogonal para dibujar en 2D.
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1); // Proyección ortográfica para modo 2D

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

<<<<<<< Updated upstream
    glDisable(GL_DEPTH_TEST); // Desactiva profundidad para que el texto se vea sobre todo
    glColor3f(1.0f, 1.0f, 1.0f); // Texto en blanco
     
    float y = 0.45f;
    float dy = -0.15f;  // Espaciado entre líneas
    int i = 0;
    for (const auto& line : items) { 
        bool isTitle = (i == 0 || i == 2);
        renderText(y, line, isTitle); // Dibuja cada línea del menú
        y += dy;
        i++;
    }
    glEnable(GL_DEPTH_TEST); // Reactiva test de profundidad
=======
    glDisable(GL_DEPTH_TEST); // Desactiva el test de profundidad para dibujar el menú encima de todo.
    glColor3f(1.0f, 1.0f, 1.0f); // Color blanco para el texto.

    float y = 0.45f;   // Posición vertical inicial.
    float dy = -0.15f; // Espaciado entre líneas.
    for (const auto& line : items) {
        renderText(y, line); // Dibuja cada línea del menú.
        y += dy;             // Baja a la siguiente línea.
    }
    glEnable(GL_DEPTH_TEST); // Reactiva el test de profundidad.
>>>>>>> Stashed changes
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
<<<<<<< Updated upstream
// Define los textos que aparecerán en el menú de inicio
void Menu::menuStart() {
<<<<<<< HEAD
    items.clear();
    mostrarInstrucciones
        ? (items.reserve(10), 
            items.push_back("INSTRUCCIONES:"),
            items.push_back("Click izq | dcho : seleccionar | mover"),
            items.push_back("- G : guardar tablero actual"),
            items.push_back("- C : cargar ultimo tablero"),
            items.push_back("- V : vista 2D o 3D"), 
            items.push_back("- M : cambiar VS"),
            items.push_back("- T : cambiar modo tablero"), 
            items.push_back("- P : pausar"),
            items.push_back("- A : volver al menu principal"),
            items.push_back("- ENTER para comenzar"))
        : (items.reserve(8), 
            items.push_back("AJEDREZ"),
            items.push_back("GUERRA-SANTA"),
            items.push_back(" "),
            items.push_back(vsMaquina ? "Jugador VS Maquina" : "Jugador VS Jugador"),
            items.push_back(modoPetty ? "Modo Petty" : "Modo Esquinas Opuestas"),
            items.push_back("I : instrucciones"),
            items.push_back("ENTER para comenzar"),
            items.push_back("ESC para salir"));
=======
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
   
        
>>>>>>> 6c28cc41d8bca757a3296a58d65734744b5ef605
}
// Asigna el nombre del jugador ganador para mostrar en el menú final
=======

// Configura los elementos del menú de inicio.
// Muestra el título del juego y las instrucciones de uso y control en pantalla.
void Menu::menuStart() {
    items.reserve(8); // Reserva espacio para 8 líneas.
    items.push_back("AJEDREZ KRAMNIK"); // Título del juego.
    items.push_back("Click izq | dcho : seleccionar | posicionar"); // Instrucciones de selección.
    items.push_back("m : vs maquina"); // Opción para jugar contra la máquina.
    items.push_back("g : guardar tablero actual"); // Guardar partida.
    items.push_back("c : cargar ultimo tablero"); // Cargar partida.
    items.push_back("v : vista 2D o 3D"); // Cambiar vista.
    items.push_back("t : tablero 'Esquinas opuestas' o 'Petty'"); // Cambiar tipo de tablero.
    items.push_back("ENTER para comenzar"); // Instrucción para empezar la partida.
}

// Establece el nombre del ganador para mostrarlo en el menú de fin de juego.
>>>>>>> Stashed changes
void Menu::setWinner(const std::string& winner) {
    winnerText = winner; // Guarda el nombre del ganador.
}
<<<<<<< Updated upstream
// Guarda las puntuaciones acumuladas en un archivo externo
=======

// Guarda las puntuaciones de ambos jugadores en un archivo.
// No muestra nada en pantalla, pero permite persistir los resultados.
>>>>>>> Stashed changes
void Menu::guardarScores(int whiteScore, int blackScore) {
    std::ofstream out("scores.txt");
    if (out.is_open()) {
        out << whiteScore << " " << blackScore; // Guarda las puntuaciones en el archivo.
        out.close();
    }
}
<<<<<<< Updated upstream
// Carga las puntuaciones desde el archivo. Si no existe, pone a cero ambas
=======

// Carga las puntuaciones de ambos jugadores desde un archivo.
// Si no existe el archivo, inicializa las puntuaciones a cero y muestra un error por consola.
>>>>>>> Stashed changes
void Menu::cargarScores(int& whiteScore, int& blackScore) {
    std::ifstream in("scores.txt");
    if (in.is_open()) {
        in >> whiteScore >> blackScore; // Lee las puntuaciones.
        in.close();
    }
    else {
<<<<<<< Updated upstream
        //std::cerr << "Error al cargar las puntuaciones.\n";
=======
        std::cerr << "Error al cargar las puntuaciones.\n"; // Mensaje de error en consola.
>>>>>>> Stashed changes
        whiteScore = 0;
        blackScore = 0;
    }
}
<<<<<<< Updated upstream
// Suma la puntuación al jugador ganador y guarda los resultados actualizados
=======

// Actualiza las puntuaciones tras finalizar una partida y guarda los nuevos valores.
// Muestra por consola el resultado actualizado.
>>>>>>> Stashed changes
void Menu::setScores() {
    cargarScores(whiteScore, blackScore); // Carga las puntuaciones actuales.
    if (winnerText == "BLANCO")
        whiteScore++; // Suma un punto al ganador.
    else if (winnerText == "NEGRO")
        blackScore++;
<<<<<<< Updated upstream
    //std::cout << "Blanco " << whiteScore << " : " << blackScore << " Negro" << std::endl;
    guardarScores(whiteScore, blackScore);
}
// Define los textos a mostrar cuando se termina la partida
void Menu::menuGameOver() {
    items.clear();
    items.reserve(7);
    items.push_back("FIN DEL JUEGO");
	items.push_back(" ");
    items.push_back("GANADOR: " + winnerText);
    items.push_back(" ");
    items.push_back("   BLANCO " + std::to_string(whiteScore) + " : " + std::to_string(blackScore) + " NEGRO");
    items.push_back(" ");
<<<<<<< HEAD
    items.push_back("ENTER para jugar de nuevo");
    items.push_back("ESC para salir");
}
=======
    std::cout << "Blanco " << whiteScore << " : " << blackScore << " Negro" << std::endl; // Muestra el resultado.
    guardarScores(whiteScore, blackScore); // Guarda las nuevas puntuaciones.
}

// Configura los elementos del menú de fin de juego.
// Muestra el mensaje de fin, el ganador, las puntuaciones y las opciones para reiniciar o salir.
void Menu::menuGameOver() {
    items.clear(); // Limpia los elementos anteriores.
    items.reserve(7); // Reserva espacio para 7 líneas.
    items.push_back("FIN DEL JUEGO"); // Mensaje de fin.
    items.push_back("GANADOR: " + winnerText); // Muestra el ganador.
    items.push_back(" "); // Línea en blanco.
    items.push_back("BLANCO " + std::to_string(whiteScore) + " : " + std::to_string(blackScore) + " NEGRO"); // Puntuaciones.
    items.push_back(" "); // Línea en blanco.
    items.push_back("r : Reiniciar"); // Opción para reiniciar.
    items.push_back("ESC para salir"); // Opción para salir.
}
>>>>>>> Stashed changes
=======
    items.push_back("  ENTER para jugar de nuevo");
    items.push_back("       ESC para salir");
}
>>>>>>> 6c28cc41d8bca757a3296a58d65734744b5ef605
