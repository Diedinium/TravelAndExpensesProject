// TravelAndExpenses.cpp : The main application file for the travel and expenses console app.
// Please note: This file has XML style comments to enable intellisense, this is not a standard feature of C++! You will need an extension called "CppTripleSlash - xml doc comments for c++"
// installed in order for this functionality to work, this not being installed does not affect functionality, it simply results in less descriptive function descriptions.

#include <cstdlib>
#include <numeric>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include "Structs.h"
#include "MiscFunctions.h"
#include "CalcFunctions.h"
#include "OutputFunctions.h"

#pragma region Function Declarations

// Note : Miscallaneous, Calculation and Output functions are declared in their respective header files, and defined in their respective .cpp source file.

// Menu action functinons
void ViewAddNewJourney(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
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
void ViewImportSummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewCompareSummaryTwoItems(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewTotalSummaryTwoItems(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth);

// Testing function : Automatically adds some journeys to save time when testing.
void TestFunction(std::vector<Journey>* vecJourneyCollection);

#pragma endregion

int main()
{
	// Get the output handle (allows changing of the console text colour.
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Get the console window. Resize and position to suit output tables.
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) {
		MoveWindow(hwnd, 100, 100, 1075, 500, TRUE);
	}
	
	// Set width and create vector to hold all journeys in use within the application.
	int intWidth = 15;
	std::vector<Journey> vecJourneyCollection;

	// Output the intro
	OutputIntro(&hConsole);

	int intMenuMainChoice = 0;
	bool boolExitWhile = false;

	// Test function that inputs some example journeys for testing purposes, uncomment to use.
	//TestFunction(&vecJourneyCollection);

	// Loop until user enters 9 - program then exits.
	do {
		// Output selection screen
		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "Enter a new Journey" });
		vecChoiceCollection.push_back(ChoiceOption{ 2, "View current journeys", 0 });
		vecChoiceCollection.push_back(ChoiceOption{ 3, "Summaries", 2 });
		vecChoiceCollection.push_back(ChoiceOption{ 4, "Comparisons and itemised summary", 2 });
		vecChoiceCollection.push_back(ChoiceOption{ 5, "Remove a Journey", 0 });
		vecChoiceCollection.push_back(ChoiceOption{ 6, "Import/Export Journeys", 0 });
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Exit" });

		// Set the text different depending on number of journeys in system.
		if (vecJourneyCollection.size() >= 2) {
			OutputMenu(&hConsole, &vecJourneyCollection, &vecChoiceCollection, "Welcome to the travel and expense system.", true, true);
		}
		else if (vecJourneyCollection.size() < 2) {
			OutputMenu(&hConsole, &vecJourneyCollection, &vecChoiceCollection, "Welcome to the travel and expense system. Please note that there are more menu options than are currently being displayed, once you have entered two journeys all options become available.", true, true);
		}

		// Loop until valid choice is made, when valid choice is entered, exitWhile is set to true and menu gets output again.
		while (boolExitWhile == false) {
			SetConsoleTextAttribute(hConsole, 9);
			std::cout << "Enter choice : ";
			SetConsoleTextAttribute(hConsole, 15);
			// Get choice and validate that input is an int.
			intMenuMainChoice = ValidateIntInput(&hConsole);

			// Once valid choice is provided, run specified function. If there are not enough items in the vector, error is thrown instead.
			try {
				switch (intMenuMainChoice)
				{
				case 1: {
					// Go to view that allows user to add new journeys when "1" is entered.
					ViewAddNewJourney(&hConsole, &vecJourneyCollection, &intWidth);
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
						// Go to view save/import menu when "2" is entered.
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
						// Go to view summaries menu when "3" is entered.
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
						// Go to view comparisons menu when "4" is entered.
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
						// Go to delete journey menu when "5" is entered.
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
						// Go to view save/import menu when "6" is entered.
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
				OutputError(&hConsole, exp.what());
				boolExitWhile = false;
			}
		}

		boolExitWhile = false;

	} while (intMenuMainChoice != 9);

	return 0;
}

// Functions

// Views/Menu screens

/// <summary>
/// Add new journey view. Function that allows user to enter new journeys.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewAddNewJourney(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	// Declare variables.
	std::string strContinueAddingJourneys;
	bool boolExitWhile = false;
	int intTravelChoiceInput;
	TravelType travelTypeChoice;
	double dTravelCost = 0;
	double dExpenseCost = 0;

	// Loops while user specifies "Y" to adding more journeys.
	do {
		// Output choice options
		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "Travel only" });
		vecChoiceCollection.push_back(ChoiceOption{ 2, "Travel and expenses" });
		vecChoiceCollection.push_back(ChoiceOption{ 3, "View Current journeys", 0 });
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Return to menu" });
		OutputMenu(hConsole, vecJourneyCollection, &vecChoiceCollection, "Add a new journey screen.", true, true);

		// Loop until exit condition is met.
		while (boolExitWhile != true) {
			SetConsoleTextAttribute(*hConsole, 9);
			std::cout << "Enter choice : ";
			SetConsoleTextAttribute(*hConsole, 15);

			// Validate input is an int
			intTravelChoiceInput = ValidateIntInput(hConsole);

			try {
				if (intTravelChoiceInput == 1) {
					// Input travel cost
					travelTypeChoice = TravelType::Travel;
					SetConsoleTextAttribute(*hConsole, 9);
					std::cout << "Travel cost : ";
					SetConsoleTextAttribute(*hConsole, 15);

					dTravelCost = ValidateDoubleInput(hConsole);

					// Create journey and add to vector.
					vecJourneyCollection->push_back(Journey{ travelTypeChoice, dTravelCost });
					boolExitWhile = true;
				}
				else if (intTravelChoiceInput == 2) {
					// Input travel cost
					travelTypeChoice = TravelType::TravelAndExpense;
					SetConsoleTextAttribute(*hConsole, 9);
					std::cout << "Travel cost : ";
					SetConsoleTextAttribute(*hConsole, 15);

					dTravelCost = ValidateDoubleInput(hConsole);

					// Input expense cost
					SetConsoleTextAttribute(*hConsole, 9);
					std::cout << "Expenses cost : ";
					SetConsoleTextAttribute(*hConsole, 15);

					dExpenseCost = ValidateDoubleInput(hConsole);

					// Create journey and add to vector.
					vecJourneyCollection->push_back(Journey{ travelTypeChoice, dTravelCost, dExpenseCost });
					boolExitWhile = true;
				}
				else if (intTravelChoiceInput == 3) {
					if (vecJourneyCollection->size() <= 0) {
						throw std::runtime_error("This option is not yet a valid option, there are no stored journeys.");
						boolExitWhile = false;
					}
					else {
						// View current journeys when "3" is entered.
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
				OutputError(hConsole, exp.what());
			}
		}

		boolExitWhile = false;

		// Allows user to loop and input more journeys, sets exit condition automatically in the case that user choose to view journeys or exit to menu.
		switch (intTravelChoiceInput) {
			case 3: {
				system("cls");
				// If user is viewing journeys, allow user to add more journeys once they return to this function.
				strContinueAddingJourneys = "Y";
				break;
			}
			case 9: {
				// Set option to N if user is intending to exit this function.
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

				// Loops while user choice is not "Y" or "N"
				bool boolExitWhileString = false;
				while (boolExitWhileString == false)
				{
					std::cin.clear();
					std::cin.ignore(123, '\n');
					std::cin >> strContinueAddingJourneys;
					// Ensure that input is always in upper case.
					transform(strContinueAddingJourneys.begin(), strContinueAddingJourneys.end(), strContinueAddingJourneys.begin(), std::toupper);

					// Check if value is valid
					if (strContinueAddingJourneys.find("Y") != std::string::npos) {
						boolExitWhileString = true;
					}
					else if (strContinueAddingJourneys.find("N") != std::string::npos) {
						boolExitWhileString = true;
					}
					else {
						OutputError(hConsole, "ERROR: Choice must be Y or N : ", true);
					}
				}
				boolExitWhile = false;
				break;
			}
		}

	} while (strContinueAddingJourneys == "Y");

	strContinueAddingJourneys = "N";
}

