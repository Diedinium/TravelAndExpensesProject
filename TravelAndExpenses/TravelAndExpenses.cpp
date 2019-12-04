// TravelAndExpenses.cpp : The main application file for the travel and expenses console app.
// Please note: This file has XML style comments to enable intellisense, this is not a standard feature of C++! You will need an extension called "CppTripleSlash - xml doc comments for c++"
// installed in order for this functionality to work, this not being installed does not affect functionality, it simply results in less descriptive function descriptions.

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

// Function namespace declaration

// Ouput print help functions.
void PrintIntro();
void PrintTravelHeader(int* intWidth);
void PrintTravelExpenseHeader(int* intWidth);
void PrintCurrentJourneysTravel(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void PrintCurrentJourneysTravelExpense(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void PrintAddJourneyScreen(std::vector<Journey>* vecJourneyCollection);
void PrintMainMenuScreen(std::vector<Journey>* vecJourneyCollection);
void PrintSummaryScreen();
void PrintSummaryHeader(int* intWidth);
void PrintComparisonScreen();


// Misc helper functions
void Pause();
int ValidateIntInput();
double ValidateDoubleInput();
auto CalculateAllSummaryTotals(std::vector<Journey>* vecJourneyCollection);
auto CalculateTravelSummaryTotals(std::vector<Journey>* vecJourneyCollection);
auto CalculateTravelExpenseSummaryTotals(std::vector<Journey>* vecJourneyCollection);
auto CalculateAllSummaryAverage(std::vector<Journey>* vecJourneyCollection);
auto CalculateTravelSummaryAverage(std::vector<Journey>* vecJourneyCollection);
auto CalculateTravelExpenseSummaryAverage(std::vector<Journey>* vecJourneyCollection);
auto CalculateAllSummaryLargest(std::vector<Journey>* vecJourneyCollection);
auto CalculateTravelSummaryLargest(std::vector<Journey>* vecJourneyCollection);
auto CalculateTravelExpenseSummaryLargest(std::vector<Journey>* vecJourneyCollection);

// Testing function : Automatically adds some journeys to save time when testing.
void TestFunction(std::vector<Journey>* vecJourneyCollection);

// Menu action functinons
void AddNewJourney(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewJourneys(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewSummary(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewCombinedSummary(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewTravelOnlySummary(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewTravelExpensesOnlySummary(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewSaveSummary(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewComparison(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewCompareTwoJourneys(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewTotalTwoJourneys(std::vector<Journey>* vecJourneyCollection, int* intWidth);

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
		PrintMainMenuScreen(&vecJourneyCollection);

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
					if (vecJourneyCollection.size() <= 0) {
						boolExitWhile = false;
						throw std::runtime_error("You have not yet added any journeys, this menu option is not available yet.");
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
			catch (std::exception & exp) {
				std::cout << "Error : " << exp.what() << "\n";
				boolExitWhile = false;
			}

		}

		boolExitWhile = false;

	} while (intMenuMainChoice != 9);

	return 0;
}

// Functions

// Calculation Functions
auto CalculateAllSummaryTotals(std::vector<Journey>* vecJourneyCollection) {
	struct result { double TotalTravel; double TotalExpense; double TotalOfTotals; double TotalExpensePay; double TotalTaxReclaim; double ExpenseNotCovered; double TotalFinalPay; };
	result SummaryTotals = result();
	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			SummaryTotals.TotalTravel += vecJourneyCollection->at(i).travelCost;
			SummaryTotals.TotalExpense += vecJourneyCollection->at(i).expenseCost;
			SummaryTotals.TotalOfTotals += vecJourneyCollection->at(i).totalCost;
			SummaryTotals.TotalExpensePay += vecJourneyCollection->at(i).expensePayable;
			SummaryTotals.TotalTaxReclaim += vecJourneyCollection->at(i).taxReclaim;
			SummaryTotals.ExpenseNotCovered += vecJourneyCollection->at(i).expenseNotCovered;
			SummaryTotals.TotalFinalPay += vecJourneyCollection->at(i).finalPayment;
		}
		return SummaryTotals;
	}

}

auto CalculateTravelSummaryTotals(std::vector<Journey>* vecJourneyCollection) {
	struct result { double TotalTravel; double TotalTaxReclaim; double TotalFinalPay; };
	result SummaryTotals = result();
	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			if (vecJourneyCollection->at(i).travelType == TravelType::Travel) {
				SummaryTotals.TotalTravel += vecJourneyCollection->at(i).travelCost;
				SummaryTotals.TotalTaxReclaim += vecJourneyCollection->at(i).taxReclaim;
				SummaryTotals.TotalFinalPay += vecJourneyCollection->at(i).finalPayment;
			}
		}
		return SummaryTotals;
	}
}

auto CalculateTravelExpenseSummaryTotals(std::vector<Journey>* vecJourneyCollection) {
	struct result { double TotalTravel; double TotalExpense; double TotalOfTotals; double TotalExpensePay; double TotalTaxReclaim; double ExpenseNotCovered; double TotalFinalPay; };
	result SummaryTotals = result();
	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			if (vecJourneyCollection->at(i).travelType == TravelType::TravelAndExpense) {
				SummaryTotals.TotalTravel += vecJourneyCollection->at(i).travelCost;
				SummaryTotals.TotalExpense += vecJourneyCollection->at(i).expenseCost;
				SummaryTotals.TotalOfTotals += vecJourneyCollection->at(i).totalCost;
				SummaryTotals.TotalExpensePay += vecJourneyCollection->at(i).expensePayable;
				SummaryTotals.TotalTaxReclaim += vecJourneyCollection->at(i).taxReclaim;
				SummaryTotals.ExpenseNotCovered += vecJourneyCollection->at(i).expenseNotCovered;
				SummaryTotals.TotalFinalPay += vecJourneyCollection->at(i).finalPayment;
			}

		}
		return SummaryTotals;
	}
}

auto CalculateAllSummaryAverage(std::vector<Journey>* vecJourneyCollection) {
	struct result { double AverageTravel; double AverageExpense; double AverageOfTotals; double AverageExpensePay; double AverageTaxReclaim; double AverageNotCovered; double AverageFinalPay; };
	result SummaryTotals = result();
	std::size_t NumOfRecords = 0;
	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			NumOfRecords++;
		}
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			SummaryTotals.AverageTravel += vecJourneyCollection->at(i).travelCost;
			SummaryTotals.AverageExpense += vecJourneyCollection->at(i).expenseCost;
			SummaryTotals.AverageOfTotals += vecJourneyCollection->at(i).totalCost;
			SummaryTotals.AverageExpensePay += vecJourneyCollection->at(i).expensePayable;
			SummaryTotals.AverageTaxReclaim += vecJourneyCollection->at(i).taxReclaim;
			SummaryTotals.AverageNotCovered += vecJourneyCollection->at(i).expenseNotCovered;
			SummaryTotals.AverageFinalPay += vecJourneyCollection->at(i).finalPayment;
		}
		SummaryTotals.AverageTravel /= NumOfRecords;
		SummaryTotals.AverageExpense /= NumOfRecords;
		SummaryTotals.AverageOfTotals /= NumOfRecords;
		SummaryTotals.AverageExpensePay /= NumOfRecords;
		SummaryTotals.AverageTaxReclaim /= NumOfRecords;
		SummaryTotals.AverageNotCovered /= NumOfRecords;
		SummaryTotals.AverageFinalPay /= NumOfRecords;
		return SummaryTotals;
	}
}

