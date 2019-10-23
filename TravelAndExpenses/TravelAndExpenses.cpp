// TravelAndExpenses.cpp : The main application file for the travel and expenses console app.

#include <iostream>
#include <string>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <vector>
#include <iomanip>
#include <conio.h>
#include <algorithm>

enum class TravelType
{
	Travel,
	TravelAndExpense
};

struct Journey {
	// Struct variables
	TravelType travelType;
	double travelCost;
	double expenseCost;
	double totalCost;
	double taxReclaim;
	double expensePayable;
	double finalPayment;
	double expenseNotCovered;

	// Constructor for travel only
	Journey(TravelType passTravelType, double passCost)
	{
		travelType = passTravelType;
		travelCost = passCost;
		totalCost = travelCost;
		expenseCost = 0;
		expensePayable = 0;
		expenseNotCovered = 0;
		taxReclaim = totalCost * 0.2;
		finalPayment = travelCost;
	}
	// Constructor used when there is travel and expenses
	Journey(TravelType passTravelType, double passTravelCost, double passExpenseCost) {
		travelType = passTravelType;
		travelCost = passTravelCost;
		expenseCost = passExpenseCost;
		totalCost = travelCost + expenseCost;
		taxReclaim = totalCost * 0.2;
		if (expenseCost >= 50) {
			expensePayable = 50;
			expenseNotCovered = expenseCost - 50;
		}
		else {
			expensePayable = expenseCost;
			expenseNotCovered = 0;
		}
		finalPayment = expensePayable + travelCost;
	}


};

// Global Variables

std::vector<Journey> vecJourneyCollection;
const int intWidth = 15;

// Global Variables end

// Function namespace declaration

// Ouput print help functions.
void PrintIntro();
void PrintTravelHeader();
void PrintTravelExpenseHeader();
void PrintCurrentJourneysTravel();
void PrintCurrentJourneysTravelExpense();
void PrintAddJourneyScreen();
void PrintMainMenuScreen();
void PrintSummaryScreen();

// Misc helper functions
void Pause();
void TestingFunction();
int ValidateChoiceInput();

void TestFunction(std::vector<Journey> *vecJourneyCollectionPass);

// Menu action functinons
void AddNewJourney();
void ViewJourneys();
void ViewSummary();

//Function namespace declaration end

int main()
{
	std::vector<Journey> vecJourneyCollection2;
	TestFunction(&vecJourneyCollection2);

	PrintIntro();

	int intMenuMainChoice = 0;
	bool boolExitWhile = false;

	TestingFunction();

	do {
		PrintMainMenuScreen();

		while (boolExitWhile == false) {
			std::cout << "Enter choice : ";
			intMenuMainChoice = ValidateChoiceInput();

			try {
				switch (intMenuMainChoice)
				{
				case 1: {
					AddNewJourney();
					boolExitWhile = true;
					intMenuMainChoice = 0;
					break;
				}
				case 2: {
					if (vecJourneyCollection.size() <= 0) {
						boolExitWhile = false;
						intMenuMainChoice = 0;
						throw std::runtime_error("You have not yet added any journeys, this menu option is not available yet.");
						break;
					}
					else {
						ViewJourneys();
						boolExitWhile = true;
						intMenuMainChoice = 0;
					}
					break;
				}
				case 3: {
					if (vecJourneyCollection.size() <= 0) {
						boolExitWhile = false;
						intMenuMainChoice = 0;
						throw std::runtime_error("You have not yet added any journeys, this menu option is not available yet.");
						break;
					}
					else {
						ViewSummary();
						boolExitWhile = true;
						intMenuMainChoice = 0;
					}
					break;
				}
				case 9: {
					boolExitWhile = true;
					system("exit");
					break;
				}
				default:
					boolExitWhile = false;
					intMenuMainChoice = 0;
					throw std::runtime_error("Input not recongised as a valid option.");
					break;
				}
			}
			catch (std::exception & exp) {
				std::cout << "Error : " << exp.what() << "\n";
				boolExitWhile = false;
				intMenuMainChoice = 0;
			}

		}

		boolExitWhile = false;

	} while (intMenuMainChoice != 9);

	return 0;
}

// Functions