/// <summary>
/// Display journeys view. Displays all journeys currently in the main vector (vecJourneyCollection). Prints travel only journeys and then travel and expense journeys. Displays some choice options that allow user to view journeys 
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewJourneys(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	system("CLS");
	// Outputs travel only journeys
	if (FindNumOfJourneys(vecJourneyCollection, TravelType::Travel) > 0) {
		OutputHeader(hConsole, intWidth, "Travel Only Journeys", 2);
		OutputTable(hConsole, vecJourneyCollection, intWidth, 2);
		std::cout << "\n";
	}

	// Outputs travel and expense journeys
	if (FindNumOfJourneys(vecJourneyCollection, TravelType::TravelAndExpense) > 0) {
		OutputHeader(hConsole, intWidth, "Travel and Expense Journeys");
		OutputTable(hConsole, vecJourneyCollection, intWidth, 1);
		std::cout << "\n";
	}

	// Ouputs choices to allow user to select what to do next.
	ViewDeleteSelect(hConsole, vecJourneyCollection, intWidth);
}

/// <summary>
/// Delete choice select menu. Dispalyed in various locations in program, allows user to perform actions on displayed list of journeys.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewDeleteSelect(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	// Declare variables.
	int intDeleteChoiceInput = 0;
	bool boolExitWhile = false;

	// Loop until "9" is entered.
	do {
		// Output menu choices
		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "Delete a journey" });
		vecChoiceCollection.push_back(ChoiceOption{ 2, "Export List as CSV" });
		vecChoiceCollection.push_back(ChoiceOption{ 3, "Add new Journey" });
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Return to previous" });
		OutputMenu(hConsole, vecJourneyCollection, &vecChoiceCollection, "Please specifiy which of the following options you would like to do.", false, false);

		// Loop until valid choice is entered.
		boolExitWhile = false;
		while (boolExitWhile == false) {
			// Validate input is an int
			SetConsoleTextAttribute(*hConsole, 9);
			std::cout << "Enter choice : ";
			SetConsoleTextAttribute(*hConsole, 15);
			intDeleteChoiceInput = ValidateIntInput(hConsole);

			try {
				switch (intDeleteChoiceInput) {
				case 1: {
					// Run view delete journeys when "1" entered.
					ViewDeleteJourney(hConsole, vecJourneyCollection, intWidth);
					boolExitWhile = true;
					intDeleteChoiceInput = 9;
					break;
				}
				case 2: {
					// Run view save summary when "2" entered.
					ViewSaveSummary(hConsole, vecJourneyCollection);
					boolExitWhile = true;
					intDeleteChoiceInput = 9;
					break;
				}
				case 3: {
					// Run add new journey view when "3" entered.
					ViewAddNewJourney(hConsole, vecJourneyCollection, intWidth);
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
				OutputError(hConsole, exp.what());
			}
		}

	} while (intDeleteChoiceInput != 9);

	intDeleteChoiceInput = 0;
	boolExitWhile = false;
}

