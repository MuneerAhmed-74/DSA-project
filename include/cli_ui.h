#ifndef CLI_UI_H
#define CLI_UI_H
#include <string>
using namespace std;

void clearScreen();
void typeWriter(const std::string &text, int);
void displayBorder();
void displayHeading();
void displayLogo();
void displayMenu();
void displayAbout();
void displayEnd();

#endif
