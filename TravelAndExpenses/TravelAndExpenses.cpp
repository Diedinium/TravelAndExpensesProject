// TravelAndExpenses.cpp : The main application file for the travel and expenses console app.
// Please note: This file has XML style comments to enable intellisense, this is not a standard feature of C++! You will need an extension called "CppTripleSlash - xml doc comments for c++"
// installed in order for this functionality to work, this not being installed does not affect functionality, it simply results in less descriptive function descriptions.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <vector>
#include <iomanip>
#include <conio.h>
#include <algorithm>
#include <stdexcept>
#include <windows.h>
#include "CalcFunctions.h"

// Function namespace declaration

// Ouput print help functions.
void OutputIntro(HANDLE* hConsole);
void OutputMenu(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, std::vector<ChoiceOption>* vecChoiceCollection, std::string introText, bool boolUseDashes, bool boolClearScreen);
void OutputHeader(HANDLE* hConsole, int* intWidth, std::string headerText);
void OutputHeader(HANDLE* hConsole, int* intWidth, std::string headerText, int headerType);
void OutputTable(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
void OutputTable(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth, int tableType);

// Misc helper functions
void Pause(HANDLE* hConsole);

// Testing function : Automatically adds some journeys to save time when testing.
void TestFunction(std::vector<Journey>* vecJourneyCollection);

// Menu action functinons
void AddNewJourney(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewJourneys(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewSummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewCombinedSummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewTravelOnlySummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewTravelExpensesOnlySummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewSaveExport(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewSaveSummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection);
void ViewComparison(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewCompareTwoJourneys(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewTotalTwoJourneys(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewDeleteSelect(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewDeleteJourney(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewSaveImportSelect(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewImportSummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection);

//Function namespace declaration end

int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int intWidth = 15;
	std::vector<Journey> vecJourneyCollection;

	OutputIntro(&hConsole);

	int intMenuMainChoice = 0;
	bool boolExitWhile = false;

	TestFunction(&vecJourneyCollection);

	do {
		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "Enter a new Journey" });
		vecChoiceCollection.push_back(ChoiceOption{ 2, "View current journeys", 0 });
		vecChoiceCollection.push_back(ChoiceOption{ 3, "Summaries", 2 });
		vecChoiceCollection.push_back(ChoiceOption{ 4, "Comparisons and itemised summary", 2 });
		vecChoiceCollection.push_back(ChoiceOption{ 5, "Remove a Journey", 0 });
		vecChoiceCollection.push_back(ChoiceOption{ 6, "Import/Export Journeys", 0 });
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Exit" });
		OutputMenu(&hConsole, &vecJourneyCollection, &vecChoiceCollection, "Welcome to the travel and expense system.", true, true);

		while (boolExitWhile == false) {
			SetConsoleTextAttribute(hConsole, 9);
			std::cout << "Enter choice : ";
			SetConsoleTextAttribute(hConsole, 15);
			intMenuMainChoice = ValidateIntInput();

			try {
				switch (intMenuMainChoice)
				{
				case 1: {
					AddNewJourney(&hConsole, &vecJourneyCollection, &intWidth);
					boolExitWhile = true;
					break;
				}
				case 2: {
					if (vecJourneyCollection.size() <= 0) {
						boolExitWhile = false;
						throw std::runtime_error("You have not yet added any journeys, this menu option is not available yet.");
						break;
					}
					else {
						ViewJourneys(&hConsole, &vecJourneyCollection, &intWidth);
						boolExitWhile = true;
					}
					break;
				}
				case 3: {
					if (vecJourneyCollection.size() <= 1) {
						boolExitWhile = false;
						throw std::runtime_error("You have not yet added enough journeys, this menu option is not available yet.");
						break;
					}
					else {
						ViewSummary(&hConsole, &vecJourneyCollection, &intWidth);
						boolExitWhile = true;
					}
					break;
				}
				case 4: {
					if (vecJourneyCollection.size() <= 2) {
						boolExitWhile = false;
						throw std::exception("You have not yet added any journeys, or there are not at least two journeys. This menu option is not available yet.");
						break;
					}
					else {
						ViewComparison(&hConsole, &vecJourneyCollection, &intWidth);
						boolExitWhile = true;
					}
					break;
				}
				case 5: {
					if (vecJourneyCollection.size() <= 0)
					{
						boolExitWhile = false;
						throw std::exception("You have not yet added a journey, this option is not yet available. It will become a visible choice once you have added a journey.");
						break;
					}
					else {
						ViewDeleteJourney(&hConsole, &vecJourneyCollection, &intWidth);
						boolExitWhile = true;
					}
					break;
				}
				case 6: {
					if (vecJourneyCollection.size() <= 0)
					{
						boolExitWhile = false;
						throw std::exception("You have not yet added a journey, this option is not yet available. It will become a visible choice once you have added a journey.");
						break;
					}
					else {
						ViewSaveImportSelect(&hConsole, &vecJourneyCollection, &intWidth);
						boolExitWhile = true;
						break;
					}
				}
				case 9: {
					boolExitWhile = true;
					system("exit");
					break;
				}
				default:
					boolExitWhile = false;

					throw std::runtime_error("Input not recongised as a valid option.");
					break;
				}
			}
			catch (std::exception& exp) {
				std::cout << "Error : " << exp.what() << "\n";
				boolExitWhile = false;
			}

		}

		boolExitWhile = false;

	} while (intMenuMainChoice != 9);

	return 0;
}

// Functions

// Views/Menu screens
void AddNewJourney(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	std::string strContinueAddingJourneys;
	bool boolExitWhile = false;

	int intTravelChoiceInput;
	TravelType travelTypeChoice;

	double dTravelCost = 0;
	double dExpenseCost = 0;

	do {
		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "Travel only" });
		vecChoiceCollection.push_back(ChoiceOption{ 2, "Travel and expenses" });
		vecChoiceCollection.push_back(ChoiceOption{ 3, "View Current journeys", 0 });
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Return to menu" });
		OutputMenu(hConsole, vecJourneyCollection, &vecChoiceCollection, "Add a new journey screen.", true, true);

		while (boolExitWhile != true) {
			SetConsoleTextAttribute(*hConsole, 9);
			std::cout << "Enter choice : ";
			SetConsoleTextAttribute(*hConsole, 15);

			intTravelChoiceInput = ValidateIntInput();

			try {
				if (intTravelChoiceInput == 1) {
					travelTypeChoice = TravelType::Travel;
					SetConsoleTextAttribute(*hConsole, 9);
					std::cout << "Travel cost : ";
					SetConsoleTextAttribute(*hConsole, 15);

					dTravelCost = ValidateDoubleInput();

					Journey newJourney{ travelTypeChoice, dTravelCost };
					vecJourneyCollection->push_back(newJourney);
					boolExitWhile = true;
				}
				else if (intTravelChoiceInput == 2) {
					travelTypeChoice = TravelType::TravelAndExpense;
					SetConsoleTextAttribute(*hConsole, 9);
					std::cout << "Travel cost : ";
					SetConsoleTextAttribute(*hConsole, 15);

					dTravelCost = ValidateDoubleInput();

					SetConsoleTextAttribute(*hConsole, 9);
					std::cout << "Expenses cost : ";
					SetConsoleTextAttribute(*hConsole, 15);

					dExpenseCost = ValidateDoubleInput();

					Journey newJourney{ travelTypeChoice, dTravelCost, dExpenseCost };
					vecJourneyCollection->push_back(newJourney);
					boolExitWhile = true;
				}
				else if (intTravelChoiceInput == 3) {
					if (vecJourneyCollection->size() <= 0) {
						throw std::runtime_error("This option is not yet a valid option, there are no stored journeys.");
						boolExitWhile = false;
					}
					else {
						ViewJourneys(hConsole, vecJourneyCollection, intWidth);
						boolExitWhile = true;
					}
				}
				else if (intTravelChoiceInput == 9) {
					boolExitWhile = true;
				}
				else {
					throw std::runtime_error("This is not a valid choice. Please try again");
					boolExitWhile = false;
				}
			}
			catch (std::exception& exp) {
				SetConsoleTextAttribute(*hConsole, 12);
				std::cout << "Error : " << exp.what() << "\n";
				SetConsoleTextAttribute(*hConsole, 15);
			}
		}

		boolExitWhile = false;

		switch (intTravelChoiceInput) {
			case 3: {
				system("cls");
				strContinueAddingJourneys = "Y";
				break;
			}
			case 9: {
				strContinueAddingJourneys = "N";
				break;
			}
			default: {
				system("CLS");
				SetConsoleTextAttribute(*hConsole, 10);
				std::cout << "Journey succesfully added.\n";
				SetConsoleTextAttribute(*hConsole, 15);
				SetConsoleTextAttribute(*hConsole, 14);
				std::cout << "Would you like to add another journey?\n";
				std::cout << "Type 'Y' to add another, or type 'N' to return to the menu.\n";
				SetConsoleTextAttribute(*hConsole, 9);
				std::cout << "Enter Choice : ";
				SetConsoleTextAttribute(*hConsole, 15);

				bool boolExitWhileString = false;
				while (boolExitWhileString == false)
				{
					std::cin.clear();
					std::cin.ignore(123, '\n');
					std::cin >> strContinueAddingJourneys;
					transform(strContinueAddingJourneys.begin(), strContinueAddingJourneys.end(), strContinueAddingJourneys.begin(), std::toupper);

					if (strContinueAddingJourneys.find("Y") != std::string::npos) {
						boolExitWhileString = true;
					}
					else if (strContinueAddingJourneys.find("N") != std::string::npos) {
						boolExitWhileString = true;
					}
					else {
						SetConsoleTextAttribute(*hConsole, 12);
						std::cout << "\nERROR: Choice must be Y or N : ";
						SetConsoleTextAttribute(*hConsole, 15);
					}
				}
				boolExitWhile = false;
				break;
			}
		}

	} while (strContinueAddingJourneys == "Y");

	strContinueAddingJourneys = "N";
}

void ViewJourneys(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	system("CLS");
	OutputHeader(hConsole, intWidth, "Travel Only Journeys", 2);
	OutputTable(hConsole, vecJourneyCollection, intWidth, 2);
	std::cout << "\n";

	OutputHeader(hConsole, intWidth, "Travel and Expense Journeys");
	OutputTable(hConsole, vecJourneyCollection, intWidth, 1);
	std::cout << "\n";
	ViewDeleteSelect(hConsole, vecJourneyCollection, intWidth);
}

void ViewSummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intSummaryChoiceInput = 0;
	bool boolExitWhile = false;

	do {
		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "View Combined Summary" });
		vecChoiceCollection.push_back(ChoiceOption{ 2, "View Travel only Summary" });
		vecChoiceCollection.push_back(ChoiceOption{ 3, "View Travel and Expenses only Summary" });
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Return to menu" });
		OutputMenu(hConsole, vecJourneyCollection, &vecChoiceCollection, "View and interact with summaries.", true, true);

		//PrintSummaryScreen();
		boolExitWhile = false;

		while (boolExitWhile == false) {
			SetConsoleTextAttribute(*hConsole, 9);
			std::cout << "Enter choice : ";
			SetConsoleTextAttribute(*hConsole, 15);
			intSummaryChoiceInput = ValidateIntInput();

			try {
				switch (intSummaryChoiceInput) {
				case 1: {
					boolExitWhile = true;
					ViewCombinedSummary(hConsole, vecJourneyCollection, intWidth);
					break;
				}
				case 2: {
					boolExitWhile = true;
					ViewTravelOnlySummary(hConsole, vecJourneyCollection, intWidth);
					break;
				}
				case 3: {
					boolExitWhile = true;
					ViewTravelExpensesOnlySummary(hConsole, vecJourneyCollection, intWidth);
					break;
				}
				case 9: {
					boolExitWhile = true;
					break;
				}
				default: {
					throw std::exception("Not recognised as valid input.");
					break;
				}
				}

			}
			catch (std::exception& exp) {
				std::cout << "Error : " << exp.what() << "\n";
			}
		}

	} while (intSummaryChoiceInput != 9);

	intSummaryChoiceInput = 0;
	boolExitWhile = false;

}