/// <summary>
/// Save summary view. Saves passed vector of journeys to a .csv file.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
void ViewSaveSummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection) {
	system("cls");

	// Declare variables.
	std::fstream fout;
	std::string fnameOriginal = "journeyList.csv";
	std::string fname = "journeyList.csv";
	int intCount = 0;

	// Loop until a valid file name is found (iterates by 1 until an unused file name is found.)
	while (FileExists(fname))
	{
		fname = fnameOriginal;
		fname = fname.insert(11, std::to_string(intCount));
		intCount++;
	}

	// Add a row of headers to the csv file.
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

	// Loop and add values to the file, ouputs all 7 values of each journey in the vector.
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

	// Explain to user where file was saved.
	SetConsoleTextAttribute(*hConsole, 14);
	std::cout << "Journeys written to '";
	SetConsoleTextAttribute(*hConsole, 13);
	std::cout << fname;
	SetConsoleTextAttribute(*hConsole, 14);
	std::cout << "'. Please check the directory that you ran this application from to find this file." << "\n";
	SetConsoleTextAttribute(*hConsole, 15);
	Pause(hConsole);
}

/// <summary>
/// Summary select view. Allows user to choose a summary type to view.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewSummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	// Declare variables.
	int intSummaryChoiceInput = 0;
	bool boolExitWhile = false;

	// Loop until 9 is specified as the choice option
	do {
		// Output menu choices.
		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "View Combined Summary" });
		vecChoiceCollection.push_back(ChoiceOption{ 2, "View Travel only Summary" });
		vecChoiceCollection.push_back(ChoiceOption{ 3, "View Travel and Expenses only Summary" });
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Return to menu" });
		OutputMenu(hConsole, vecJourneyCollection, &vecChoiceCollection, "View and interact with summaries.", true, true);

		// Loop until exit condition is met (valid choice specified)
		boolExitWhile = false;
		while (boolExitWhile == false) {
			SetConsoleTextAttribute(*hConsole, 9);
			std::cout << "Enter choice : ";
			SetConsoleTextAttribute(*hConsole, 15);
			intSummaryChoiceInput = ValidateIntInput(hConsole);

			// Once valid numeric choice is provided, execute relevant function.
			try {
				switch (intSummaryChoiceInput) {
				case 1: {
					boolExitWhile = true;
					// View combined summary when "1" is entered.
					ViewCombinedSummary(hConsole, vecJourneyCollection, intWidth);
					break;
				}
				case 2: {
					boolExitWhile = true;
					// View travel only summary when "2" is entered.
					ViewTravelOnlySummary(hConsole, vecJourneyCollection, intWidth);
					break;
				}
				case 3: {
					boolExitWhile = true;
					// View travel and expenses summary when "3" is entered.
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
				OutputError(hConsole, exp.what());
			}
		}

	} while (intSummaryChoiceInput != 9);

	intSummaryChoiceInput = 0;
	boolExitWhile = false;
}

