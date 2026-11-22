#include "cli_ui.h"
#include <cstdlib>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
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
}

void border()
{
    cout << "\t+";
    for (int i = 0; i < 45; i++)
        cout << "-";
    cout << "+\n";
}

void displayHeading(string text)
{
    clearScreen();
    displayLogo();
    border();
    typeWriter(text, 50);
    border();
}

void displayLogo()
{
    cout << R"(
                    ███████╗███████╗██╗  ██╗ █████╗ ████████╗
                    ██╔════╝██╔════╝██║  ██║██╔══██╗╚══██╔══╝
                    ███████╗█████╗  ███████║███████║   ██║
                    ╚════██║██╔══╝  ██╔══██║██╔══██║   ██║
                    ███████║███████╗██║  ██║██║  ██║   ██║
                    ╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝ v2
                    
                    )"
         << "\n\n";
}

void displayEnd()
{
    displayHeading("\t\tThank you for choosing Sehat!\n");
    cout << R"(
                
                                 _|=|__________
                                /              \\
                               /                \\
                              /__________________\\
                               ||  || /--\\ ||  ||
                               ||[]|| | .| ||[]||
                             ()||__||_|__|_||__||()
                            ( )|-|-|-|====|-|-|-|( )
                            ^^^^^^^^^^====^^^^^^^^^^^
                    )"
         << endl;
}