void AddNewJourney() {
	std::string strContinueAddingJourneys;
	bool boolExitWhile = false;

	int intTravelChoiceInput;
	TravelType travelTypeChoice;

	double dTravelCost = 0;
	double dExpenseCost = 0;

	do {
		PrintAddJourneyScreen();

		while (boolExitWhile != true) {
			std::cout << "Enter choice  : ";

			while (!(std::cin >> intTravelChoiceInput)) {
				// Makes user try again if input is not an int
				std::cout << "ERROR: a whole number must be entered : ";
				std::cin.clear();
				std::cin.ignore(123, '\n');
			}

			try {
				if (intTravelChoiceInput == 1) {
					travelTypeChoice = TravelType::Travel;
					std::cout << "Travel cost : ";

					while (!(std::cin >> dTravelCost)) {
						// Makes user try again if input is not an int
						std::cout << "ERROR: a number must be entered : ";
						std::cin.clear();
						std::cin.ignore(123, '\n');
					}

					Journey newJourney{ travelTypeChoice, dTravelCost };
					vecJourneyCollection.push_back(newJourney);
					boolExitWhile = true;
				}
				else if (intTravelChoiceInput == 2) {
					travelTypeChoice = TravelType::TravelAndExpense;
					std::cout << "Travel cost : ";

					while (!(std::cin >> dTravelCost)) {
						// Makes user try again if input is not an int
						std::cout << "ERROR: a number must be entered : ";
						std::cin.clear();
						std::cin.ignore(123, '\n');
					}

					std::cout << "Expenses cost : ";

					while (!(std::cin >> dExpenseCost)) {
						// Makes user try again if input is not an int
						std::cout << "ERROR: a number must be entered : ";
						std::cin.clear();
						std::cin.ignore(123, '\n');
					}

					Journey newJourney{ travelTypeChoice, dTravelCost, dExpenseCost };
					vecJourneyCollection.push_back(newJourney);
					boolExitWhile = true;
				}
				else if (intTravelChoiceInput == 3) {
					if (vecJourneyCollection.size() <= 0) {
						throw std::runtime_error("This option is not yet a valid option, there are no stored journeys.");
						boolExitWhile = false;
					}
					else {
						ViewJourneys();
						boolExitWhile = true;
					}
				}
				else if (intTravelChoiceInput == 4) {
					boolExitWhile = true;
				}
				else {
					throw std::runtime_error("This is not a valid choice. Please try again");
					boolExitWhile = false;
				}
			}
			catch (std::exception & exp) {
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
		case 4: {
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

void ViewJourneys() {
	system("CLS");
	PrintTravelHeader();
	PrintCurrentJourneysTravel();

	PrintTravelExpenseHeader();
	PrintCurrentJourneysTravelExpense();
	Pause();
}

void ViewSummary() {
	int intSummaryChoiceInput = 0;
	bool boolExitWhile = false;

	do {
		PrintSummaryScreen();

		while (boolExitWhile == false) {
			std::cout << "Enter choice : ";
			intSummaryChoiceInput = ValidateChoiceInput();

			// TODO : Implement functionality that allows summaries of items
			try {
				switch (intSummaryChoiceInput) {
					case 1: {
						boolExitWhile = true;
						break;
					}
					case 2: {
						boolExitWhile = true;
						break;
					} 
					case 3: {
						boolExitWhile = true;
						break;
					} 
					case 4: {
						boolExitWhile = true;
						break;
					}
					case 5: {
						boolExitWhile = true;
						break;
					}
					default: {
						throw std::exception("Not recognised as valid input.");
						break;
					}
				}

			}
			catch (std::exception & exp) {
				std::cout << "Error : " << exp.what() << "\n";
			}
		}

	} while (intSummaryChoiceInput != 5);

	intSummaryChoiceInput = 0;
	boolExitWhile = false;

}

void PrintTravelHeader() {
	std::cout << "Travel Only Journeys" << "\n";
	std::cout << "------------------------------------------------------------\n";
	std::cout << std::setw(intWidth) << "Travel Type" << std::setw(intWidth) << "Travel Cost" << std::setw(intWidth) << "Tax Reclaim" << std::setw(intWidth) << "Final Pay" << "\n";
	std::cout << "------------------------------------------------------------\n";
}

void PrintTravelExpenseHeader() {
	std::cout << "Travel and Expenses Journeys" << "\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << std::setw(intWidth) << "Travel Type" << std::setw(intWidth) << "Travel Cost" << std::setw(intWidth) << "Exp Cost" << std::setw(intWidth) << "Total Cost" << std::setw(intWidth) << "Exp Payable" << std::setw(intWidth) << "Tax Reclaim" << std::setw(intWidth) << "Exp not Cvrd" << std::setw(intWidth) << "Final Pay\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
}

void PrintCurrentJourneysTravel() {
	if (vecJourneyCollection.size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
	}
	else {
		for (int i = 0; i < (int)vecJourneyCollection.size(); ++i) {
			if (vecJourneyCollection[i].travelType == TravelType::Travel) {
				std::cout.precision(2);
				std::cout
					<< std::setw(intWidth) << ((((int)vecJourneyCollection[i].travelType) == 0) ? "Travel" : "Travel & Exp")
					<< std::setw(intWidth) << std::fixed << vecJourneyCollection[i].totalCost
					<< std::setw(intWidth) << std::fixed << vecJourneyCollection[i].taxReclaim
					<< std::setw(intWidth) << std::fixed << vecJourneyCollection[i].finalPayment << "\n";
			}
		}
		std::cout << "\n";
	}

}

void PrintCurrentJourneysTravelExpense() {
	if (vecJourneyCollection.size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
	}
	else {
		for (int i = 0; i < (int)vecJourneyCollection.size(); ++i) {
			if (vecJourneyCollection[i].travelType == TravelType::TravelAndExpense) {
				std::cout.precision(2);
				std::cout
					<< std::setw(intWidth) << ((((int)vecJourneyCollection[i].travelType) == 0) ? "Travel" : "Travel & Exp")
					<< std::fixed << std::setw(intWidth) << vecJourneyCollection[i].travelCost
					<< std::fixed << std::setw(intWidth) << vecJourneyCollection[i].expenseCost
					<< std::fixed << std::setw(intWidth) << vecJourneyCollection[i].totalCost
					<< std::fixed << std::setw(intWidth) << vecJourneyCollection[i].expensePayable
					<< std::fixed << std::setw(intWidth) << vecJourneyCollection[i].taxReclaim
					<< std::fixed << std::setw(intWidth) << vecJourneyCollection[i].expenseNotCovered
					<< std::fixed << std::setw(intWidth) << vecJourneyCollection[i].finalPayment << "\n";
			}
		}
		std::cout << "\n";
	}

}

void PrintIntro() {
	// Notice for users about setup needed to ensure proper formatted output.
	std::cout << "Notice: To ensure proper text formatting while in use, please make sure you right click on the console window header, \n";
	std::cout << "then go to defaults and disable the 'Wrap text output on resize' option. Without doing this, text will end up sat on the\n";
	std::cout << "same line ruining some of the output tables.\n";

	Pause();
}

void PrintMainMenuScreen() {
	system("cls");
	std::cout << "-------------------------------------------\n";
	std::cout << "\n";
	std::cout << "Welcome to the travel and expeses system.\n";
	std::cout << "Please specify your option:\n";
	std::cout << "\n";
	std::cout << "Option 1: Enter a new Journey\n";
	if (vecJourneyCollection.size() > 0) {
		std::cout << "Option 2: View current journeys\n";
	}
	if (vecJourneyCollection.size() > 0) {
		std::cout << "Option 3: Summaries\n";
	}
	std::cout << "Option 9: Exit\n";
	std::cout << "\n";
	std::cout << "-------------------------------------------\n";
	std::cout << "\n";
}

void PrintAddJourneyScreen() {
	system("cls");
	std::cout << "-------------------------------------------\n";
	std::cout << "\n";
	std::cout << "Add new journey screen\n";
	std::cout << "Please specify your option:\n";
	std::cout << "\n";
	std::cout << "Option 1 : Travel only\n";
	std::cout << "Option 2 : Travel and expenses\n";
	if (vecJourneyCollection.size() > 0) {
		std::cout << "Option 3 : View current journeys\n";
	}
	std::cout << "Option 4 : Return to menu\n";
	std::cout << "\n";
	std::cout << "-------------------------------------------\n";
	std::cout << "\n";
}

void PrintSummaryScreen() {
	system("cls");
	std::cout << "-------------------------------------------\n";
	std::cout << "\n";
	std::cout << "View and interact with summary.\n";
	std::cout << "Please specify your option:\n";
	std::cout << "\n";
	std::cout << "Option 1 : View Combined Summary\n";
	std::cout << "Option 2 : View Travel only Summary\n";
	std::cout << "Option 3 : View Travel and Expenses only Summary\n";
	std::cout << "Option 4 : Export Summary to file\n";
	std::cout << "Option 5 : Return to menu\n";
	std::cout << "\n";
	std::cout << "-------------------------------------------\n";
	std::cout << "\n";
}

int ValidateChoiceInput() {
	int ChoiceValue;
	while (!(std::cin >> ChoiceValue)) {
		// Makes user try again if input is not an int
		std::cout << "ERROR: a whole number must be entered : ";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}

	return ChoiceValue;
}

void Pause()
{
	std::cout << "\n";
	std::cout << "Press any key to continue...";
	_getch();
}

void TestingFunction() {
	// Testing function, adds some example journeys with large decimal point inputs.

	Journey journey1{ TravelType::Travel, 25.23534 };
	Journey journey2{ TravelType::TravelAndExpense, 23.23, 10.9263 };
	Journey journey3{ TravelType::Travel, 27 };
	Journey journey4{ TravelType::TravelAndExpense, 120.2553, 57.823 };

	vecJourneyCollection.push_back(journey1);
	vecJourneyCollection.push_back(journey2);
	vecJourneyCollection.push_back(journey3);
	vecJourneyCollection.push_back(journey4);
}

// Experiemnt with passing by reference, needs implementing!
void TestFunction(std::vector<Journey>* vecJourneyCollectionPass) {
	double tempVar;
	Journey tempJourney{ TravelType::TravelAndExpense, 25, 50 };
	vecJourneyCollectionPass->push_back(tempJourney);
	tempVar = vecJourneyCollectionPass->at(0).expenseCost;
	std::cout << "Temp var is : " << tempVar;
	Pause();
}

// Functions end