/// <summary>
/// Combined summary view. Displays a combined summary (summarises all journeys currently in system)
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewCombinedSummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	system("cls");

	// Output the header with the default description, output table showing both types of journeys.
	OutputHeader(hConsole, intWidth, "");
	if (vecJourneyCollection->size() > 0) {
		OutputTable(hConsole, vecJourneyCollection, intWidth, 3);
		OutputTable(hConsole, vecJourneyCollection, intWidth, 1);
	}

	// Output results showing the total of all the items in the summary.
	try {
		auto totals = CalculateAllSummaryTotals(vecJourneyCollection);
		OutputResults(hConsole, &totals, intWidth, "Totals");
	}
	catch (std::exception& exp) {
		OutputError(hConsole, exp.what());
	}

	// Output results showing the average of all the items in the summary
	try {
		auto average = CalculateAllSummaryAverage(vecJourneyCollection);
		OutputResults(hConsole, &average, intWidth, "Averages");
	}
	catch (std::exception& exp) {
		OutputError(hConsole, exp.what());
	}

	// Output results showing the largest of all the items in the summary
	try {
		auto largest = CalculateAllSummaryLargest(vecJourneyCollection);
		OutputResults(hConsole, &largest, intWidth, "Largest");
	}
	catch (std::exception& exp) {
		OutputError(hConsole, exp.what());
	}

	// Displays save options
	ViewSaveExport(hConsole, vecJourneyCollection, intWidth);
}

/// <summary>
/// Travel only summary view. Displays a summary of travel only journeys.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewTravelOnlySummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	// Store travel only journeys in vector
	std::vector<Journey> vecTravelOnlyCollection;
	
	system("cls");

	// Output header and table for travel only journeys
	OutputHeader(hConsole, intWidth, "Travel Only Journeys", 2);
	OutputTable(hConsole, vecJourneyCollection, intWidth, 2);

	// Output results showing total of all travel journeys in the summmary.
	try {
		auto totals = CalculateTravelSummaryTotals(vecJourneyCollection);
		OutputResults(hConsole, &totals, intWidth, "Totals");
	}
	catch (std::exception& exp) {
		OutputError(hConsole, exp.what());
	}

	// Output results showing average of all travel journeys in the summmary.
	try {
		auto average = CalculateTravelSummaryAverage(vecJourneyCollection);
		OutputResults(hConsole, &average, intWidth, "Averages");
	}
	catch (std::exception& exp) {
		OutputError(hConsole, exp.what());
	}

	// Output results showing largest of all travel journeys in the summmary.
	try {
		auto largest = CalculateTravelSummaryLargest(vecJourneyCollection);
		OutputResults(hConsole, &largest, intWidth, "Largest");
	}
	catch (std::exception& exp) {
		OutputError(hConsole, exp.what());
	}

	// Stores all travel only journeys into a list.
	for (size_t i = 0; i < vecJourneyCollection->size(); i++)
	{
		if (vecJourneyCollection->at(i).travelType == TravelType::Travel) {
			vecTravelOnlyCollection.push_back(vecJourneyCollection->at(i));
		}
	}

	// Displays save options - will only save travel journey types
	ViewSaveExport(hConsole, &vecTravelOnlyCollection, intWidth);
}

/// <summary>
/// Travel and expenses summary view. Displays a summary of travel and expense journeys.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewTravelExpensesOnlySummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	// Store all travel and expense journeys in vector
	std::vector<Journey> vecTravelExpenseOnlyCollection;
	
	system("cls");

	//Output header and table for travel and expense journeys
	OutputHeader(hConsole, intWidth, "Travel and Expense Journeys");
	OutputTable(hConsole, vecJourneyCollection, intWidth, 1);

	// Output results for total of all travel and expense journeys
	try {
		auto totals = CalculateTravelExpenseSummaryTotals(vecJourneyCollection);
		OutputResults(hConsole, &totals, intWidth, "Totals");
	}
	catch (std::exception& exp) {
		OutputError(hConsole, exp.what());
	}

	// Output results for average of all travel and expense journeys
	try {
		auto average = CalculateTravelExpenseSummaryAverage(vecJourneyCollection);
		OutputResults(hConsole, &average, intWidth, "Averages");
	}
	catch (std::exception& exp) {
		OutputError(hConsole, exp.what());
	}

	// Output results for largest of all travel and expense journeys
	try {
		auto largest = CalculateTravelExpenseSummaryLargest(vecJourneyCollection);
		OutputResults(hConsole, &largest, intWidth, "Largest");
	}
	catch (std::exception& exp) {
		OutputError(hConsole, exp.what());
	}

	// Stores all travel and expense journeys into list
	for (size_t i = 0; i < vecJourneyCollection->size(); i++)
	{
		if (vecJourneyCollection->at(i).travelType == TravelType::TravelAndExpense) {
			vecTravelExpenseOnlyCollection.push_back(vecJourneyCollection->at(i));
		}
	}

	// Displays save options - will only save travel and expense journeys 
	ViewSaveExport(hConsole, &vecTravelExpenseOnlyCollection, intWidth);
}

