#pragma once
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>

#ifndef MISCFUNCTIONS_H
#define MISCFUNCTIONS_H

int ValidateIntInput();
double ValidateDoubleInput();
bool InRange(int low, int high, int compare);
bool fileExists(std::string fileName);
void Pause(HANDLE* hConsole);

#endif // !MISCFUNCTIONS_H