void ViewTotalSummaryTwoItems(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	system("cls");
	OutputHeader(hConsole, intWidth, "Two Journey : Totals", 1);
	if (vecJourneyCollection->size() > 0) {
		OutputTable(hConsole, vecJourneyCollection, intWidth);
	}

	try {
		auto totals = CalculateAllSummaryTotals(vecJourneyCollection);
		std::cout << "\n";
		std::cout.precision(2);
		std::cout
			<< std::fixed << std::setw(20) << "Totals :"
			<< std::fixed << std::setw(*intWidth) << totals.Travel
			<< std::fixed << std::setw(*intWidth) << totals.Expense
			<< std::fixed << std::setw(*intWidth) << totals.Totals
			<< std::fixed << std::setw(*intWidth) << totals.ExpensePay
			<< std::fixed << std::setw(*intWidth) << totals.TaxReclaim
			<< std::fixed << std::setw(*intWidth) << totals.ExpenseNotCovered
			<< std::fixed << std::setw(*intWidth) << totals.FinalPay << "\n";
	}
	catch (std::exception& exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	ViewSaveExport(hConsole, vecJourneyCollection, intWidth);
}

void ViewCompareSummaryTwoItems(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	system("cls");
	OutputHeader(hConsole, intWidth, "Two Journeys : Comparison", 1);
	if (vecJourneyCollection->size() > 0) {
		OutputTable(hConsole, vecJourneyCollection, intWidth);
	}

	try {
		auto totals = CalculateAllSummaryTotals(vecJourneyCollection);
		std::cout << "\n";
		std::cout.precision(2);
		std::cout
			<< std::fixed << std::setw(20) << "Totals :"
			<< std::fixed << std::setw(*intWidth) << totals.Travel
			<< std::fixed << std::setw(*intWidth) << totals.Expense
			<< std::fixed << std::setw(*intWidth) << totals.Totals
			<< std::fixed << std::setw(*intWidth) << totals.ExpensePay
			<< std::fixed << std::setw(*intWidth) << totals.TaxReclaim
			<< std::fixed << std::setw(*intWidth) << totals.ExpenseNotCovered
			<< std::fixed << std::setw(*intWidth) << totals.FinalPay << "\n";
	}
	catch (std::exception& exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	try {
		auto largest = CalculateAllSummaryLargest(vecJourneyCollection);
		std::cout << "\n";
		std::cout.precision(2);
		std::cout
			<< std::fixed << std::setw(20) << "Largest :"
			<< std::fixed << std::setw(*intWidth) << largest.Travel
			<< std::fixed << std::setw(*intWidth) << largest.Expense
			<< std::fixed << std::setw(*intWidth) << largest.Totals
			<< std::fixed << std::setw(*intWidth) << largest.ExpensePay
			<< std::fixed << std::setw(*intWidth) << largest.TaxReclaim
			<< std::fixed << std::setw(*intWidth) << largest.ExpenseNotCovered
			<< std::fixed << std::setw(*intWidth) << largest.FinalPay << "\n";
	}
	catch (std::exception& exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	try {
		auto difference = CalculateTwoItemComparison(vecJourneyCollection);
		std::cout << "\n";
		std::cout.precision(2);
		std::cout
			<< std::fixed << std::setw(20) << "Difference :"
			<< std::fixed << std::setw(*intWidth) << difference.Travel
			<< std::fixed << std::setw(*intWidth) << difference.Expense
			<< std::fixed << std::setw(*intWidth) << difference.Totals
			<< std::fixed << std::setw(*intWidth) << difference.ExpensePay
			<< std::fixed << std::setw(*intWidth) << difference.TaxReclaim
			<< std::fixed << std::setw(*intWidth) << difference.ExpenseNotCovered
			<< std::fixed << std::setw(*intWidth) << difference.FinalPay << "\n";
	}
	catch (std::exception& exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	ViewSaveExport(hConsole, vecJourneyCollection, intWidth);
}

void ViewCombinedSummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	system("cls");
	OutputHeader(hConsole, intWidth, "");
	if (vecJourneyCollection->size() > 0) {
		OutputTable(hConsole, vecJourneyCollection, intWidth, 2);
		OutputTable(hConsole, vecJourneyCollection, intWidth, 1);
		//PrintCurrentJourneysTravelExpense(vecJourneyCollection, intWidth);
	}

	try {
		auto totals = CalculateAllSummaryTotals(vecJourneyCollection);
		std::cout << "\n";
		std::cout.precision(2);
		std::cout
			<< std::fixed << std::setw(*intWidth) << "Totals :"
			<< std::fixed << std::setw(*intWidth) << totals.Travel
			<< std::fixed << std::setw(*intWidth) << totals.Expense
			<< std::fixed << std::setw(*intWidth) << totals.Totals
			<< std::fixed << std::setw(*intWidth) << totals.ExpensePay
			<< std::fixed << std::setw(*intWidth) << totals.TaxReclaim
			<< std::fixed << std::setw(*intWidth) << totals.ExpenseNotCovered
			<< std::fixed << std::setw(*intWidth) << totals.FinalPay << "\n";
	}
	catch (std::exception& exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	try {
		auto average = CalculateAllSummaryAverage(vecJourneyCollection);
		std::cout << "\n";
		std::cout.precision(2);
		std::cout
			<< std::fixed << std::setw(*intWidth) << "Averages :"
			<< std::fixed << std::setw(*intWidth) << average.Travel
			<< std::fixed << std::setw(*intWidth) << average.Expense
			<< std::fixed << std::setw(*intWidth) << average.Totals
			<< std::fixed << std::setw(*intWidth) << average.ExpensePay
			<< std::fixed << std::setw(*intWidth) << average.TaxReclaim
			<< std::fixed << std::setw(*intWidth) << average.ExpenseNotCovered
			<< std::fixed << std::setw(*intWidth) << average.FinalPay << "\n";
	}
	catch (std::exception& exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	try {
		auto largest = CalculateAllSummaryLargest(vecJourneyCollection);
		std::cout << "\n";
		std::cout.precision(2);
		std::cout
			<< std::fixed << std::setw(*intWidth) << "Largest :"
			<< std::fixed << std::setw(*intWidth) << largest.Travel
			<< std::fixed << std::setw(*intWidth) << largest.Expense
			<< std::fixed << std::setw(*intWidth) << largest.Totals
			<< std::fixed << std::setw(*intWidth) << largest.ExpensePay
			<< std::fixed << std::setw(*intWidth) << largest.TaxReclaim
			<< std::fixed << std::setw(*intWidth) << largest.ExpenseNotCovered
			<< std::fixed << std::setw(*intWidth) << largest.FinalPay << "\n";
	}
	catch (std::exception& exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	ViewSaveExport(hConsole, vecJourneyCollection, intWidth);
}

void ViewTravelOnlySummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	system("cls");
	OutputHeader(hConsole, intWidth, "Travel Only Journeys", 2);
	OutputTable(hConsole, vecJourneyCollection, intWidth, 2);
	try {
		auto totals = CalculateTravelSummaryTotals(vecJourneyCollection);
		std::cout << "\n";
		std::cout.precision(2);
		std::cout
			<< std::fixed << std::setw(*intWidth) << "Totals :"
			<< std::fixed << std::setw(*intWidth) << totals.Travel
			<< std::fixed << std::setw(*intWidth) << totals.TaxReclaim
			<< std::fixed << std::setw(*intWidth) << totals.FinalPay << "\n";
	}
	catch (std::exception& exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	try {
		auto average = CalculateTravelSummaryAverage(vecJourneyCollection);
		std::cout << "\n";
		std::cout.precision(2);
		std::cout
			<< std::fixed << std::setw(*intWidth) << "Averages :"
			<< std::fixed << std::setw(*intWidth) << average.Travel
			<< std::fixed << std::setw(*intWidth) << average.TaxReclaim
			<< std::fixed << std::setw(*intWidth) << average.FinalPay << "\n";
	}
	catch (std::exception& exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	try {
		auto largest = CalculateTravelSummaryLargest(vecJourneyCollection);
		std::cout << "\n";
		std::cout.precision(2);
		std::cout
			<< std::fixed << std::setw(*intWidth) << "Largest :"
			<< std::fixed << std::setw(*intWidth) << largest.Travel
			<< std::fixed << std::setw(*intWidth) << largest.TaxReclaim
			<< std::fixed << std::setw(*intWidth) << largest.FinalPay << "\n";
	}
	catch (std::exception& exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	std::vector<Journey> vecTravelOnlyCollection;
	for (size_t i = 0; i < vecJourneyCollection->size(); i++)
	{
		if (vecJourneyCollection->at(i).travelType == TravelType::Travel) {
			vecTravelOnlyCollection.push_back(vecJourneyCollection->at(i));
		}
	}

	ViewSaveExport(hConsole, &vecTravelOnlyCollection, intWidth);
}

void ViewTravelExpensesOnlySummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	system("cls");
	OutputHeader(hConsole, intWidth, "Travel and Expense Journeys");
	//PrintCurrentJourneysTravelExpense(vecJourneyCollection, intWidth);
	OutputTable(hConsole, vecJourneyCollection, intWidth, 1);
	try {
		auto totals = CalculateTravelExpenseSummaryTotals(vecJourneyCollection);
		std::cout << "\n";
		std::cout.precision(2);
		std::cout
			<< std::fixed << std::setw(*intWidth) << "Totals :"
			<< std::fixed << std::setw(*intWidth) << totals.Travel
			<< std::fixed << std::setw(*intWidth) << totals.Expense
			<< std::fixed << std::setw(*intWidth) << totals.Totals
			<< std::fixed << std::setw(*intWidth) << totals.ExpensePay
			<< std::fixed << std::setw(*intWidth) << totals.TaxReclaim
			<< std::fixed << std::setw(*intWidth) << totals.ExpenseNotCovered
			<< std::fixed << std::setw(*intWidth) << totals.FinalPay << "\n";
	}
	catch (std::exception& exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	try {
		auto average = CalculateTravelExpenseSummaryAverage(vecJourneyCollection);
		std::cout << "\n";
		std::cout.precision(2);
		std::cout
			<< std::fixed << std::setw(*intWidth) << "Averages :"
			<< std::fixed << std::setw(*intWidth) << average.Travel
			<< std::fixed << std::setw(*intWidth) << average.Expense
			<< std::fixed << std::setw(*intWidth) << average.Totals
			<< std::fixed << std::setw(*intWidth) << average.ExpensePay
			<< std::fixed << std::setw(*intWidth) << average.TaxReclaim
			<< std::fixed << std::setw(*intWidth) << average.ExpenseNotCovered
			<< std::fixed << std::setw(*intWidth) << average.FinalPay << "\n";
	}
	catch (std::exception& exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	try {
		auto largest = CalculateTravelExpenseSummaryLargest(vecJourneyCollection);
		std::cout << "\n";
		std::cout.precision(2);
		std::cout
			<< std::fixed << std::setw(*intWidth) << "Largest :"
			<< std::fixed << std::setw(*intWidth) << largest.Travel
			<< std::fixed << std::setw(*intWidth) << largest.Expense
			<< std::fixed << std::setw(*intWidth) << largest.Totals
			<< std::fixed << std::setw(*intWidth) << largest.ExpensePay
			<< std::fixed << std::setw(*intWidth) << largest.TaxReclaim
			<< std::fixed << std::setw(*intWidth) << largest.ExpenseNotCovered
			<< std::fixed << std::setw(*intWidth) << largest.FinalPay << "\n";
	}
	catch (std::exception& exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	std::vector<Journey> vecTravelExpenseOnlyCollection;
	for (size_t i = 0; i < vecJourneyCollection->size(); i++)
	{
		if (vecJourneyCollection->at(i).travelType == TravelType::TravelAndExpense) {
			vecTravelExpenseOnlyCollection.push_back(vecJourneyCollection->at(i));
		}
	}

	ViewSaveExport(hConsole, &vecTravelExpenseOnlyCollection, intWidth);
}

void ViewSaveSummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection) {
	system("cls");

	std::fstream fout;
	std::string fnameOriginal = "journeyList.csv";
	std::string fname = "journeyList.csv";
	int intCount = 0;

	while (fileExists(fname))
	{
		fname = fnameOriginal;
		fname = fname.insert(11, std::to_string(intCount));
		intCount++;
	}

	fout.open(fname, std::ios::out | std::ios::app);

	fout << "Travel Type" << ", "
		<< "Travel Cost" << ", "
		<< "Expense Cost" << ", "
		<< "Total Cost" << ", "
		<< "Tax Reclaim" << ", "
		<< "Expense payable" << ", "
		<< "Final payment" << ", "
		<< "Expense Not Covered"
		<< "\n";

	for (size_t i = 0; i < vecJourneyCollection->size(); i++)
	{
		fout << std::fixed << std::setprecision(2) << ((((int)vecJourneyCollection->at(i).travelType) == 0) ? "Travel" : "Travel & Exp") << ", "
			<< vecJourneyCollection->at(i).travelCost << ", "
			<< vecJourneyCollection->at(i).expenseCost << ", "
			<< vecJourneyCollection->at(i).totalCost << ", "
			<< vecJourneyCollection->at(i).taxReclaim << ", "
			<< vecJourneyCollection->at(i).expensePayable << ", "
			<< vecJourneyCollection->at(i).finalPayment << ", "
			<< vecJourneyCollection->at(i).expenseNotCovered
			<< "\n";
	}

	fout.close();

	std::cout << "Journeys written to '" << fname << "'. Please check the directory that you ran this application from to find this file." << "\n";

	Pause(hConsole);
}

void ViewImportSummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection) {

	std::string strFilename = "";
	std::fstream fin;
	bool boolExitLoop = false;
	bool boolHasReadFile = false;

	system("cls");
	std::cout << "Please specify the name of the file you would like to import below\n";
	std::cout << "Note : Please enter the full file name, such as 'JourneyList.csv', otherwise the file will not be found. The file must also be in the same directory that you are running this program from. Type 'exit' if you would like to cancel and return to the previous screen.\n";
	std::cout << "\n";

	do {
		try {
			std::cout << "File name : ";
			std::cin >> strFilename;
			fin.open(strFilename, std::ios::in);
			if (strFilename == "exit") {
				boolExitLoop = true;
				boolHasReadFile = false;
			}
			else {
				if (fileExists(strFilename)) {
					std::cout << "File exists.\n";
					boolExitLoop = true;
					boolHasReadFile = true;
				}
				else {
					std::cout << "\n";
					std::cout << "Error : File could not be found. Please ensure you are specifying the filename correctly.\n";
					boolHasReadFile = false;
				}
			}
		}
		catch (std::exception& ex) {
			std::cout << "\n";
			std::cout << "Error :" << ex.what() << "\n";
		}
	} while (boolExitLoop == false);

	if (boolHasReadFile) {
		std::vector<std::string> vecRowTemp;
		std::string strLine, strWord, strTemp;

		try {
			while (!fin.eof()) {
				vecRowTemp.clear();

				std::getline(fin, strLine);

				std::stringstream s(strLine);


				while (std::getline(s, strWord, ',')) {
					vecRowTemp.push_back(strWord);
				}

				if (!vecRowTemp.empty()) {
					if (vecRowTemp[0] != "Travel Type") {
						Journey journeyTemp{ TravelType::Travel, 0 };
						journeyTemp.travelType = (((vecRowTemp[0]) == "Travel") ? TravelType::Travel : TravelType::TravelAndExpense);
						journeyTemp.travelCost = std::stod(vecRowTemp[1]);
						journeyTemp.expenseCost = std::stod(vecRowTemp[2]);
						journeyTemp.totalCost = std::stod(vecRowTemp[3]);
						journeyTemp.taxReclaim = std::stod(vecRowTemp[4]);
						journeyTemp.expensePayable = std::stod(vecRowTemp[5]);
						journeyTemp.finalPayment = std::stod(vecRowTemp[6]);
						journeyTemp.expenseNotCovered = std::stod(vecRowTemp[7]);

						vecJourneyCollection->push_back(journeyTemp);
					}
				}
			}

			std::cout << "Journeys succssfully imported.\n";
		}
		catch (std::exception& ex) {
			std::cout << "\n";
			std::cout << "Sorry, but the file could not be imported. This is likely because the file is not formatted correctly.\n";
			std::cout << "Exception Generated : " << ex.what() << "\n";

			Pause(hConsole);
		}


		Pause(hConsole);
	}
}

void ViewComparison(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intComparisonChoiceInput = 0;
	bool boolExitWhile = false;

	do {
		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "Compare two journeys", 2 });
		vecChoiceCollection.push_back(ChoiceOption{ 2, "Total two journeys", 2 });
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Return to menu" });
		OutputMenu(hConsole, vecJourneyCollection, &vecChoiceCollection, "Make Comparisons and total invoices.", true, true);

		boolExitWhile = false;

		while (boolExitWhile == false) {
			SetConsoleTextAttribute(*hConsole, 9);
			std::cout << "Enter choice : ";
			SetConsoleTextAttribute(*hConsole, 15);
			intComparisonChoiceInput = ValidateIntInput();

			try {
				switch (intComparisonChoiceInput) {
				case 1: {
					boolExitWhile = true;
					ViewCompareTwoJourneys(hConsole, vecJourneyCollection, intWidth);
					break;
				}
				case 2: {
					boolExitWhile = true;
					ViewTotalTwoJourneys(hConsole, vecJourneyCollection, intWidth);
					break;
				}
				case 9: {
					boolExitWhile = true;
					intComparisonChoiceInput = 9;
					break;
				}
				default: {
					throw std::exception("Not recognised as valid input.");
					break;
				}
				}

			}
			catch (std::exception& exp) {
				std::cout << "Error : " << exp.what() << "\n";
			}
		}

	} while (intComparisonChoiceInput != 9);

	intComparisonChoiceInput = 0;
	boolExitWhile = false;
}

/// <summary>
/// Save/Export menu view. Printed in particular places where saving/exporting needs to be only option. Importing and Saving handled in seperate View.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewSaveExport(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intSaveExportChoiceInput = 0;
	bool boolExitWhile = false;

	do {
		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "Export list as CSV" });
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Return to previous" });
		OutputMenu(hConsole, vecJourneyCollection, &vecChoiceCollection, "Make Comparisons and total invoices.", false, false);

		boolExitWhile = false;

		while (boolExitWhile == false) {
			SetConsoleTextAttribute(*hConsole, 9);
			std::cout << "Enter choice : ";
			SetConsoleTextAttribute(*hConsole, 15);
			intSaveExportChoiceInput = ValidateIntInput();

			try {
				switch (intSaveExportChoiceInput) {
				case 1: {
					ViewSaveSummary(hConsole, vecJourneyCollection);
					boolExitWhile = true;
					intSaveExportChoiceInput = 9;
					break;
				}
				case 9: {
					boolExitWhile = true;
					break;
				}
				default: {
					throw std::exception("Not recognised as valid input.");
					break;
				}
				}

			}
			catch (std::exception& exp) {
				std::cout << "Error : " << exp.what() << "\n";
			}
		}

	} while (intSaveExportChoiceInput != 9);

	intSaveExportChoiceInput = 0;
	boolExitWhile = false;
}

/// <summary>
/// Asks user to choose two items, presents comparison of two items.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewCompareTwoJourneys(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intCompareFirst = 0, intCompareSecond = 0;
	std::vector<Journey> vecJourneyCompare;

	system("cls");
	OutputHeader(hConsole, intWidth, "", 1);
	OutputTable(hConsole, vecJourneyCollection, intWidth);

	std::cout << "\n";
	std::cout << "Please specify number of the first journey you would like to compare.\n";
	do {
		SetConsoleTextAttribute(*hConsole, 9);
		std::cout << "Enter Choice : ";
		SetConsoleTextAttribute(*hConsole, 15);
		intCompareFirst = ValidateIntInput() - 1;

		try {
			vecJourneyCompare.push_back(vecJourneyCollection->at(intCompareFirst));
		}
		catch (std::exception ex) {
			std::cout << "The number you specified is not a valid item currently in the list.\n";
		}
	} while (!InRange(0, (int)vecJourneyCollection->size() - 1, intCompareFirst));

	std::cout << "\n";
	std::cout << "Please specify number of the second journey you would like to compare.\n";
	do {
		SetConsoleTextAttribute(*hConsole, 9);
		std::cout << "Enter Choice : ";
		SetConsoleTextAttribute(*hConsole, 15);
		intCompareSecond = (ValidateIntInput() - 1);

		try {
			if (intCompareSecond == intCompareFirst) {
				throw std::runtime_error("You cannot compare two of the same item.");
			}
			else {
				vecJourneyCompare.push_back(vecJourneyCollection->at(intCompareSecond));
			}
		}
		catch (std::out_of_range ex) {
			std::cout << "The number you specified is not a valid item currently in the list.\n";
		}
		catch (std::runtime_error ex) {
			std::cout << ex.what() << "\n";
		}
	} while (!InRange(0, (int)vecJourneyCollection->size() - 1, intCompareSecond) || intCompareFirst == intCompareSecond);

	ViewCompareSummaryTwoItems(hConsole, &vecJourneyCompare, intWidth);
}

/// <summary>
/// Asks user to choose two items currently in system. Then displays comparison.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewTotalTwoJourneys(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intTotalFirst = 0, intTotalSecond = 0;
	std::vector<Journey> vecJourneyTotal;

	system("cls");
	OutputHeader(hConsole, intWidth, "", 1);
	OutputTable(hConsole, vecJourneyCollection, intWidth);

	std::cout << "\n";
	std::cout << "Please specify number of the first journey you would like to total.\n";
	do {
		SetConsoleTextAttribute(*hConsole, 9);
		std::cout << "Enter Choice : ";
		SetConsoleTextAttribute(*hConsole, 15);
		intTotalFirst = ValidateIntInput() - 1;

		try {
			vecJourneyTotal.push_back(vecJourneyCollection->at(intTotalFirst));
		}
		catch (std::exception ex) {
			std::cout << "The number you specified is not a valid item currently in the list.\n";
		}
	} while (!InRange(0, (int)vecJourneyCollection->size() - 1, intTotalFirst));

	std::cout << "\n";
	std::cout << "Please specify number of the second journey you would like to total.\n";
	do {
		SetConsoleTextAttribute(*hConsole, 9);
		std::cout << "Enter Choice : ";
		SetConsoleTextAttribute(*hConsole, 15);
		intTotalSecond = (ValidateIntInput() - 1);

		try {
			if (intTotalSecond == intTotalFirst) {
				throw std::runtime_error("You cannot compare two of the same item.");
			}
			else {
				vecJourneyTotal.push_back(vecJourneyCollection->at(intTotalSecond));
			}
		}
		catch (std::out_of_range ex) {
			std::cout << "The number you specified is not a valid item currently in the list.\n";
		}
		catch (std::runtime_error ex) {
			std::cout << ex.what() << "\n";
		}
	} while (!InRange(0, (int)vecJourneyCollection->size() - 1, intTotalSecond) || intTotalFirst == intTotalSecond);

	ViewTotalSummaryTwoItems(hConsole, &vecJourneyTotal, intWidth);
}

/// <summary>
/// Delete choice menu, allows user to choose to delete an item, or to return to previous. Passes onto the more generic ViewDeleteJourney screen that handles deleteing a journey.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewDeleteSelect(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intDeleteChoiceInput = 0;
	bool boolExitWhile = false;

	do {

		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "Delete a journey" });
		vecChoiceCollection.push_back(ChoiceOption{ 2, "Export List as CSV" });
		vecChoiceCollection.push_back(ChoiceOption{ 3, "Add new Journey" });
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Return to previous" });
		OutputMenu(hConsole, vecJourneyCollection, &vecChoiceCollection, "Please specifiy which of the following options you would like to do.", false, false);

		boolExitWhile = false;

		while (boolExitWhile == false) {
			SetConsoleTextAttribute(*hConsole, 9);
			std::cout << "Enter choice : ";
			SetConsoleTextAttribute(*hConsole, 15);
			intDeleteChoiceInput = ValidateIntInput();

			try {
				switch (intDeleteChoiceInput) {
				case 1: {
					ViewDeleteJourney(hConsole, vecJourneyCollection, intWidth);
					boolExitWhile = true;
					intDeleteChoiceInput = 9;
					break;
				}
				case 2: {
					ViewSaveSummary(hConsole, vecJourneyCollection);
					boolExitWhile = true;
					intDeleteChoiceInput = 9;
					break;
				}
				case 3: {
					AddNewJourney(hConsole, vecJourneyCollection, intWidth);
					boolExitWhile = true;
					intDeleteChoiceInput = 9;
					break;
				}
				case 9: {
					boolExitWhile = true;
					break;
				}
				default: {
					throw std::exception("Not recognised as valid input.");
					break;
				}
				}

			}
			catch (std::exception& exp) {
				std::cout << "Error : " << exp.what() << "\n";
			}
		}

	} while (intDeleteChoiceInput != 9);

	intDeleteChoiceInput = 0;
	boolExitWhile = false;
}