/// <summary>
/// Comparison menu view. Allows user to select type of comparison they would like to make.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewComparison(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	// Declare variables.
	int intComparisonChoiceInput = 0;
	bool boolExitWhile = false;

	// Loop until user enters "9"
	do {
		// Output menu options
		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "Compare two journeys", 2 });
		vecChoiceCollection.push_back(ChoiceOption{ 2, "Total two journeys", 2 });
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Return to menu" });
		OutputMenu(hConsole, vecJourneyCollection, &vecChoiceCollection, "Make Comparisons and total invoices.", true, true);

		// Loop until valid choice is made
		boolExitWhile = false;
		while (boolExitWhile == false) {
			// Validate input is an int
			SetConsoleTextAttribute(*hConsole, 9);
			std::cout << "Enter choice : ";
			SetConsoleTextAttribute(*hConsole, 15);
			intComparisonChoiceInput = ValidateIntInput(hConsole);

			// Execute function depending on choice made.
			try {
				switch (intComparisonChoiceInput) {
				case 1: {
					boolExitWhile = true;
					// Compare two journeys when "1" is entered.
					ViewCompareTwoJourneys(hConsole, vecJourneyCollection, intWidth);
					break;
				}
				case 2: {
					boolExitWhile = true;
					// Total two journeys when "2" is entered.
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
				OutputError(hConsole, exp.what());
			}
		}

	} while (intComparisonChoiceInput != 9);

	intComparisonChoiceInput = 0;
	boolExitWhile = false;
}

/// <summary>
/// Compare two journeys select view. Allows user to select two journeys to compare.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewCompareTwoJourneys(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	// Declare variables
	int intCompareFirst = 0, intCompareSecond = 0;
	std::vector<Journey> vecJourneyCompare;

	system("cls");
	// Output header and table for all items currently in main vector.
	OutputHeader(hConsole, intWidth, "", 1);
	OutputTable(hConsole, vecJourneyCollection, intWidth);

	std::cout << "\n";
	SetConsoleTextAttribute(*hConsole, 14);
	std::cout << "Please specify number of the first journey you would like to compare.\n";
	// Loop while comparision choice is not a valid item of the main vector.
	do {
		// Validate input is an int.
		SetConsoleTextAttribute(*hConsole, 9);
		std::cout << "Enter Choice : ";
		SetConsoleTextAttribute(*hConsole, 15);
		intCompareFirst = ValidateIntInput(hConsole) - 1;

		// Attempt to add specified selection to vector of journeys to compare. If input is not a valid item, error is displayed.
		try {
			vecJourneyCompare.push_back(vecJourneyCollection->at(intCompareFirst));
		}
		catch (std::out_of_range) {
			OutputError(hConsole, "The number you specified is not a valid item currently in the list.");
		}
	} while (!InRange(0, (int)vecJourneyCollection->size() - 1, intCompareFirst));

	std::cout << "\n";
	SetConsoleTextAttribute(*hConsole, 14);
	std::cout << "Please specify number of the second journey you would like to compare.\n";
	// Loop while second comparision choice is not a valid item of the main vector
	do {
		// Validate input is an int
		SetConsoleTextAttribute(*hConsole, 9);
		std::cout << "Enter Choice : ";
		SetConsoleTextAttribute(*hConsole, 15);
		intCompareSecond = (ValidateIntInput(hConsole) - 1);

		// Attempt to add specified selection to vector of journeys to compare. If input is not a valid item, error is displayed.
		try {
			// Throw error if second item to compare is the same as the first.
			if (intCompareSecond == intCompareFirst) {
				throw std::runtime_error("You cannot compare two of the same item.");
			}
			else {
				vecJourneyCompare.push_back(vecJourneyCollection->at(intCompareSecond));
			}
		}
		catch (std::out_of_range) {
			OutputError(hConsole, "The number you specified is not a valid item currently in the list.");
		}
		// Catch statement to print error when same item is added twice.
		catch (std::runtime_error& exp) {
			OutputError(hConsole, exp.what());
		}
	} while (!InRange(0, (int)vecJourneyCollection->size() - 1, intCompareSecond) || intCompareFirst == intCompareSecond);

	// Display comparison of the two items.
	ViewCompareSummaryTwoItems(hConsole, &vecJourneyCompare, intWidth);
}

