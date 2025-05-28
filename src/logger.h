#pragma once
class logger
{
public:
    static void init();
    static void info(const char* message);
    static void shutdown();
};