/// <summary>
/// Asks user to choose a item to delete, removes item. Continues to loop until valid array item is given.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewDeleteJourney(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intJourneyToDelete = 0, intCompareSecond = 0;
	bool boolIsValid = false;
	bool boolIsExiting = false;

	system("cls");
	OutputHeader(hConsole, intWidth, "", 1);
	OutputTable(hConsole, vecJourneyCollection, intWidth);

	std::cout << "\n";
	SetConsoleTextAttribute(*hConsole, 14);
	std::cout << "Please specify number of the journey you would like to remove. Type '0' to cancel. \n";
	SetConsoleTextAttribute(*hConsole, 15);

	while (boolIsValid == false) {
		SetConsoleTextAttribute(*hConsole, 9);
		std::cout << "Enter Choice : ";
		SetConsoleTextAttribute(*hConsole, 15);
		intJourneyToDelete = ValidateIntInput() - 1;

		if (intJourneyToDelete == -1) {
			boolIsValid = true;
			boolIsExiting = true;
		}
		else if (InRange(0, (int)vecJourneyCollection->size() - 1, intJourneyToDelete)) {
			boolIsValid = true;
		}
		else {
			SetConsoleTextAttribute(*hConsole, 12);
			std::cout << "The number you specified is not a valid item currently in the list.\n";
			SetConsoleTextAttribute(*hConsole, 15);
		}
	}

	if (!boolIsExiting) {
		try {
			vecJourneyCollection->erase(vecJourneyCollection->begin() + intJourneyToDelete);
		}
		catch (std::exception& ex) {
			std::cout << "Sorry, something went wrong while removing this item.\n";
			SetConsoleTextAttribute(*hConsole, 15);
		}

		std::cout << "\n";
		SetConsoleTextAttribute(*hConsole, 10);
		std::cout << "Journey " << (intJourneyToDelete + 1) << " successfully removed.\n";
		SetConsoleTextAttribute(*hConsole, 15);

		Pause(hConsole);
	}
}