/// <summary>
/// Total two journeys select view. Allows user to select two journeys to total.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewTotalTwoJourneys(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	// Declare variables
	int intTotalFirst = 0, intTotalSecond = 0;
	std::vector<Journey> vecJourneyTotal;

	system("cls");
	// Output header and table for all items currently in main vector.
	OutputHeader(hConsole, intWidth, "", 1);
	OutputTable(hConsole, vecJourneyCollection, intWidth);

	std::cout << "\n";
	SetConsoleTextAttribute(*hConsole, 14);
	std::cout << "Please specify number of the first journey you would like to total.\n";
	// Loop while comparision choice is not a valid item of the main vector.
	do {
		// Validate input is an int.
		SetConsoleTextAttribute(*hConsole, 9);
		std::cout << "Enter Choice : ";
		SetConsoleTextAttribute(*hConsole, 15);
		intTotalFirst = ValidateIntInput(hConsole) - 1;

		// Attempt to add specified selection to vector of journeys to compare. If input is not a valid item, error is displayed.
		try {
			vecJourneyTotal.push_back(vecJourneyCollection->at(intTotalFirst));
		}
		catch (std::out_of_range) {
			OutputError(hConsole, "The number you specified is not a valid item currently in the list.");
		}
	} while (!InRange(0, (int)vecJourneyCollection->size() - 1, intTotalFirst));

	std::cout << "\n";
	SetConsoleTextAttribute(*hConsole, 14);
	std::cout << "Please specify number of the second journey you would like to total.\n";
	// Loop while comparision choice is not a valid item of the main vector.
	do {
		// Validate input is an int.
		SetConsoleTextAttribute(*hConsole, 9);
		std::cout << "Enter Choice : ";
		SetConsoleTextAttribute(*hConsole, 15);
		intTotalSecond = (ValidateIntInput(hConsole) - 1);

		// Attempt to add specified selection to vector of journeys to compare. If input is not a valid item, error is displayed.
		try {
			// Throw error if second item to compare is the same as the first.
			if (intTotalSecond == intTotalFirst) {
				throw std::runtime_error("You cannot compare two of the same item.");
			}
			else {
				vecJourneyTotal.push_back(vecJourneyCollection->at(intTotalSecond));
			}
		}
		catch (std::out_of_range) {
			OutputError(hConsole, "The number you specified is not a valid item currently in the list.");
		}
		// Catch statement to print error when same item is added twice.
		catch (std::runtime_error& exp) {
			OutputError(hConsole, exp.what());
		}
	} while (!InRange(0, (int)vecJourneyCollection->size() - 1, intTotalSecond) || intTotalFirst == intTotalSecond);

	ViewTotalSummaryTwoItems(hConsole, &vecJourneyTotal, intWidth);
}

/// <summary>
/// Compare two items summary view. Displays comparison of two journeys
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewCompareSummaryTwoItems(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	system("cls");

	// Outputs header and table for the two journeys to compare.
	OutputHeader(hConsole, intWidth, "Two Journeys : Comparison", 1);
	if (vecJourneyCollection->size() > 0) {
		OutputTable(hConsole, vecJourneyCollection, intWidth);
	}

	// Ouputs results showing the combined total of the two items being compared
	try {
		auto totals = CalculateAllSummaryTotals(vecJourneyCollection);
		OutputResults(hConsole, &totals, intWidth, "Totals", true);
	}
	catch (std::exception& exp) {
		OutputError(hConsole, exp.what());
	}

	// Oupputs results showing the larget value of hte two items being compared.
	try {
		auto largest = CalculateAllSummaryLargest(vecJourneyCollection);
		OutputResults(hConsole, &largest, intWidth, "Largest", true);
	}
	catch (std::exception& exp) {
		OutputError(hConsole, exp.what());
	}

	// Outputs results showing the difference of the two items being compared.
	try {
		auto difference = CalculateTwoItemComparison(vecJourneyCollection);
		OutputResults(hConsole, &difference, intWidth, "Difference", true);
	}
	catch (std::exception& exp) {
		OutputError(hConsole, exp.what());
	}

	// Displays save options
	ViewSaveExport(hConsole, vecJourneyCollection, intWidth);
}

/// <summary>
/// Total two items summary view. Displays total of two journeys
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewTotalSummaryTwoItems(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	system("cls");

	// Outputs header and table the two items to total.
	OutputHeader(hConsole, intWidth, "Two Journeys : Totals", 1);
	if (vecJourneyCollection->size() > 0) {
		OutputTable(hConsole, vecJourneyCollection, intWidth);
	}

	// Displays total of the two journeys.
	try {
		auto totals = CalculateAllSummaryTotals(vecJourneyCollection);
		OutputResults(hConsole, &totals, intWidth, "Totals", true);
	}
	catch (std::exception& exp) {
		OutputError(hConsole, exp.what());
	}

	// Displays save options
	ViewSaveExport(hConsole, vecJourneyCollection, intWidth);
}

