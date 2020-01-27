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
#include <stdexcept>

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
void PrintAllJourneyNumberedHeader(int* intWidth);
void PrintAllJourneyNumberedHeader(int* intWidth, std::string message);
void PrintAllJourneysInOrder(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void PrintSaveExportScreen();
void PrintDeleteChoiceScreen();


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
bool InRange(int low, int high, int compare);

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
void ViewSaveSummary(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewComparison(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewCompareTwoJourneys(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewTotalTwoJourneys(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewDeleteChoice(std::vector<Journey>* vecJourneyCollection, int* intWidth);
void ViewDeleteJourney(std::vector<Journey>* vecJourneyCollection, int* intWidth);

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

/// <summary>
/// Expects pass of only two items, since function only compares first two items regardless, will ignore any extra items if they end up (somehow) being passed.
/// Items are compared, lower value is taken from higher value. This provides difference of items. If both match, 0 is returned as there is no difference.
///	Wrap in try/catch statement, to handle possiblility of only one vector item being passed.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <returns></returns>
auto CalculateTwoItemComparison(std::vector<Journey>* vecJourneyCollection) {

	struct result { double DiffTravel; double DiffExpense; double DiffOfTotals; double DiffExpensePay; double DiffTaxReclaim; double DifffNotCovered; double DiffFinalPay; };
	result SummaryTotals = result();
	double dTravelDiff = 0, dExpenseDiff = 0, dTotalsDiff = 0, dExpensePayDiff = 0, dTaxReclaimDiff = 0, dNotCoveredDiff = 0, dFinalPayDiff = 0;

	if (vecJourneyCollection->at(0).travelCost == 0 && vecJourneyCollection->at(1).travelCost == 0) {
		dTravelDiff = 0;
	}
	else {
		if (vecJourneyCollection->at(0).travelCost == vecJourneyCollection->at(1).travelCost) {
			dTravelDiff = 0;
		}
		else {
			if (vecJourneyCollection->at(0).travelCost > vecJourneyCollection->at(1).travelCost) {
				dTravelDiff = vecJourneyCollection->at(0).travelCost - vecJourneyCollection->at(1).travelCost;
			}
			else {
				dTravelDiff = vecJourneyCollection->at(1).travelCost - vecJourneyCollection->at(0).travelCost;
			}
		}
	}

	if (vecJourneyCollection->at(0).expenseCost == 0 && vecJourneyCollection->at(1).expenseCost == 0) {
		dExpenseDiff = 0;
	}
	else {
		if (vecJourneyCollection->at(0).expenseCost == vecJourneyCollection->at(1).expenseCost) {
			dExpenseDiff = 0;
		}
		else {
			if (vecJourneyCollection->at(0).expenseCost > vecJourneyCollection->at(1).expenseCost) {
				dExpenseDiff = vecJourneyCollection->at(0).expenseCost - vecJourneyCollection->at(1).expenseCost;
			}
			else {
				dExpenseDiff = vecJourneyCollection->at(1).expenseCost - vecJourneyCollection->at(0).expenseCost;
			}
		}
	}

	if (vecJourneyCollection->at(0).totalCost == 0 && vecJourneyCollection->at(1).totalCost == 0) {
		dTotalsDiff = 0;
	}
	else {
		if (vecJourneyCollection->at(0).totalCost == vecJourneyCollection->at(1).totalCost) {
			dTotalsDiff = 0;
		}
		else {
			if (vecJourneyCollection->at(0).totalCost > vecJourneyCollection->at(1).totalCost) {
				dTotalsDiff = vecJourneyCollection->at(0).totalCost - vecJourneyCollection->at(1).totalCost;
			}
			else {
				dTotalsDiff = vecJourneyCollection->at(1).totalCost - vecJourneyCollection->at(0).totalCost;
			}
		}
	}

	if (vecJourneyCollection->at(0).expensePayable == 0 && vecJourneyCollection->at(1).expensePayable == 0) {
		dExpensePayDiff = 0;
	}
	else {
		if (vecJourneyCollection->at(0).expensePayable == vecJourneyCollection->at(1).expensePayable) {
			dExpensePayDiff = 0;
		}
		else {
			if (vecJourneyCollection->at(0).expensePayable > vecJourneyCollection->at(1).expensePayable) {
				dExpensePayDiff = vecJourneyCollection->at(0).expensePayable - vecJourneyCollection->at(1).expensePayable;
			}
			else {
				dExpensePayDiff = vecJourneyCollection->at(1).expensePayable - vecJourneyCollection->at(0).expensePayable;
			}
		}
	}

	if (vecJourneyCollection->at(0).taxReclaim == 0 && vecJourneyCollection->at(1).taxReclaim == 0) {
		dTaxReclaimDiff = 0;
	}
	else {
		if (vecJourneyCollection->at(0).taxReclaim == vecJourneyCollection->at(1).taxReclaim) {
			dTaxReclaimDiff = 0;
		}
		else {
			if (vecJourneyCollection->at(0).taxReclaim > vecJourneyCollection->at(1).taxReclaim) {
				dTaxReclaimDiff = vecJourneyCollection->at(0).taxReclaim - vecJourneyCollection->at(1).taxReclaim;
			}
			else {
				dTaxReclaimDiff = vecJourneyCollection->at(1).taxReclaim - vecJourneyCollection->at(0).taxReclaim;
			}
		}
	}

	if (vecJourneyCollection->at(0).expenseNotCovered == 0 && vecJourneyCollection->at(1).expenseNotCovered == 0) {
		dNotCoveredDiff = 0;
	}
	else {
		if (vecJourneyCollection->at(0).expenseNotCovered == vecJourneyCollection->at(1).expenseNotCovered) {
			dNotCoveredDiff = 0;
		}
		else {
			if (vecJourneyCollection->at(0).expenseNotCovered > vecJourneyCollection->at(1).expenseNotCovered) {
				dNotCoveredDiff = vecJourneyCollection->at(0).expenseNotCovered - vecJourneyCollection->at(1).expenseNotCovered;
			}
			else {
				dNotCoveredDiff = vecJourneyCollection->at(1).expenseNotCovered - vecJourneyCollection->at(0).expenseNotCovered;
			}
		}
	}

	if (vecJourneyCollection->at(0).finalPayment == 0 && vecJourneyCollection->at(1).finalPayment == 0) {
		dFinalPayDiff = 0;
	}
	else {
		if (vecJourneyCollection->at(0).finalPayment == vecJourneyCollection->at(1).finalPayment) {
			dFinalPayDiff = 0;
		}
		else {
			if (vecJourneyCollection->at(0).finalPayment > vecJourneyCollection->at(1).finalPayment) {
				dFinalPayDiff = vecJourneyCollection->at(0).finalPayment - vecJourneyCollection->at(1).finalPayment;
			}
			else {
				dFinalPayDiff = vecJourneyCollection->at(1).finalPayment - vecJourneyCollection->at(0).finalPayment;
			}
		}
	}

	SummaryTotals.DiffTravel = dTravelDiff;
	SummaryTotals.DiffExpense = dExpenseDiff;
	SummaryTotals.DiffOfTotals = dTotalsDiff;
	SummaryTotals.DiffExpensePay = dExpensePayDiff;
	SummaryTotals.DiffTaxReclaim = dTaxReclaimDiff;
	SummaryTotals.DifffNotCovered = dNotCoveredDiff;
	SummaryTotals.DiffFinalPay = dFinalPayDiff;

	return SummaryTotals;
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

/// <summary>
/// Returns true if compare integer passed into function is within range of low and high, false if not.
/// </summary>
/// <param name="low"></param>
/// <param name="high"></param>
/// <param name="compare"></param>
/// <returns></returns>
bool InRange(int low, int high, int compare) {
	return ((compare - high) * (compare - low) <= 0);
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
				else if (intTravelChoiceInput == 9) {
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
	ViewDeleteChoice(vecJourneyCollection, intWidth);
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
			catch (std::exception & exp) {
				std::cout << "Error : " << exp.what() << "\n";
			}
		}

	} while (intSummaryChoiceInput != 9);

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
	catch (std::exception & exp) {
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
	catch (std::exception & exp) {
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
	catch (std::exception & exp) {
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
	catch (std::exception & exp) {
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
			catch (std::exception & exp) {
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
		PrintSaveExportScreen();
		boolExitWhile = false;

		while (boolExitWhile == false) {
			std::cout << "Enter choice : ";
			intSaveExportChoiceInput = ValidateIntInput();

			try {
				switch (intSaveExportChoiceInput) {
					case 1: {
						ViewSaveSummary(vecJourneyCollection, intWidth);
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
			catch (std::exception & exp) {
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
		catch (std::out_of_range & ex) {
			std::cout << "The number you specified is not a valid item currently in the list.\n";
		}
		catch (std::runtime_error & ex) {
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
		catch (std::out_of_range & ex) {
			std::cout << "The number you specified is not a valid item currently in the list.\n";
		}
		catch (std::runtime_error & ex) {
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
void ViewDeleteChoice(std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	int intDeleteChoiceInput = 0;
	bool boolExitWhile = false;

	do {
		PrintDeleteChoiceScreen();
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
					ViewSaveSummary(vecJourneyCollection, intWidth);
					boolExitWhile = true;
					intDeleteChoiceInput = 9;
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
			catch (std::exception & exp) {
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

	system("cls");
	PrintAllJourneyNumberedHeader(intWidth);
	PrintAllJourneysInOrder(vecJourneyCollection, intWidth);

	std::cout << "\n";
	std::cout << "Please specify number of the journey you would like to remove.\n";
	do {
		std::cout << "Enter Choice : ";
		intJourneyToDelete = ValidateIntInput() - 1;

		if (InRange(0, (int)vecJourneyCollection->size() - 1, intJourneyToDelete)) {
			// Try to erase the specified choice.
			try {
				vecJourneyCollection->erase(vecJourneyCollection->begin() + intJourneyToDelete);
			}
			catch (std::exception ex) {
				std::cout << "The number you specified is not a valid item currently in the list.\n";
			}
		}
		else {
			std::cout << "The number you specified is not a valid item currently in the list.\n";
		}

		
	} while (!InRange(0, (int)vecJourneyCollection->size() - 1, intJourneyToDelete));

	std::cout << "\n";
	std::cout << "Journey " << (intJourneyToDelete + 1) << " successfully removed.\n";

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
	std::cout << "Option 1 : Enter a new Journey\n";
	if (vecJourneyCollection->size() > 0) {
		std::cout << "Option 2 : View current journeys\n";
	}
	if (vecJourneyCollection->size() > 0) {
		std::cout << "Option 3 : Summaries\n";
	}
	if (vecJourneyCollection->size() > 0) {
		std::cout << "Option 4 : Comparisons and itemised summary\n";
	}
	if (vecJourneyCollection->size() > 0) {
		std::cout << "Option 5 : Remove a Journey\n";
	}
	std::cout << "Option 9 : Exit\n";
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
	std::cout << "Option 9 : Return to menu\n";
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
	std::cout << "Option 9 : Return to menu\n";
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

void PrintSaveExportScreen() {
	std::cout << "\n";
	std::cout << "You can now either choose to Save these items for future importing (.CSV file) or return to the previous screen.\n";
	std::cout << "Please specify your option:\n";
	std::cout << "\n";
	std::cout << "Option 1 : Export list as CSV\n";
	std::cout << "Option 9 : Return to previous\n";
	std::cout << "\n";
}

void PrintDeleteChoiceScreen() {
	std::cout << "\n";
	std::cout << "Please specifiy which of the following options you would like to do.\n";
	std::cout << "Please specify your option:\n";
	std::cout << "\n";
	std::cout << "Option 1 : Delete a Journey\n";
	std::cout << "Option 2 : Export List as CSV\n";
	std::cout << "Option 9 : Return to previous\n";
	std::cout << "\n";
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

// Print out functions end

// I/O Functions

void ExportVectorAsCSV(std::vector<Journey>* vecJourneyCollection) {
	// TODO : First need to print column headers, Will then need to do a for loop. For each item in the passed vector array, will write value to a CSV row then do new line.
	system("cls");
	std::cout << "TODO: Implement exporting of the object vector array, this function is not yet implemented.";
	Pause();
}

auto ImportVectorFromCSV(std::vector<Journey>* vecJourneyCollection) {
	// TODO : Need to allow user to specify file path (full file path, from C: drive), file is then read, error displayed if unable to read. Each row is read and pushed as an item into vector, then returned.
	std::vector<Journey> vecImportedJourney;
	int intNumItemsImported = 0;

	system("cls");
	std::cout << "TODO: Implement exporting of the object vector array, this function is not yet implemented.";
	Pause();

	return vecImportedJourney;
}

// I/O Functions end

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