void ViewSaveImportSelect(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intSaveImportChoiceInput = 0;
	bool boolExitWhile = false;

	do {
		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "Export current Journeys" });
		vecChoiceCollection.push_back(ChoiceOption{ 2, "Import Journeys from CSV" });
		vecChoiceCollection.push_back(ChoiceOption{ 3, "View current journeys" });
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Return to previous" });
		OutputMenu(hConsole, vecJourneyCollection, &vecChoiceCollection, "Import or export journeys.", true, true);

		boolExitWhile = false;

		while (boolExitWhile == false) {
			SetConsoleTextAttribute(*hConsole, 9);
			std::cout << "Enter choice : ";
			SetConsoleTextAttribute(*hConsole, 15);
			intSaveImportChoiceInput = ValidateIntInput();

			try {
				switch (intSaveImportChoiceInput) {
				case 1: {
					boolExitWhile = true;
					ViewSaveSummary(hConsole, vecJourneyCollection);
					break;
				}
				case 2: {
					boolExitWhile = true;
					ViewImportSummary(hConsole, vecJourneyCollection);
					break;
				}
				case 3: {
					boolExitWhile = true;
					ViewJourneys(hConsole, vecJourneyCollection, intWidth);
					break;
				}
				case 9: {
					boolExitWhile = true;
					intSaveImportChoiceInput = 9;
					break;
				}
				default: {
					throw std::exception("Not recognised as valid input.");
					break;
				}
				}

			}
			catch (std::exception& exp) {
				std::cout << "Error : " << exp.what() << "\n";
			}
		}

	} while (intSaveImportChoiceInput != 9);

	intSaveImportChoiceInput = 0;
	boolExitWhile = false;
}
// Views/Menu screens end