/// <summary>
/// Delete journey view. Allows user to delete a journey from the main journey vector.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewDeleteJourney(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intJourneyToDelete = 0;
	bool boolIsValid = false;
	bool boolIsExiting = false;

	system("cls");
	// Output header and table for all current journeys, with numeric numbering.
	OutputHeader(hConsole, intWidth, "", 1);
	OutputTable(hConsole, vecJourneyCollection, intWidth);

	std::cout << "\n";
	SetConsoleTextAttribute(*hConsole, 14);
	std::cout << "Please specify number of the journey you would like to remove. Type '0' to cancel. \n";
	SetConsoleTextAttribute(*hConsole, 15);

	// Loop until valid item to delete is enteered.
	while (boolIsValid == false) {
		// Validate that input is an int.
		SetConsoleTextAttribute(*hConsole, 9);
		std::cout << "Enter Choice : ";
		SetConsoleTextAttribute(*hConsole, 15);
		intJourneyToDelete = ValidateIntInput(hConsole) - 1;

		// If "0" is entered; user intends to exit. Exit loop and skip delete.
		if (intJourneyToDelete == -1) {
			boolIsValid = true;
			boolIsExiting = true;
		}
		// If number is valid item in vector, exit loop.
		else if (InRange(0, (int)vecJourneyCollection->size() - 1, intJourneyToDelete)) {
			boolIsValid = true;
		}
		else {
			OutputError(hConsole, "The number you specified is not a valid item currently in the list.");
		}
	}

	// If not exiting.
	if (!boolIsExiting) {
		// Try to delete journey from vector.
		try {
			vecJourneyCollection->erase(vecJourneyCollection->begin() + intJourneyToDelete);

			std::cout << "\n";
			SetConsoleTextAttribute(*hConsole, 10);
			std::cout << "Journey " << (intJourneyToDelete + 1) << " successfully removed.\n";
			SetConsoleTextAttribute(*hConsole, 15);
		}
		catch (std::exception) {
			OutputError(hConsole, "Sorry, something went wrong while removing this item.");
		}

		Pause(hConsole);
	}
}

/// <summary>
/// Save and import select view. Allows uesr to choose to save, import or view journeys.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewSaveImportSelect(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	// Declare variables.
	int intSaveImportChoiceInput = 0;
	bool boolExitWhile = false;

	do {
		// Output menu options
		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "Export current Journeys" });
		vecChoiceCollection.push_back(ChoiceOption{ 2, "Import Journeys from CSV" });
		vecChoiceCollection.push_back(ChoiceOption{ 3, "View current journeys" });
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Return to previous" });
		OutputMenu(hConsole, vecJourneyCollection, &vecChoiceCollection, "Import or export journeys.", true, true);

		// Loop until "9" entered.
		boolExitWhile = false;
		while (boolExitWhile == false) {
			// Validate input is an int.
			SetConsoleTextAttribute(*hConsole, 9);
			std::cout << "Enter choice : ";
			SetConsoleTextAttribute(*hConsole, 15);
			intSaveImportChoiceInput = ValidateIntInput(hConsole);

			try {
				switch (intSaveImportChoiceInput) {
				case 1: {
					boolExitWhile = true;
					// Run view save summary when "1" entered.
					ViewSaveSummary(hConsole, vecJourneyCollection);
					break;
				}
				case 2: {
					boolExitWhile = true;
					// Run view import summary when "2" entered.
					ViewImportSummary(hConsole, vecJourneyCollection, intWidth);
					break;
				}
				case 3: {
					boolExitWhile = true;
					// Run view journeys when "3" entered.
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
				OutputError(hConsole, exp.what());
			}
		}

	} while (intSaveImportChoiceInput != 9);

	intSaveImportChoiceInput = 0;
	boolExitWhile = false;
}

