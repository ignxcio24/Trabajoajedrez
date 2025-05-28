#include "logger.h"
#include <fstream>
#include <iostream>
#include <sstream>

static std::ofstream logfile;

void logger::init() {
    logfile.open("lastgame.txt");
    if (!logfile.is_open()) {
        std::cerr << "No se pudo abrir lastgame.txt\n";
    }
}

void logger::info(const char* message) {
    std::ostringstream output;
    output << message << std::endl;
    std::cout << output.str();
    if (logfile.is_open()) logfile << output.str();
}

void logger::shutdown() {
    if (logfile.is_open())
        logfile.close();
}