// Output functions

/// <summary>
/// Prints the intro warning/notice when loading the program.
/// </summary>
/// <param name="hConsole"></param>
void OutputIntro(HANDLE* hConsole) {
	// Notice for users about setup needed to ensure proper formatted output.
	SetConsoleTextAttribute(*hConsole, 12);
	std::cout << "### NOTICE ###\n";
	SetConsoleTextAttribute(*hConsole, 14);
	std::cout << "To ensure proper text formatting while in use, please make sure you widen the console window. ";
	std::cout << "You can do this by dragging the window larger or by right clicking on the top of this window then go to properties, ";
	std::cout << "and the layout tab. Setting the console width to 127 is recommended. Not doing this could result in text being wrapped ";
	std::cout << "ruining some of the output tables.\n";
	SetConsoleTextAttribute(*hConsole, 12);
	std::cout << "### NOTICE ###\n";
	SetConsoleTextAttribute(*hConsole, 15);

	Pause(hConsole);
}

void OutputMenu(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, std::vector<ChoiceOption>* vecChoiceCollection, std::string introText, bool boolUseDashes, bool boolClearScreen) {
	if (boolClearScreen) {
		system("cls");
	}
	SetConsoleTextAttribute(*hConsole, 6);
	if (boolUseDashes) {
		std::cout << "-------------------------------------------\n";
	}
	SetConsoleTextAttribute(*hConsole, 15);
	std::cout << "\n";
	SetConsoleTextAttribute(*hConsole, 14);
	std::cout << introText;
	std::cout << "\nPlease specify your option :\n";
	std::cout << "\n";
	SetConsoleTextAttribute(*hConsole, 15);
	for (size_t i = 0; i < vecChoiceCollection->size(); i++)
	{
		if (vecChoiceCollection->at(i).OptionHideThreshold != 99) {
			if (vecChoiceCollection->at(i).OptionHideThreshold == 0) {
				if (vecJourneyCollection->size() > vecChoiceCollection->at(i).OptionHideThreshold) {
					SetConsoleTextAttribute(*hConsole, 10);
					std::cout << "Option " << vecChoiceCollection->at(i).OptionNumber << " : ";
					SetConsoleTextAttribute(*hConsole, 15);
					std::cout << vecChoiceCollection->at(i).OptionText << "\n";
				}
			}
			else {
				if (vecJourneyCollection->size() >= vecChoiceCollection->at(i).OptionHideThreshold) {
					SetConsoleTextAttribute(*hConsole, 10);
					std::cout << "Option " << vecChoiceCollection->at(i).OptionNumber << " : ";
					SetConsoleTextAttribute(*hConsole, 15);
					std::cout << vecChoiceCollection->at(i).OptionText << "\n";
				}
			}
		}
		else {
			SetConsoleTextAttribute(*hConsole, 10);
			std::cout << "Option " << vecChoiceCollection->at(i).OptionNumber << " : ";
			SetConsoleTextAttribute(*hConsole, 15);
			std::cout << vecChoiceCollection->at(i).OptionText << "\n";
		}
	}
	std::cout << "\n";
	if (boolUseDashes) {
		SetConsoleTextAttribute(*hConsole, 6);
		std::cout << "-------------------------------------------\n";
		SetConsoleTextAttribute(*hConsole, 15);
	}
}

