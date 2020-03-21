#pragma once

#ifndef OUTPUTFUNCTIONS_H
#define OUTPUTFUNCTIONS_H

void OutputIntro(HANDLE* hConsole);
void OutputMenu(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, std::vector<ChoiceOption>* vecChoiceCollection, std::string introText, bool boolUseDashes, bool boolClearScreen);
void OutputHeader(HANDLE* hConsole, int* intWidth, std::string headerText);
void OutputHeader(HANDLE* hConsole, int* intWidth, std::string headerText, int headerType);
void OutputTable(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
void OutputTable(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth, int tableType);

#endif // !OUTPUTFUNCTIONS_H
