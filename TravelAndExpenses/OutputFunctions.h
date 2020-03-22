#pragma once

#ifndef OUTPUTFUNCTIONS_H
#define OUTPUTFUNCTIONS_H

void OutputIntro(HANDLE* hConsole);
void OutputMenu(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, std::vector<ChoiceOption>* vecChoiceCollection, std::string introText, bool boolUseDashes, bool boolClearScreen);
void OutputHeader(HANDLE* hConsole, int* intWidth, std::string headerText);
void OutputHeader(HANDLE* hConsole, int* intWidth, std::string headerText, int headerType);
void OutputTable(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
void OutputTable(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth, int tableType);
void OutputResults(HANDLE* hConsole, ResultTravel* resultTravel, int* intWidth, std::string strResultType);
void OutputResults(HANDLE* hConsole, ResultTravelExpense* resultTravelExpense, int* intWidth, std::string strResultType);
void OutputResults(HANDLE* hConsole, ResultTravelExpense* resultTravelExpense, int* intWidth, std::string strResultType, bool boolIsNumbered);
void OutputError(HANDLE* hConsole, std::string strErrorText);
void OutputError(HANDLE* hConsole, std::string strErrorText, bool boolNewLine);

#endif // !OUTPUTFUNCTIONS_H