auto CalculateTravelSummaryAverage(std::vector<Journey>* vecJourneyCollection) {
	struct result { double AverageTravel; double AverageTaxReclaim; double AverageFinalPay; };
	result SummaryTotals = result();
	std::size_t NumOfRecords = 0;
	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			if (vecJourneyCollection->at(i).travelType == TravelType::Travel) {
				NumOfRecords++;
			}
		}
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			if (vecJourneyCollection->at(i).travelType == TravelType::Travel) {
				SummaryTotals.AverageTravel += vecJourneyCollection->at(i).travelCost;
				SummaryTotals.AverageTaxReclaim += vecJourneyCollection->at(i).taxReclaim;
				SummaryTotals.AverageFinalPay += vecJourneyCollection->at(i).finalPayment;
			}
		}
		SummaryTotals.AverageTravel /= NumOfRecords;
		SummaryTotals.AverageTaxReclaim /= NumOfRecords;
		SummaryTotals.AverageFinalPay /= NumOfRecords;
		return SummaryTotals;
	}

}

auto CalculateTravelExpenseSummaryAverage(std::vector<Journey>* vecJourneyCollection) {
	struct result { double AverageTravel; double AverageExpense; double AverageOfTotals; double AverageExpensePay; double AverageTaxReclaim; double AverageNotCovered; double AverageFinalPay; };
	result SummaryTotals = result();
	std::size_t NumOfRecords = 0;
	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			if (vecJourneyCollection->at(i).travelType == TravelType::TravelAndExpense) {
				NumOfRecords++;
			}
		}
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			if (vecJourneyCollection->at(i).travelType == TravelType::TravelAndExpense) {
				SummaryTotals.AverageTravel += vecJourneyCollection->at(i).travelCost;
				SummaryTotals.AverageExpense += vecJourneyCollection->at(i).expenseCost;
				SummaryTotals.AverageOfTotals += vecJourneyCollection->at(i).totalCost;
				SummaryTotals.AverageExpensePay += vecJourneyCollection->at(i).expensePayable;
				SummaryTotals.AverageTaxReclaim += vecJourneyCollection->at(i).taxReclaim;
				SummaryTotals.AverageNotCovered += vecJourneyCollection->at(i).expenseNotCovered;
				SummaryTotals.AverageFinalPay += vecJourneyCollection->at(i).finalPayment;
			}
		}
		SummaryTotals.AverageTravel /= NumOfRecords;
		SummaryTotals.AverageExpense /= NumOfRecords;
		SummaryTotals.AverageOfTotals /= NumOfRecords;
		SummaryTotals.AverageExpensePay /= NumOfRecords;
		SummaryTotals.AverageTaxReclaim /= NumOfRecords;
		SummaryTotals.AverageNotCovered /= NumOfRecords;
		SummaryTotals.AverageFinalPay /= NumOfRecords;
		return SummaryTotals;
	}
}

