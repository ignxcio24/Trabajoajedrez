#include "logger.h"
#include <fstream>
#include <iostream>
#include <sstream>
//Inicialización de logger
static std::ofstream logfile;

//método init
void logger::init() {
    logfile.open("lastgame.txt");
    if (!logfile.is_open()) {
        std::cerr << "No se pudo abrir lastgame.txt\n";
    }
}
//método info
void logger::info(const char* message) {
    std::ostringstream output;
    output << message << std::endl;
    std::cout << output.str();
    if (logfile.is_open()) logfile << output.str();
}
//método warning
void logger::shutdown() {
    if (logfile.is_open())
        logfile.close();
}
