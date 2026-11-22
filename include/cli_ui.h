#ifndef CLI_UI_H
#define CLI_UI_H

#include <string>

void clearScreen();
void typeWriter(const std::string &text, int delay);
void border();
void displayHeading(std::string text);
void displayLogo();
void displayMenu();
void displayAbout();
void displayEnd();

#endif
