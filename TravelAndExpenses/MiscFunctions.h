#pragma once
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>

#ifndef MISCFUNCTIONS_H
#define MISCFUNCTIONS_H

// Misc functions declarations.

int ValidateIntInput(HANDLE* hConsole);
double ValidateDoubleInput(HANDLE* hConsole);
bool InRange(int low, int high, int compare);
bool FileExists(std::string fileName);
void Pause(HANDLE* hConsole);
int FindNumOfJourneys(std::vector<Journey>* vecJourneyCollection, TravelType travelType);

#endif // !MISCFUNCTIONS_H