/// <summary>
/// Outputs standard 7 item header, accepts different titles when header text is set to non-empty value.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="intWidth"></param>
/// <param name="headerText"></param>
void OutputHeader(HANDLE* hConsole, int* intWidth, std::string headerText) {
	// Print header text if set
	if (!headerText.empty()) {
		SetConsoleTextAttribute(*hConsole, 14);
		std::cout << headerText << "\n";
	}
	else {
		// Use default if string is empty
		SetConsoleTextAttribute(*hConsole, 14);
		std::cout << "All Journeys" << "\n";
	}

	// Output standard 7 item header
	SetConsoleTextAttribute(*hConsole, 6);
	std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
	SetConsoleTextAttribute(*hConsole, 13);
	std::cout << std::setw(*intWidth) << "Travel Type" << std::setw(*intWidth) << "Travel Cost" << std::setw(*intWidth) << "Exp Cost" << std::setw(*intWidth) << "Total Cost" << std::setw(*intWidth) << "Exp Payable" << std::setw(*intWidth) << "Tax Reclaim" << std::setw(*intWidth) << "Exp not Cvrd" << std::setw(*intWidth) << "Final Pay\n";
	SetConsoleTextAttribute(*hConsole, 6);
	std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
	SetConsoleTextAttribute(*hConsole, 15);
}

