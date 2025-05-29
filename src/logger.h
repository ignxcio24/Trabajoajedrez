#pragma once
class logger
{
//Iniialización de todos los métodos
public:
    static void init();
    static void info(const char* message);
    static void shutdown();
};

