#include "cli_ui.h"
#include <cstdlib>
#include <thread>
#include <chrono>
#include <iostream>
using namespace std;

void clearScreen()
{
#ifdef _Win32
    system("cls");
#else
    system("clear");
#endif
}

void typeWriter(const std::string &text, int delay)
{
    std::chrono::milliseconds delayTime(delay);
    for (char c : text)
    {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(delayTime);
    }
    std::cout << std::endl;
}