/// <summary>
/// Outputs header variants, overload of OutputHeader. Variants include 1 and 2. 1 is header with number column, 2 is short 4 item header (for travel only items)
/// If header text is set to empty (""), defaults to "All Journeys".
/// </summary>
/// <param name="hConsole"></param>
/// <param name="intWidth"></param>
/// <param name="headerText"></param>
/// <param name="headerType"></param>
void OutputHeader(HANDLE* hConsole, int* intWidth, std::string headerText, int headerType) {
	// Print header text if set
	if (!headerText.empty()) {
		SetConsoleTextAttribute(*hConsole, 14);
		std::cout << headerText << "\n";
	}
	else {
		// Use default if string is empty
		SetConsoleTextAttribute(*hConsole, 14);
		std::cout << "All Journeys" << "\n";
	}
	switch (headerType)
	{
		case 1: {
			// Standard 7 item header with numbers column
			SetConsoleTextAttribute(*hConsole, 6);
			std::cout << "------------------------------------------------------------------------------------------------------------------------------\n";
			SetConsoleTextAttribute(*hConsole, 13);
			std::cout << std::setw(5) << "Number" << std::setw(*intWidth) << "Travel Type" << std::setw(*intWidth) << "Travel Cost" << std::setw(*intWidth) << "Exp Cost" << std::setw(*intWidth) << "Total Cost" << std::setw(*intWidth) << "Exp Payable" << std::setw(*intWidth) << "Tax Reclaim" << std::setw(*intWidth) << "Exp not Cvrd" << std::setw(*intWidth) << "Final Pay\n";
			SetConsoleTextAttribute(*hConsole, 6);
			std::cout << "------------------------------------------------------------------------------------------------------------------------------\n";
			SetConsoleTextAttribute(*hConsole, 15);
			break;
		}
		case 2: {
			// Short 4 item header
			SetConsoleTextAttribute(*hConsole, 6);
			std::cout << "------------------------------------------------------------\n";
			SetConsoleTextAttribute(*hConsole, 13);
			std::cout << std::setw(*intWidth) << "Travel Type" << std::setw(*intWidth) << "Travel Cost" << std::setw(*intWidth) << "Tax Reclaim" << std::setw(*intWidth) << "Final Pay" << "\n";
			SetConsoleTextAttribute(*hConsole, 6);
			std::cout << "------------------------------------------------------------\n";
			SetConsoleTextAttribute(*hConsole, 15);
			break;
		} 
		default: {
			SetConsoleTextAttribute(*hConsole, 12);
			std::cout << "Error : Header could not be rendered\n";
			SetConsoleTextAttribute(*hConsole, 15);
			break;
		}
	}
}

