#pragma once
class logger
{
//Iniializaci�n de todos los m�todos
public:
    static void init();
    static void info(const char* message);
    static void shutdown();
};