/// <summary>
/// Save/Export menu view. Printed in particular places where saving/exporting needs to be only option. Importing and Saving handled in seperate Views.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void ViewSaveExport(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	// Declare variables
	int intSaveExportChoiceInput = 0;
	bool boolExitWhile = false;

	// Loop until "9" is entered.
	do {
		// Output menu choices.
		std::vector<ChoiceOption> vecChoiceCollection;
		vecChoiceCollection.push_back(ChoiceOption{ 1, "Export list as CSV" });
		vecChoiceCollection.push_back(ChoiceOption{ 9, "Return to previous" });
		OutputMenu(hConsole, vecJourneyCollection, &vecChoiceCollection, "Make Comparisons and total invoices.", false, false);

		// Loop until valid choice number is made. Execute function depending on number entered.
		boolExitWhile = false;
		while (boolExitWhile == false) {
			// Validate input is an int.
			SetConsoleTextAttribute(*hConsole, 9);
			std::cout << "Enter choice : ";
			SetConsoleTextAttribute(*hConsole, 15);
			intSaveExportChoiceInput = ValidateIntInput(hConsole);

			try {
				switch (intSaveExportChoiceInput) {
				case 1: {
					// View save summary when "1" is entered.
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
				OutputError(hConsole, exp.what());
			}
		}

	} while (intSaveExportChoiceInput != 9);

	intSaveExportChoiceInput = 0;
	boolExitWhile = false;
}

/// <summary>
/// Import summary view. Allows user to import journeys from a .csv file.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
void ViewImportSummary(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	// Declare variables.
	std::vector<Journey> vecJourneyTemp;
	std::string strFilename = "";
	std::fstream fin;
	bool boolExitLoop = false;
	bool boolHasReadFile = false;

	system("cls");
	SetConsoleTextAttribute(*hConsole, 14);
	std::cout << "Please specify the name of the file you would like to import below.\n";
	std::cout << "Note : Please enter the full file name, such as '";
	SetConsoleTextAttribute(*hConsole, 13);
	std::cout << "journeyList.csv";
	SetConsoleTextAttribute(*hConsole, 14);
	std::cout << "', otherwise the file will not be found.The file must also be in the same directory that you are running this program from.Type 'exit' if you would like to canceland return to the previous screen.\n";
	SetConsoleTextAttribute(*hConsole, 15);
	std::cout << "\n";

	// Loop until file is successfully read, or user specifies "exit"
	do {
		try {
			SetConsoleTextAttribute(*hConsole, 9);
			std::cout << "File name : ";
			SetConsoleTextAttribute(*hConsole, 15);
			std::cin >> strFilename;

			fin.open(strFilename, std::ios::in);

			// If exit is specified, exit loop and ensure HasFileRead is false.
			if (strFilename == "exit") {
				boolExitLoop = true;
				boolHasReadFile = false;
			}
			else {
				// If the file exists, exit loop and set HasFileRead to true.
				if (FileExists(strFilename)) {
					SetConsoleTextAttribute(*hConsole, 10);
					std::cout << "File exists...\n";
					SetConsoleTextAttribute(*hConsole, 15);
					boolExitLoop = true;
					boolHasReadFile = true;
				}
				// Otherwise continue looping until "exit" is specified or valid filename is provided.
				else {
					OutputError(hConsole, "File could not be found. Please ensure you are specifying the file name correctly.", true);
					boolHasReadFile = false;
				}
			}
		}
		catch (std::exception& exp) {
			OutputError(hConsole, exp.what(), true);
		}
	} while (boolExitLoop == false);

	// If a file has be read into file stream
	if (boolHasReadFile) {
		// Declare variables
		std::vector<std::string> vecRowTemp;
		std::string strLine, strWord, strTemp;

		// Try reading file.
		try {
			SetConsoleTextAttribute(*hConsole, 10);
			std::cout << "Attempting to read file...\n";
			SetConsoleTextAttribute(*hConsole, 15);
			// If not end of file.
			while (!fin.eof()) {
				vecRowTemp.clear();

				std::getline(fin, strLine);

				std::stringstream s(strLine);

				// Split read line into seperate items. Split on comma.
				while (std::getline(s, strWord, ',')) {
					vecRowTemp.push_back(strWord);
				}

				// If items were read from line.
				if (!vecRowTemp.empty()) {
					// If first item is not "Travel Type" (makes sure that header is not read in)
					if (vecRowTemp.at(0) != "Travel Type") {
						// Create a journey and set appropraite values from the vector of items read from line.
						Journey journeyTemp{ TravelType::Travel, 0 };
						journeyTemp.travelType = (((vecRowTemp.at(0)) == "Travel") ? TravelType::Travel : TravelType::TravelAndExpense);
						journeyTemp.travelCost = std::stod(vecRowTemp.at(1));
						journeyTemp.expenseCost = std::stod(vecRowTemp.at(2));
						journeyTemp.totalCost = std::stod(vecRowTemp.at(3));
						journeyTemp.taxReclaim = std::stod(vecRowTemp.at(4));
						journeyTemp.expensePayable = std::stod(vecRowTemp.at(5));
						journeyTemp.finalPayment = std::stod(vecRowTemp.at(6));
						journeyTemp.expenseNotCovered = std::stod(vecRowTemp.at(7));

						// Store journey in main collection, and in temp collection in order to display to user.
						vecJourneyCollection->push_back(journeyTemp);
						vecJourneyTemp.push_back(journeyTemp);
					}
				}
			}

			// Display header and table showing journeys that were imported.
			std::cout << "\n";
			OutputHeader(hConsole, intWidth, "The following journeys were successfully imported", 1);
			OutputTable(hConsole, &vecJourneyTemp, intWidth);
		}
		catch (std::exception& exp) {
			// If file could not be imported, output error
			std::string strErrorText = "Sorry, but the file could not be imported. This is likely because the file is not formatted correctly.\nException Generated : ";
			strErrorText += exp.what();
			OutputError(hConsole, strErrorText, true);
		}

		Pause(hConsole);
	}
}

// Views/Menu screens end

// Test functions

/// <summary>
/// Testing function. Adds 4 pre-made journeys to vector to speed up process of testing when debugging application.
/// </summary>
/// <param name="vecJourneyCollection"></param>
void TestFunction(std::vector<Journey>* vecJourneyCollection) {
	// Testing function, adds some example journeys with large decimal point inputs.

	vecJourneyCollection->push_back(Journey{ TravelType::Travel, 25.23534 });
	vecJourneyCollection->push_back(Journey{ TravelType::TravelAndExpense, 23.23, 10.9263 });
	vecJourneyCollection->push_back(Journey{ TravelType::Travel, 27 });
	vecJourneyCollection->push_back(Journey{ TravelType::TravelAndExpense, 120.2553, 57.823 });
}

// Test functions end

// Functions end