auto CalculateAllSummaryLargest(std::vector<Journey>* vecJourneyCollection) {
	struct result { double LargestTravel; double LargestExpense; double LargestOfTotals; double LargestExpensePay; double LargestTaxReclaim; double LargestNotCovered; double LargestFinalPay; };
	result SummaryTotals = result();
	double dTravelLargest = 0, dExpenseLargest = 0, dTotalsLargest = 0, dExpensePayLargest = 0, dTaxReclaimLargest = 0, dNotCoveredLargest = 0, dFinalPayLargest = 0;

	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			if (vecJourneyCollection->at(i).travelCost > dTravelLargest) {
				dTravelLargest =vecJourneyCollection->at(i).travelCost;
			}
			if (vecJourneyCollection->at(i).expenseCost > dExpenseLargest) {
				dExpenseLargest = vecJourneyCollection->at(i).expenseCost;
			}
			if (vecJourneyCollection->at(i).totalCost > dTotalsLargest) {
				dTotalsLargest = vecJourneyCollection->at(i).totalCost;
			}
			if (vecJourneyCollection->at(i).expensePayable > dExpensePayLargest) {
				dExpensePayLargest = vecJourneyCollection->at(i).expensePayable;
			}
			if (vecJourneyCollection->at(i).taxReclaim > dTaxReclaimLargest) {
				dTaxReclaimLargest = vecJourneyCollection->at(i).taxReclaim;
			}
			if (vecJourneyCollection->at(i).expenseNotCovered > dNotCoveredLargest) {
				dNotCoveredLargest = vecJourneyCollection->at(i).expenseNotCovered;
			}
			if (vecJourneyCollection->at(i).finalPayment > dFinalPayLargest) {
				dFinalPayLargest = vecJourneyCollection->at(i).finalPayment;
			}
		}
		SummaryTotals.LargestTravel = dTravelLargest;
		SummaryTotals.LargestExpense = dExpenseLargest;
		SummaryTotals.LargestOfTotals = dTotalsLargest;
		SummaryTotals.LargestExpensePay = dExpensePayLargest;
		SummaryTotals.LargestTaxReclaim = dTaxReclaimLargest;
		SummaryTotals.LargestNotCovered = dNotCoveredLargest;
		SummaryTotals.LargestFinalPay = dFinalPayLargest;
		return SummaryTotals;
	}
}

auto CalculateTravelSummaryLargest(std::vector<Journey>* vecJourneyCollection) {
	struct result { double LargestTravel; double LargestTaxReclaim; double LargestFinalPay; };
	result SummaryTotals = result();
	double dTravelLargest = 0, dTaxReclaimLargest = 0, dFinalPayLargest = 0;

	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			if (vecJourneyCollection->at(i).travelType == TravelType::Travel) {
				if (vecJourneyCollection->at(i).travelCost > dTravelLargest) {
					dTravelLargest = vecJourneyCollection->at(i).travelCost;
				}
				if (vecJourneyCollection->at(i).taxReclaim > dTaxReclaimLargest) {
					dTaxReclaimLargest = vecJourneyCollection->at(i).taxReclaim;
				}
				if (vecJourneyCollection->at(i).finalPayment > dFinalPayLargest) {
					dFinalPayLargest = vecJourneyCollection->at(i).finalPayment;
				}
			}
		}
		SummaryTotals.LargestTravel = dTravelLargest;
		SummaryTotals.LargestTaxReclaim = dTaxReclaimLargest;
		SummaryTotals.LargestFinalPay = dFinalPayLargest;
		return SummaryTotals;
	}
}

