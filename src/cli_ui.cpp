#include "cli_ui.h"
#include "ui_patient.h"
#include "ui_app.h"
#include <cstdlib>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
using namespace std;

void clearScreen()
{
#ifdef _WIN32
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

void displayAbout()
{
    clearScreen();
    displayLogo();

    string table = R"(
	+--------------------+------------------------------------------------------+
	| Feature            | Details                                              |
	+--------------------+------------------------------------------------------+
	| Patient            | Dynamic array; sorting and searching algorithms      |
	|                    |                                                      |
	| Appointment        | Dynamic linked list; queue                           |
	|                    |                                                      |
	| File Handling      | .txt files used for storing data                     |
	|                    |                                                      |
	| Location           | Murree, Pakistan                                     |
	+--------------------+------------------------------------------------------+)";
    typeWriter(table, 5);
    cout << "\n";
}

void waitForEnter()
{
    cout << "\n\tPress Enter to return...";
    cin.get();
}

void displayMenu()
{
    int choice = 0;

    while (true)
    {
        displayHeading("\t\t>Home\t\t\tAbout\n");
        cout << "\n\t\tWelcome to Sehat Hospital!\n"
             << "\n\t\to Navigate\t\to Manage\n"
             << "\n\t\t |1. About" << "\t\t |3. Patient" << "\n\t\t |" << "\t\t\t |" << "\n\t\t |2. Exit" << "\t\t |4. Appointments";

        cout << "\n\n\t\tSelect an option: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\033[31m\t\tInvalid input. Enter a number (1-4).\033[0m\n";
            waitForEnter();
            continue;
        }

        cin.ignore(1000, '\n');

        switch (choice)
        {
        case 1:
            displayAbout();
            waitForEnter();
            break;

        case 2:
            displayEnd();
            return;

        case 3:
            displayPatientMenu();
            break;

        case 4:
            displayAppointmentMenu();
            break;

        default:
            cout << "\033[31m\t\tInvalid input. Enter a number (1-4).\033[0m\n";
            waitForEnter();
            break;
        }
    }
}