/// <summary>
/// Outputs a standard 7 item table with numbering, outputs all journeys passed in vector.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void OutputTable(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	// Output standard 7 item table
	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
	}
	else {
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			std::cout.precision(2);
			SetConsoleTextAttribute(*hConsole, 9);
			std::cout << std::setw(5) << (i + 1);
			std::cout.precision(2);
			SetConsoleTextAttribute(*hConsole, 10);
			std::cout << std::setw(*intWidth) << ((((int)vecJourneyCollection->at(i).travelType) == 0) ? "Travel" : "Travel & Exp");
			std::cout.precision(2);
			SetConsoleTextAttribute(*hConsole, 15);
			std::cout 
				<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).travelCost
				<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).expenseCost
				<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).totalCost
				<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).expensePayable
				<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).taxReclaim
				<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).expenseNotCovered
				<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).finalPayment << "\n";
		}
	}
}

/// <summary>
/// Overload of OutputTable that outputs non standard table variants. Option 1 outputs travel and expense only, option 2 outputs 4 item table (travel only) and option 3 outputs 
/// the same travel only journeys, but with all 7 columns.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
/// <param name="tableType"></param>
void OutputTable(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth, int tableType) {
	switch (tableType)
	{
		case 1: {
			// Output travel and expense journeys only
			if (vecJourneyCollection->size() <= 0) {
				SetConsoleTextAttribute(*hConsole, 12);
				std::cout << "There are currently no stored journeys\n";
				SetConsoleTextAttribute(*hConsole, 15);
			}
			else {
				for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
					if (vecJourneyCollection->at(i).travelType == TravelType::TravelAndExpense) {
						std::cout.precision(2);
						SetConsoleTextAttribute(*hConsole, 10);
						std::cout << std::setw(*intWidth) << ((((int)vecJourneyCollection->at(i).travelType) == 0) ? "Travel" : "Travel & Exp");
						std::cout.precision(2);
						SetConsoleTextAttribute(*hConsole, 15);
						std::cout
							<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).travelCost
							<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).expenseCost
							<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).totalCost
							<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).expensePayable
							<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).taxReclaim
							<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).expenseNotCovered
							<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).finalPayment << "\n";
					}
				}
			}
			break;
		}
		case 2: {
			// Output travel journeys only
			if (vecJourneyCollection->size() <= 0) {
				SetConsoleTextAttribute(*hConsole, 12);
				std::cout << "There are currently no stored journeys\n";
				SetConsoleTextAttribute(*hConsole, 15);
			}
			else {
				for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
					if (vecJourneyCollection->at(i).travelType == TravelType::Travel) {
						std::cout.precision(2);
						SetConsoleTextAttribute(*hConsole, 10);
						std::cout << std::setw(*intWidth) << ((((int)vecJourneyCollection->at(i).travelType) == 0) ? "Travel" : "Travel & Exp");
						std::cout.precision(2);
						SetConsoleTextAttribute(*hConsole, 15);
						std::cout
							<< std::setw(*intWidth) << std::fixed << vecJourneyCollection->at(i).travelCost
							<< std::setw(*intWidth) << std::fixed << vecJourneyCollection->at(i).taxReclaim
							<< std::setw(*intWidth) << std::fixed << vecJourneyCollection->at(i).finalPayment << "\n";
					}
				}
			}
			break;
		}
		case 3: {
			// Output travel journeys only, but all 7 columns
			if (vecJourneyCollection->size() <= 0) {
				SetConsoleTextAttribute(*hConsole, 12);
				std::cout << "There are currently no stored journeys\n";
				SetConsoleTextAttribute(*hConsole, 15);
			}
			else {
				for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
					if (vecJourneyCollection->at(i).travelType == TravelType::Travel) {
						std::cout.precision(2);
						SetConsoleTextAttribute(*hConsole, 10);
						std::cout << std::setw(*intWidth) << ((((int)vecJourneyCollection->at(i).travelType) == 0) ? "Travel" : "Travel & Exp");
						std::cout.precision(2);
						SetConsoleTextAttribute(*hConsole, 15);
						std::cout
							<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).travelCost
							<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).expenseCost
							<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).totalCost
							<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).expensePayable
							<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).taxReclaim
							<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).expenseNotCovered
							<< std::fixed << std::setw(*intWidth) << vecJourneyCollection->at(i).finalPayment << "\n";
					}
				}
			}
			break;
		}
		default: {
			SetConsoleTextAttribute(*hConsole, 12);
			std::cout << "Error : Table could not be rendered\n";
			SetConsoleTextAttribute(*hConsole, 15);
			break;
		}
	}
}

// Print out functions end

// Misc functions

void Pause(HANDLE* hConsole)
{
	std::cout << "\n";
	SetConsoleTextAttribute(*hConsole, 9);
	std::cout << "Press any key to continue...";
	SetConsoleTextAttribute(*hConsole, 15);
	_getch();
}

void TestFunction(std::vector<Journey>* vecJourneyCollection) {
	// Testing function, adds some example journeys with large decimal point inputs.

	vecJourneyCollection->push_back(Journey{ TravelType::Travel, 25.23534 });
	vecJourneyCollection->push_back(Journey{ TravelType::TravelAndExpense, 23.23, 10.9263 });
	vecJourneyCollection->push_back(Journey{ TravelType::Travel, 27 });
	vecJourneyCollection->push_back(Journey{ TravelType::TravelAndExpense, 120.2553, 57.823 });
}

// Misc functions end

// Functions end