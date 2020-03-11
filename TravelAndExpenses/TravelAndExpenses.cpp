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
#include "CalcFunctions.h"

struct ChoiceOption {
	int OptionNumber;
	std::string OptionText;
	int OptionHideThreshold;

	// Constructor for creating a Menu option with no HideThreshold (always visible)
	ChoiceOption(int passOptionNumber, std::string passOptionText) {
		OptionNumber = passOptionNumber;
		OptionText = passOptionText;
		OptionHideThreshold = 99;
	}

	// Constructor for creating a Menu option with a HideThreshold (hidden based on number)
	ChoiceOption(int passOptionNumber, std::string passOptionText, int passOptionHideThreshold) {
		OptionNumber = passOptionNumber;
		OptionText = passOptionText;
		OptionHideThreshold = passOptionHideThreshold;
	}
};

// Function namespace declaration

// Ouput print help functions.
void PrintIntro();
void PrintTravelHeader(int* intWidth);
void PrintTravelExpenseHeader(int* intWidth);
void PrintCurrentJourneysTravel(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void PrintCurrentJourneysTravelExpense(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void PrintSummaryHeader(int* intWidth);
void PrintAllJourneyNumberedHeader(int* intWidth);
void PrintAllJourneyNumberedHeader(int* intWidth, std::string message);
void PrintAllJourneysInOrder(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void OutputMenu(std::vector<Journey>* vecJourneyCollection, std::vector<ChoiceOption>* vecChoiceCollection, std::string introText, bool boolUseDashes, bool boolClearScreen);

// Misc helper functions
void Pause();

// Testing function : Automatically adds some journeys to save time when testing.
void TestFunction(std::vector<Journey>* vecJourneyCollection);

// Menu action functinons
void AddNewJourney(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewJourneys(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewSummary(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewCombinedSummary(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewTravelOnlySummary(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewTravelExpensesOnlySummary(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewSaveExport(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewSaveSummary(std::vector<Journey>* vecJourneyCollection);
void ViewComparison(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewCompareTwoJourneys(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewTotalTwoJourneys(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewDeleteSelect(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewDeleteJourney(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewSaveImportSelect(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewImportSummary(std::vector<Journey>* vecJourneyCollection);

//Function namespace declaration end

int main()
{
	int intWidth = 15;
	std::vector<Journey> vecJourneyCollection;

	PrintIntro();

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
		OutputMenu(&vecJourneyCollection, &vecChoiceCollection, "Welcome to the travel and expense system.", true, true);

		while (boolExitWhile == false) {
			std::cout << "Enter choice : ";
			intMenuMainChoice = ValidateIntInput();

			try {
				switch (intMenuMainChoice)
				{
				case 1: {
					AddNewJourney(&vecJourneyCollection, &intWidth);
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
						ViewJourneys(&vecJourneyCollection, &intWidth);
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
						ViewSummary(&vecJourneyCollection, &intWidth);
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
						ViewComparison(&vecJourneyCollection, &intWidth);
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
						ViewDeleteJourney(&vecJourneyCollection, &intWidth);
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
						ViewSaveImportSelect(&vecJourneyCollection, &intWidth);
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
void AddNewJourney(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
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
		OutputMenu(vecJourneyCollection, &vecChoiceCollection, "Add a new journey screen.", true, true);

		while (boolExitWhile != true) {
			std::cout << "Enter choice  : ";

			intTravelChoiceInput = ValidateIntInput();

			try {
				if (intTravelChoiceInput == 1) {
					travelTypeChoice = TravelType::Travel;
					std::cout << "Travel cost : ";

					dTravelCost = ValidateDoubleInput();

					Journey newJourney{ travelTypeChoice, dTravelCost };
					vecJourneyCollection->push_back(newJourney);
					boolExitWhile = true;
				}
				else if (intTravelChoiceInput == 2) {
					travelTypeChoice = TravelType::TravelAndExpense;
					std::cout << "Travel cost : ";

					dTravelCost = ValidateDoubleInput();

					std::cout << "Expenses cost : ";

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
						ViewJourneys(vecJourneyCollection, intWidth);
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
				std::cout << "Error : " << exp.what() << "\n";
			}
		}

		boolExitWhile = false;

		switch (intTravelChoiceInput) {
		case 3: {
			system("cls");
			strContinueAddingJourneys = "yes";
			break;
		}
		case 9: {
			strContinueAddingJourneys = "no";
			break;
		}
		default: {
			system("CLS");
			std::cout << "Journey succesfully added.\n";
			std::cout << "Would you like to add another journey?\n";
			std::cout << "Type 'yes' to add another, or type and enter any other value to return to menu.\n";

			while (!(std::cin >> strContinueAddingJourneys)) {
				// Makes user try again if input is not an int
				std::cout << "ERROR: a string must be entered : ";
				std::cin.clear();
				std::cin.ignore(123, '\n');
			}

			transform(strContinueAddingJourneys.begin(), strContinueAddingJourneys.end(), strContinueAddingJourneys.begin(), ::tolower);
			break;
		}
		}

	} while (strContinueAddingJourneys == "yes");

	strContinueAddingJourneys = "no";
}

void ViewJourneys(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	system("CLS");
	PrintTravelHeader(intWidth);
	PrintCurrentJourneysTravel(vecJourneyCollection, intWidth);
	std::cout << "\n";

	PrintTravelExpenseHeader(intWidth);
	PrintCurrentJourneysTravelExpense(vecJourneyCollection, intWidth);
	std::cout << "\n";
	ViewDeleteSelect(vecJourneyCollection, intWidth);
}

void ViewSummary(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intSummaryChoiceInput = 0;
	bool boolExitWhile = false;

	do {
		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "View Combined Summary" });
		vecChoiceCollection.push_back(ChoiceOption{ 2, "View Travel only Summary" });
		vecChoiceCollection.push_back(ChoiceOption{ 3, "View Travel and Expenses only Summary" });
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Return to menu" });
		OutputMenu(vecJourneyCollection, &vecChoiceCollection, "View and interact with summaries.", true, true);

		//PrintSummaryScreen();
		boolExitWhile = false;

		while (boolExitWhile == false) {
			std::cout << "Enter choice : ";
			intSummaryChoiceInput = ValidateIntInput();

			try {
				switch (intSummaryChoiceInput) {
				case 1: {
					boolExitWhile = true;
					ViewCombinedSummary(vecJourneyCollection, intWidth);
					break;
				}
				case 2: {
					boolExitWhile = true;
					ViewTravelOnlySummary(vecJourneyCollection, intWidth);
					break;
				}
				case 3: {
					boolExitWhile = true;
					ViewTravelExpensesOnlySummary(vecJourneyCollection, intWidth);
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

void ViewTotalSummaryTwoItems(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	system("cls");
	PrintAllJourneyNumberedHeader(intWidth, "Two item comparison : Totals");
	if (vecJourneyCollection->size() > 0) {
		PrintAllJourneysInOrder(vecJourneyCollection, intWidth);
	}

	try {
		auto totals = CalculateAllSummaryTotals(vecJourneyCollection);
		std::cout << "\n";
		std::cout.precision(2);
		std::cout
			<< std::fixed << std::setw(20) << "Totals :"
			<< std::fixed << std::setw(*intWidth) << totals.TotalTravel
			<< std::fixed << std::setw(*intWidth) << totals.TotalExpense
			<< std::fixed << std::setw(*intWidth) << totals.TotalOfTotals
			<< std::fixed << std::setw(*intWidth) << totals.TotalExpensePay
			<< std::fixed << std::setw(*intWidth) << totals.TotalTaxReclaim
			<< std::fixed << std::setw(*intWidth) << totals.ExpenseNotCovered
			<< std::fixed << std::setw(*intWidth) << totals.TotalFinalPay << "\n";
	}
	catch (std::exception& exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	ViewSaveExport(vecJourneyCollection, intWidth);
}

void ViewCompareSummaryTwoItems(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	system("cls");
	PrintAllJourneyNumberedHeader(intWidth, "Two item comparison : Comparison");
	if (vecJourneyCollection->size() > 0) {
		PrintAllJourneysInOrder(vecJourneyCollection, intWidth);
	}

	try {
		auto totals = CalculateAllSummaryTotals(vecJourneyCollection);
		std::cout << "\n";
		std::cout.precision(2);
		std::cout
			<< std::fixed << std::setw(20) << "Totals :"
			<< std::fixed << std::setw(*intWidth) << totals.TotalTravel
			<< std::fixed << std::setw(*intWidth) << totals.TotalExpense
			<< std::fixed << std::setw(*intWidth) << totals.TotalOfTotals
			<< std::fixed << std::setw(*intWidth) << totals.TotalExpensePay
			<< std::fixed << std::setw(*intWidth) << totals.TotalTaxReclaim
			<< std::fixed << std::setw(*intWidth) << totals.ExpenseNotCovered
			<< std::fixed << std::setw(*intWidth) << totals.TotalFinalPay << "\n";
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
			<< std::fixed << std::setw(*intWidth) << largest.LargestTravel
			<< std::fixed << std::setw(*intWidth) << largest.LargestExpense
			<< std::fixed << std::setw(*intWidth) << largest.LargestOfTotals
			<< std::fixed << std::setw(*intWidth) << largest.LargestExpensePay
			<< std::fixed << std::setw(*intWidth) << largest.LargestTaxReclaim
			<< std::fixed << std::setw(*intWidth) << largest.LargestNotCovered
			<< std::fixed << std::setw(*intWidth) << largest.LargestFinalPay << "\n";
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
			<< std::fixed << std::setw(*intWidth) << difference.DiffTravel
			<< std::fixed << std::setw(*intWidth) << difference.DiffExpense
			<< std::fixed << std::setw(*intWidth) << difference.DiffOfTotals
			<< std::fixed << std::setw(*intWidth) << difference.DiffExpensePay
			<< std::fixed << std::setw(*intWidth) << difference.DiffTaxReclaim
			<< std::fixed << std::setw(*intWidth) << difference.DifffNotCovered
			<< std::fixed << std::setw(*intWidth) << difference.DiffFinalPay << "\n";
	}
	catch (std::exception& exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	ViewSaveExport(vecJourneyCollection, intWidth);
}

void ViewCombinedSummary(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	system("cls");
	PrintSummaryHeader(intWidth);
	if (vecJourneyCollection->size() > 0) {
		PrintCurrentJourneysTravel(vecJourneyCollection, intWidth);
		PrintCurrentJourneysTravelExpense(vecJourneyCollection, intWidth);
	}

	try {
		auto totals = CalculateAllSummaryTotals(vecJourneyCollection);
		std::cout << "\n";
		std::cout.precision(2);
		std::cout
			<< std::fixed << std::setw(*intWidth) << "Totals :"
			<< std::fixed << std::setw(*intWidth) << totals.TotalTravel
			<< std::fixed << std::setw(*intWidth) << totals.TotalExpense
			<< std::fixed << std::setw(*intWidth) << totals.TotalOfTotals
			<< std::fixed << std::setw(*intWidth) << totals.TotalExpensePay
			<< std::fixed << std::setw(*intWidth) << totals.TotalTaxReclaim
			<< std::fixed << std::setw(*intWidth) << totals.ExpenseNotCovered
			<< std::fixed << std::setw(*intWidth) << totals.TotalFinalPay << "\n";
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
			<< std::fixed << std::setw(*intWidth) << average.AverageTravel
			<< std::fixed << std::setw(*intWidth) << average.AverageExpense
			<< std::fixed << std::setw(*intWidth) << average.AverageOfTotals
			<< std::fixed << std::setw(*intWidth) << average.AverageExpensePay
			<< std::fixed << std::setw(*intWidth) << average.AverageTaxReclaim
			<< std::fixed << std::setw(*intWidth) << average.AverageNotCovered
			<< std::fixed << std::setw(*intWidth) << average.AverageFinalPay << "\n";
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
			<< std::fixed << std::setw(*intWidth) << largest.LargestTravel
			<< std::fixed << std::setw(*intWidth) << largest.LargestExpense
			<< std::fixed << std::setw(*intWidth) << largest.LargestOfTotals
			<< std::fixed << std::setw(*intWidth) << largest.LargestExpensePay
			<< std::fixed << std::setw(*intWidth) << largest.LargestTaxReclaim
			<< std::fixed << std::setw(*intWidth) << largest.LargestNotCovered
			<< std::fixed << std::setw(*intWidth) << largest.LargestFinalPay << "\n";
	}
	catch (std::exception& exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	ViewSaveExport(vecJourneyCollection, intWidth);
}

void ViewTravelOnlySummary(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	system("cls");
	PrintTravelHeader(intWidth);
	PrintCurrentJourneysTravel(vecJourneyCollection, intWidth);
	try {
		auto totals = CalculateTravelSummaryTotals(vecJourneyCollection);
		std::cout << "\n";
		std::cout.precision(2);
		std::cout
			<< std::fixed << std::setw(*intWidth) << "Totals :"
			<< std::fixed << std::setw(*intWidth) << totals.TotalTravel
			<< std::fixed << std::setw(*intWidth) << totals.TotalTaxReclaim
			<< std::fixed << std::setw(*intWidth) << totals.TotalFinalPay << "\n";
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
			<< std::fixed << std::setw(*intWidth) << average.AverageTravel
			<< std::fixed << std::setw(*intWidth) << average.AverageTaxReclaim
			<< std::fixed << std::setw(*intWidth) << average.AverageFinalPay << "\n";
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
			<< std::fixed << std::setw(*intWidth) << largest.LargestTravel
			<< std::fixed << std::setw(*intWidth) << largest.LargestTaxReclaim
			<< std::fixed << std::setw(*intWidth) << largest.LargestFinalPay << "\n";
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

	ViewSaveExport(&vecTravelOnlyCollection, intWidth);
}

void ViewTravelExpensesOnlySummary(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	system("cls");
	PrintTravelExpenseHeader(intWidth);
	PrintCurrentJourneysTravelExpense(vecJourneyCollection, intWidth);
	try {
		auto totals = CalculateTravelExpenseSummaryTotals(vecJourneyCollection);
		std::cout << "\n";
		std::cout.precision(2);
		std::cout
			<< std::fixed << std::setw(*intWidth) << "Totals :"
			<< std::fixed << std::setw(*intWidth) << totals.TotalTravel
			<< std::fixed << std::setw(*intWidth) << totals.TotalExpense
			<< std::fixed << std::setw(*intWidth) << totals.TotalOfTotals
			<< std::fixed << std::setw(*intWidth) << totals.TotalExpensePay
			<< std::fixed << std::setw(*intWidth) << totals.TotalTaxReclaim
			<< std::fixed << std::setw(*intWidth) << totals.ExpenseNotCovered
			<< std::fixed << std::setw(*intWidth) << totals.TotalFinalPay << "\n";
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
			<< std::fixed << std::setw(*intWidth) << average.AverageTravel
			<< std::fixed << std::setw(*intWidth) << average.AverageExpense
			<< std::fixed << std::setw(*intWidth) << average.AverageOfTotals
			<< std::fixed << std::setw(*intWidth) << average.AverageExpensePay
			<< std::fixed << std::setw(*intWidth) << average.AverageTaxReclaim
			<< std::fixed << std::setw(*intWidth) << average.AverageNotCovered
			<< std::fixed << std::setw(*intWidth) << average.AverageFinalPay << "\n";
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
			<< std::fixed << std::setw(*intWidth) << largest.LargestTravel
			<< std::fixed << std::setw(*intWidth) << largest.LargestExpense
			<< std::fixed << std::setw(*intWidth) << largest.LargestOfTotals
			<< std::fixed << std::setw(*intWidth) << largest.LargestExpensePay
			<< std::fixed << std::setw(*intWidth) << largest.LargestTaxReclaim
			<< std::fixed << std::setw(*intWidth) << largest.LargestNotCovered
			<< std::fixed << std::setw(*intWidth) << largest.LargestFinalPay << "\n";
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

	ViewSaveExport(&vecTravelExpenseOnlyCollection, intWidth);
}

void ViewSaveSummary(std::vector<Journey>* vecJourneyCollection) {
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

	Pause();
}

void ViewImportSummary(std::vector<Journey>* vecJourneyCollection) {

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

			Pause();
		}


		Pause();
	}
}

void ViewComparison(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intComparisonChoiceInput = 0;
	bool boolExitWhile = false;

	do {
		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "Compare two journeys", 2 });
		vecChoiceCollection.push_back(ChoiceOption{ 2, "Total two journeys", 2 });
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Return to menu" });
		OutputMenu(vecJourneyCollection, &vecChoiceCollection, "Make Comparisons and total invoices.", true, true);

		boolExitWhile = false;

		while (boolExitWhile == false) {
			std::cout << "Enter choice : ";
			intComparisonChoiceInput = ValidateIntInput();

			try {
				switch (intComparisonChoiceInput) {
				case 1: {
					boolExitWhile = true;
					ViewCompareTwoJourneys(vecJourneyCollection, intWidth);
					break;
				}
				case 2: {
					boolExitWhile = true;
					ViewTotalTwoJourneys(vecJourneyCollection, intWidth);
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
void ViewSaveExport(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intSaveExportChoiceInput = 0;
	bool boolExitWhile = false;

	do {
		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "Export list as CSV" });
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Return to previous" });
		OutputMenu(vecJourneyCollection, &vecChoiceCollection, "Make Comparisons and total invoices.", false, false);

		boolExitWhile = false;

		while (boolExitWhile == false) {
			std::cout << "Enter choice : ";
			intSaveExportChoiceInput = ValidateIntInput();

			try {
				switch (intSaveExportChoiceInput) {
				case 1: {
					ViewSaveSummary(vecJourneyCollection);
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
void ViewCompareTwoJourneys(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intCompareFirst = 0, intCompareSecond = 0;
	std::vector<Journey> vecJourneyCompare;

	system("cls");
	PrintAllJourneyNumberedHeader(intWidth);
	PrintAllJourneysInOrder(vecJourneyCollection, intWidth);

	std::cout << "\n";
	std::cout << "Please specify number of the first journey you would like to compare.\n";
	do {
		std::cout << "Enter Choice : ";
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
		std::cout << "Enter Choice : ";
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

	ViewCompareSummaryTwoItems(&vecJourneyCompare, intWidth);
}

/// <summary>
/// Asks user to choose two items currently in system. Then displays comparison.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewTotalTwoJourneys(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intTotalFirst = 0, intTotalSecond = 0;
	std::vector<Journey> vecJourneyTotal;

	system("cls");
	PrintAllJourneyNumberedHeader(intWidth);
	PrintAllJourneysInOrder(vecJourneyCollection, intWidth);

	std::cout << "\n";
	std::cout << "Please specify number of the first journey you would like to total.\n";
	do {
		std::cout << "Enter Choice : ";
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
		std::cout << "Enter Choice : ";
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

	ViewTotalSummaryTwoItems(&vecJourneyTotal, intWidth);
}

/// <summary>
/// Delete choice menu, allows user to choose to delete an item, or to return to previous. Passes onto the more generic ViewDeleteJourney screen that handles deleteing a journey.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewDeleteSelect(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intDeleteChoiceInput = 0;
	bool boolExitWhile = false;

	do {

		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "Delete a journey" });
		vecChoiceCollection.push_back(ChoiceOption{ 2, "Export List as CSV"});
		vecChoiceCollection.push_back(ChoiceOption{ 3, "Add new Journey"});
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Return to previous" });
		OutputMenu(vecJourneyCollection, &vecChoiceCollection, "Please specifiy which of the following options you would like to do.", false, false);

		boolExitWhile = false;

		while (boolExitWhile == false) {
			std::cout << "Enter choice : ";
			intDeleteChoiceInput = ValidateIntInput();

			try {
				switch (intDeleteChoiceInput) {
				case 1: {
					ViewDeleteJourney(vecJourneyCollection, intWidth);
					boolExitWhile = true;
					intDeleteChoiceInput = 9;
					break;
				}
				case 2: {
					ViewSaveSummary(vecJourneyCollection);
					boolExitWhile = true;
					intDeleteChoiceInput = 9;
					break;
				}
				case 3: {
					AddNewJourney(vecJourneyCollection, intWidth);
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
void ViewDeleteJourney(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intJourneyToDelete = 0, intCompareSecond = 0;
	bool boolIsValid = false;
	bool boolIsExiting = false;

	system("cls");
	PrintAllJourneyNumberedHeader(intWidth);
	PrintAllJourneysInOrder(vecJourneyCollection, intWidth);

	std::cout << "\n";
	std::cout << "Please specify number of the journey you would like to remove. Type '0' to cancel. \n";

	while (boolIsValid == false) {
		std::cout << "Enter Choice : ";
		intJourneyToDelete = ValidateIntInput() - 1;

		if (intJourneyToDelete == -1) {
			boolIsValid = true;
			boolIsExiting = true;
		}
		else if (InRange(0, (int)vecJourneyCollection->size() - 1, intJourneyToDelete)) {
			boolIsValid = true;
		}
		else {
			std::cout << "The number you specified is not a valid item currently in the list.\n";
		}
	}

	if (!boolIsExiting) {
		try {
			vecJourneyCollection->erase(vecJourneyCollection->begin() + intJourneyToDelete);
		}
		catch (std::exception &ex) {
			std::cout << "Sorry, something went wrong while removing this item.\n";
		}

		std::cout << "\n";
		std::cout << "Journey " << (intJourneyToDelete + 1) << " successfully removed.\n";

		Pause();
	}

	//do {
	//	std::cout << "Enter Choice : ";
	//	intJourneyToDelete = ValidateIntInput() - 1;

	//	if (InRange(0, (int)vecJourneyCollection->size() - 1, intJourneyToDelete)) {
	//		// Try to erase the specified choice.
	//		try {
	//			vecJourneyCollection->erase(vecJourneyCollection->begin() + intJourneyToDelete);
	//		}
	//		catch (std::exception ex) {
	//			std::cout << "The number you specified is not a valid item currently in the list.\n";
	//		}
	//	}
	//	else {
	//		std::cout << "The number you specified is not a valid item currently in the list.\n";
	//	}
	//} while (!InRange(0, (int)vecJourneyCollection->size() - 1, intJourneyToDelete));
}

void ViewSaveImportSelect(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intSaveImportChoiceInput = 0;
	bool boolExitWhile = false;

	do {
		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "Export current Journeys" });
		vecChoiceCollection.push_back(ChoiceOption{ 2, "Import Journeys from CSV" });
		vecChoiceCollection.push_back(ChoiceOption{ 3, "View current journeys" });
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Return to previous" });
		OutputMenu(vecJourneyCollection, &vecChoiceCollection, "Import or export journeys.", true, true);

		boolExitWhile = false;

		while (boolExitWhile == false) {
			std::cout << "Enter choice : ";
			intSaveImportChoiceInput = ValidateIntInput();

			try {
				switch (intSaveImportChoiceInput) {
				case 1: {
					boolExitWhile = true;
					ViewSaveSummary(vecJourneyCollection);
					break;
				}
				case 2: {
					boolExitWhile = true;
					ViewImportSummary(vecJourneyCollection);
					break;
				}
				case 3: {
					boolExitWhile = true;
					ViewJourneys(vecJourneyCollection, intWidth);
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

// Print out functions

/// <summary>
/// Prints the summary header for generic journey view screens
/// </summary>
/// <param name="intWidth"></param>
void PrintSummaryHeader(int* intWidth) {
	std::cout << "All Journeys" << "\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << std::setw(*intWidth) << "Travel Type" << std::setw(*intWidth) << "Travel Cost" << std::setw(*intWidth) << "Exp Cost" << std::setw(*intWidth) << "Total Cost" << std::setw(*intWidth) << "Exp Payable" << std::setw(*intWidth) << "Tax Reclaim" << std::setw(*intWidth) << "Exp not Cvrd" << std::setw(*intWidth) << "Final Pay\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
}

/// <summary>
/// Prints out a header for when a numbered list of all journeys currently stored in the vector are needed (for selection etc).
/// </summary>
/// <param name="intWidth"></param>
void PrintAllJourneyNumberedHeader(int* intWidth) {
	std::cout << "All Journeys" << "\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << std::setw(5) << "Number" << std::setw(*intWidth) << "Travel Type" << std::setw(*intWidth) << "Travel Cost" << std::setw(*intWidth) << "Exp Cost" << std::setw(*intWidth) << "Total Cost" << std::setw(*intWidth) << "Exp Payable" << std::setw(*intWidth) << "Tax Reclaim" << std::setw(*intWidth) << "Exp not Cvrd" << std::setw(*intWidth) << "Final Pay\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------------\n";
}

void PrintAllJourneyNumberedHeader(int* intWidth, std::string message) {
	std::cout << message << "\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << std::setw(5) << "Number" << std::setw(*intWidth) << "Travel Type" << std::setw(*intWidth) << "Travel Cost" << std::setw(*intWidth) << "Exp Cost" << std::setw(*intWidth) << "Total Cost" << std::setw(*intWidth) << "Exp Payable" << std::setw(*intWidth) << "Tax Reclaim" << std::setw(*intWidth) << "Exp not Cvrd" << std::setw(*intWidth) << "Final Pay\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------------\n";
}

/// <summary>
/// Prints the travel only expense header, takes the globally defined column width declared in main.
/// </summary>
/// <param name="intWidth"></param>
void PrintTravelHeader(int* intWidth) {
	std::cout << "Travel Only Journeys" << "\n";
	std::cout << "------------------------------------------------------------\n";
	std::cout << std::setw(*intWidth) << "Travel Type" << std::setw(*intWidth) << "Travel Cost" << std::setw(*intWidth) << "Tax Reclaim" << std::setw(*intWidth) << "Final Pay" << "\n";
	std::cout << "------------------------------------------------------------\n";
}

/// <summary>
/// Prints the travel expense header, takes the globally defined column width declared in main.
/// </summary>
/// <param name="intWidth"></param>
void PrintTravelExpenseHeader(int* intWidth) {
	std::cout << "Travel and Expenses Journeys" << "\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << std::setw(*intWidth) << "Travel Type" << std::setw(*intWidth) << "Travel Cost" << std::setw(*intWidth) << "Exp Cost" << std::setw(*intWidth) << "Total Cost" << std::setw(*intWidth) << "Exp Payable" << std::setw(*intWidth) << "Tax Reclaim" << std::setw(*intWidth) << "Exp not Cvrd" << std::setw(*intWidth) << "Final Pay\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
}

/// <summary>
/// Prints the currently stored Journeys that are of the Travel type from the Journey vector.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void PrintCurrentJourneysTravel(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
	}
	else {
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			if (vecJourneyCollection->at(i).travelType == TravelType::Travel) {
				std::cout.precision(2);
				std::cout
					<< std::setw(*intWidth) << ((((int)vecJourneyCollection->at(i).travelType) == 0) ? "Travel" : "Travel & Exp")
					<< std::setw(*intWidth) << std::fixed << vecJourneyCollection->at(i).travelCost
					<< std::setw(*intWidth) << std::fixed << vecJourneyCollection->at(i).taxReclaim
					<< std::setw(*intWidth) << std::fixed << vecJourneyCollection->at(i).finalPayment << "\n";
			}
		}
	}
}

/// <summary>
/// Prints the currently stored Journeys that are of the TravelAndExpense type from the Journey vector.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void PrintCurrentJourneysTravelExpense(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
	}
	else {
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			if (vecJourneyCollection->at(i).travelType == TravelType::TravelAndExpense) {
				std::cout.precision(2);
				std::cout
					<< std::setw(*intWidth) << ((((int)vecJourneyCollection->at(i).travelType) == 0) ? "Travel" : "Travel & Exp")
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

}

/// <summary>
/// Prints the intro warning/notice when loading the program.
/// </summary>
void PrintIntro() {
	// Notice for users about setup needed to ensure proper formatted output.
	std::cout << "### NOTICE ###\n";
	std::cout << "To ensure proper text formatting while in use, please make sure you widen the console window. ";
	std::cout << "You can do this by dragging the window larger or by right clicking on the top of this window then go to properties, ";
	std::cout << "and the layout tab. Setting the console width to 127 is recommended. Not doing this could result in text being wrapped ";
	std::cout << "ruining some of the output tables.\n";
	std::cout << "### NOTICE ###\n";

	Pause();
}

void PrintAllJourneysInOrder(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
	}
	else {
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			std::cout.precision(2);
			std::cout
				<< std::setw(5) << (i + 1)
				<< std::setw(*intWidth) << ((((int)vecJourneyCollection->at(i).travelType) == 0) ? "Travel" : "Travel & Exp")
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

void OutputMenu(std::vector<Journey>* vecJourneyCollection, std::vector<ChoiceOption>* vecChoiceCollection, std::string introText, bool boolUseDashes, bool boolClearScreen) {
	if (boolClearScreen) {
		system("cls");
	}
	if (boolUseDashes) {
		std::cout << "-------------------------------------------\n";
	}
	std::cout << "\n";
	std::cout << introText;
	std::cout << "\nPlease specify your option :\n";
	std::cout << "\n";
	for (size_t i = 0; i < vecChoiceCollection->size(); i++)
	{
		if (vecChoiceCollection->at(i).OptionHideThreshold != 99) {
			if (vecChoiceCollection->at(i).OptionHideThreshold == 0) {
				if (vecJourneyCollection->size() > vecChoiceCollection->at(i).OptionHideThreshold) {
					std::cout << "Option " << vecChoiceCollection->at(i).OptionNumber << " : " << vecChoiceCollection->at(i).OptionText << "\n";
				}
			}
			else {
				if (vecJourneyCollection->size() >= vecChoiceCollection->at(i).OptionHideThreshold) {
					std::cout << "Option " << vecChoiceCollection->at(i).OptionNumber << " : " << vecChoiceCollection->at(i).OptionText << "\n";
				}
			}
		}
		else {
			std::cout << "Option " << vecChoiceCollection->at(i).OptionNumber << " : " << vecChoiceCollection->at(i).OptionText << "\n";
		}
	}
	std::cout << "\n";
	if (boolUseDashes) {
		std::cout << "-------------------------------------------\n";
	}
}

// Print out functions end

// Misc functions

void Pause()
{
	std::cout << "\n";
	std::cout << "Press any key to continue...";
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