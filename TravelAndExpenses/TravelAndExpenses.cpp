// TravelAndExpenses.cpp : The main application file for the travel and expenses console app.

#include <iostream>
#include <string>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <vector>
#include <iomanip>
#include <map>
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
void PrintTravelHeader();
void PrintTravelExpenseHeader();
void PrintCurrentJourneysTravel();
void PrintCurrentJourneysTravelExpense();

// Misc helper functions
void Pause();

// Menu action functinons
void AddNewJourney();
void ViewJourneys();

//Function namespace declaration end

int main()
{
	// Notice for users about setup needed to ensure proper formatted output.
	std::cout << "Notice: To ensure proper text formatting while in use, please make sure you right click on the console window header, \n";
	std::cout << "then go to defaults and disable the 'Wrap text output on resize' option. Without doing this, text will end up sat on the\n";
	std::cout << "same line ruining some of the output tables.\n";

	Pause();

	int intMenuMainChoice = 0;

	do {
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
		std::cout << "Option 9: Exit\n";
		std::cout << "\n";
		std::cout << "-------------------------------------------\n";
		std::cout << "\n";
		std::cout << "Enter number : ";

		while (!(std::cin >> intMenuMainChoice)) {
			// Makes user try again if input is not an int
			std::cout << "ERROR: a whole number must be entered : ";
			std::cin.clear();
			std::cin.ignore(123, '\n');
		}

		switch (intMenuMainChoice)
		{
		case 1: {
			AddNewJourney();
			break;
		}
		case 2: {
			if (vecJourneyCollection.size() <= 0) {
				std::cout << "You have not yet added any journeys, this menu option is not available yet, and will be unhidden once at least 1 journey has been added.\n";
				Pause();
				break;
			}
			else {
				ViewJourneys();
			}
			break;
		}
		case 9: {
			system("exit");
			break;
		}
		default:
			std::cout << "Input not recongised as a valid option.\n";
			Pause();
			break;
		}
	} while (intMenuMainChoice != 9);

	// Testing function for future use, adds some examples.

	/*Journey journey1{ TravelType::Travel, 25.23534 };
	Journey journey2{ TravelType::TravelAndExpense, 23.23, 10.9263 };
	Journey journey3{ TravelType::Travel, 27 };
	Journey journey4{ TravelType::TravelAndExpense, 120.2553, 57.823 };

	vecJourneyCollection.push_back(journey1);
	vecJourneyCollection.push_back(journey2);
	vecJourneyCollection.push_back(journey3);
	vecJourneyCollection.push_back(journey4);

	PrintTravelHeader();
	PrintCurrentJourneysTravel();

	PrintTravelExpenseHeader();
	PrintCurrentJourneysTravelExpense();*/

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
		system("cls");
		std::cout << "-------------------------------------------\n";
		std::cout << "\n";
		std::cout << "Add new journey screen\n";
		std::cout << "Please specify your option:\n";
		std::cout << "\n";
		std::cout << "Option 1 : Travel only\n";
		std::cout << "Option 2 : Travel and expenses\n";
		std::cout << "\n";
		std::cout << "-------------------------------------------\n";
		std::cout << "\n";

		while (boolExitWhile != true) {
			std::cout << "Enter number  : ";

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
		
		system("CLS");
		std::cout << "Journey succesfully added.\n";
		std::cout << "Would you like to add another journey?\n";
		std::cout << "Type 'yes' to add another, Any other input will return you to menu\n";

		while (!(std::cin >> strContinueAddingJourneys)) {
			// Makes user try again if input is not an int
			std::cout << "ERROR: a string must be entered : ";
			std::cin.clear();
			std::cin.ignore(123, '\n');
		}

		transform(strContinueAddingJourneys.begin(), strContinueAddingJourneys.end(), strContinueAddingJourneys.begin(), ::tolower);

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

void Pause()
{
	std::cout << "\n";
	std::cout << "Press any key to continue...";
	_getch();
}

// Functions end