auto CalculateTravelExpenseSummaryLargest(std::vector<Journey>* vecJourneyCollection) {
	struct result { double LargestTravel; double LargestExpense; double LargestOfTotals; double LargestExpensePay; double LargestTaxReclaim; double LargestNotCovered; double LargestFinalPay; };
	result SummaryTotals = result();
	double dTravelLargest = 0, dExpenseLargest = 0, dTotalsLargest = 0, dExpensePayLargest = 0, dTaxReclaimLargest = 0, dNotCoveredLargest = 0, dFinalPayLargest = 0;

	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			if (vecJourneyCollection->at(i).travelType == TravelType::TravelAndExpense) {
				if (vecJourneyCollection->at(i).travelCost > dTravelLargest) {
					dTravelLargest = vecJourneyCollection->at(i).travelCost;
				}
				if (vecJourneyCollection->at(i).expenseCost > dExpenseLargest) {
					dExpenseLargest = vecJourneyCollection->at(i).expenseCost;
				}
				if (vecJourneyCollection->at(i).totalCost > dTotalsLargest) {
					dTotalsLargest = vecJourneyCollection->at(i).totalCost;
				}
				if (vecJourneyCollection->at(i).expensePayable > dExpensePayLargest) {
					dExpensePayLargest = vecJourneyCollection->at(i).expensePayable;
				}
				if (vecJourneyCollection->at(i).taxReclaim > dTaxReclaimLargest) {
					dTaxReclaimLargest = vecJourneyCollection->at(i).taxReclaim;
				}
				if (vecJourneyCollection->at(i).expenseNotCovered > dNotCoveredLargest) {
					dNotCoveredLargest = vecJourneyCollection->at(i).expenseNotCovered;
				}
				if (vecJourneyCollection->at(i).finalPayment > dFinalPayLargest) {
					dFinalPayLargest = vecJourneyCollection->at(i).finalPayment;
				}
			}
		}
		SummaryTotals.LargestTravel = dTravelLargest;
		SummaryTotals.LargestExpense = dExpenseLargest;
		SummaryTotals.LargestOfTotals = dTotalsLargest;
		SummaryTotals.LargestExpensePay = dExpensePayLargest;
		SummaryTotals.LargestTaxReclaim = dTaxReclaimLargest;
		SummaryTotals.LargestNotCovered = dNotCoveredLargest;
		SummaryTotals.LargestFinalPay = dFinalPayLargest;
		return SummaryTotals;
	}
}

int ValidateIntInput() {
	int ChoiceValue;
	while (!(std::cin >> ChoiceValue)) {
		// Makes user try again if input is not an int
		std::cout << "ERROR: a whole number must be entered : ";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}

	return ChoiceValue;
}

double ValidateDoubleInput() {
	double DoubleValue;
	while (!(std::cin >> DoubleValue)) {
		// Makes user try again if input is not an int
		std::cout << "ERROR: a decimal number must be entered : ";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}

	return DoubleValue;
}

// Calculation functions end

