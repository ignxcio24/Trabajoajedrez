#include "logger.h"
#include <fstream>
#include <iostream>
#include <sstream>
//Inicializaci�n de logger
static std::ofstream logfile;

//m�todo init
void logger::init() {
    logfile.open("lastgame.txt");
    if (!logfile.is_open()) {
        std::cerr << "No se pudo abrir lastgame.txt\n";
    }
}
//m�todo info
void logger::info(const char* message) {
    std::ostringstream output;
    output << message << std::endl;
    std::cout << output.str();
    if (logfile.is_open()) logfile << output.str();
}
//m�todo warning
void logger::shutdown() {
    if (logfile.is_open())
        logfile.close();
}