// Views/Menu screens
void AddNewJourney(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	std::string strContinueAddingJourneys;
	bool boolExitWhile = false;

	int intTravelChoiceInput;
	TravelType travelTypeChoice;

	double dTravelCost = 0;
	double dExpenseCost = 0;

	do {
		PrintAddJourneyScreen(vecJourneyCollection);

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

void ViewJourneys(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	system("CLS");
	PrintTravelHeader(intWidth);
	PrintCurrentJourneysTravel(vecJourneyCollection, intWidth);
	std::cout << "\n";

	PrintTravelExpenseHeader(intWidth);
	PrintCurrentJourneysTravelExpense(vecJourneyCollection, intWidth);
	std::cout << "\n";
	Pause();
}

void ViewSummary(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intSummaryChoiceInput = 0;
	bool boolExitWhile = false;

	do {
		PrintSummaryScreen();
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
				case 4: {
					boolExitWhile = true;
					ViewSaveSummary(vecJourneyCollection, intWidth);
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
	catch (std::exception & exp) {
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
	catch (std::exception & exp) {
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
	catch (std::exception & exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	Pause();
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
	catch (std::exception & exp) {
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
	catch (std::exception & exp) {
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
	catch (std::exception & exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	Pause();
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
	catch (std::exception & exp) {
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
	catch (std::exception & exp) {
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
	catch (std::exception & exp) {
		std::cout << "Error : " << exp.what() << "\n";
	}

	Pause();
}

void ViewSaveSummary(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	system("cls");
	std::cout << "Sorry, this function has not been implemented yet\n";
	Pause();
}

void ViewComparison(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intComparisonChoiceInput = 0;
	bool boolExitWhile = false;

	do {
		PrintComparisonScreen();
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

void ViewCompareTwoJourneys(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	// TODO: Implement ability to compare two user selected journeys.
	// Implement this by presenting list of journeys, in order that they are in the vector, then allow user to make two choices (take 1 from their input so that it matches up to the array item).
	// Add the two specified vector items to a new vector and pass this to a comparison function.
	// Comparison function will print out both items, using the already existing print functions, and print out the same "summaries" values as seen in the main summaries section
	// Add aditional "Price difference" row that shows the price difference between the two invoices.
	// Plan to allow this to be exported as a file if user specifies.
	system("cls");
	std::cout << "Function not yet implemented.\n";
	Pause();
}

void ViewTotalTwoJourneys(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	// TODO: Implement ability to total two user selected journeys.
	// Implement this by presenting list of journeys, in order that they are in the vector, then allow user to make two choices (take 1 from their input so that it matches up to the array item).
	// Add the two specified vector items to a new vector and pass this to a totalling function.
	// Total function will add both together and present as row.
	// Plan to allow this to exported as a file if user specifies.
	system("cls");
	std::cout << "Function not yet implemented.\n";
	Pause();
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
	std::cout << "Notice: To ensure proper text formatting while in use, please make sure you right click on the console window header, \n";
	std::cout << "then go to defaults and disable the 'Wrap text output on resize' option. Without doing this, text will end up sat on the\n";
	std::cout << "same line ruining some of the output tables.\n";

	Pause();
}

/// <summary>
/// Prints the main menu screen intro, takes the Journey vector in order to hide options if they are not availale yet.
/// </summary>
/// <param name="vecJourneyCollection"></param>
void PrintMainMenuScreen(std::vector<Journey>* vecJourneyCollection) {
	system("cls");
	std::cout << "-------------------------------------------\n";
	std::cout << "\n";
	std::cout << "Welcome to the travel and expeses system.\n";
	std::cout << "Please specify your option:\n";
	std::cout << "\n";
	std::cout << "Option 1: Enter a new Journey\n";
	if (vecJourneyCollection->size() > 0) {
		std::cout << "Option 2: View current journeys\n";
	}
	if (vecJourneyCollection->size() > 0) {
		std::cout << "Option 3: Summaries\n";
	}
	if (vecJourneyCollection->size() > 0) {
		std::cout << "Option 4: Comparisons and itemised summary\n";
	}
	std::cout << "Option 9: Exit\n";
	std::cout << "\n";
	std::cout << "-------------------------------------------\n";
	std::cout << "\n";
}

void PrintAddJourneyScreen(std::vector<Journey>* vecJourneyCollection) {
	system("cls");
	std::cout << "-------------------------------------------\n";
	std::cout << "\n";
	std::cout << "Add new journey screen\n";
	std::cout << "Please specify your option:\n";
	std::cout << "\n";
	std::cout << "Option 1 : Travel only\n";
	std::cout << "Option 2 : Travel and expenses\n";
	if (vecJourneyCollection->size() > 0) {
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
	std::cout << "View and interact with summaries\n";
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

void PrintComparisonScreen() {
	system("cls");
	std::cout << "-------------------------------------------\n";
	std::cout << "\n";
	std::cout << "Make Comparisons and total invoices\n";
	std::cout << "Please specify your option:\n";
	std::cout << "\n";
	std::cout << "Option 1 : Compare two journeys\n";
	std::cout << "Option 2 : Total two journeys\n";
	std::cout << "Option 9 : Return to menu\n";
	std::cout << "\n";
	std::cout << "-------------------------------------------\n";
	std::cout << "\n";
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

	Journey journey1{ TravelType::Travel, 25.23534 };
	Journey journey2{ TravelType::TravelAndExpense, 23.23, 10.9263 };
	Journey journey3{ TravelType::Travel, 27 };
	Journey journey4{ TravelType::TravelAndExpense, 120.2553, 57.823 };

	vecJourneyCollection->push_back(journey1);
	vecJourneyCollection->push_back(journey2);
	vecJourneyCollection->push_back(journey3);
	vecJourneyCollection->push_back(journey4);
}

// Misc functions end

// Functions end