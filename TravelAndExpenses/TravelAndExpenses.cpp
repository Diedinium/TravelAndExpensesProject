// TravelAndExpenses.cpp : The main application file for the travel and expenses console app.

#include <iostream>
#include <string>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <vector>
#include <iomanip>
#include <map>

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

	// Constructor for travel only
	Journey(TravelType passTravelType, double passCost)
	{
		travelType = passTravelType;
		travelCost = passCost;
		totalCost = travelCost;
		expenseCost = 0;
		expensePayable = 0;
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
		}
		else {
			expensePayable = expenseCost;
		}
		finalPayment = expensePayable + travelCost;
	}


};

std::vector<Journey> vecJourneyCollection;

int main()
{
	

	Journey journey1{ TravelType::Travel, 25.23 };
	Journey journey2{ TravelType::TravelAndExpense, 23.23, 10.92 };
	Journey journey3{ TravelType::Travel, 25.23 };
	Journey journey4{ TravelType::TravelAndExpense, 120.25, 57.82 };
	
	vecJourneyCollection.push_back(journey1);
	vecJourneyCollection.push_back(journey2);
	vecJourneyCollection.push_back(journey3);
	vecJourneyCollection.push_back(journey4);

	for (int i = 0; i < (int)vecJourneyCollection.size(); ++i) {
		if (vecJourneyCollection[i].travelType == TravelType::Travel) {
			std::cout << "Travel type : " << ((((int)vecJourneyCollection[i].travelType) == 0) ? "Travel" : "Travel and Expenses")<< "\n";
			std::cout << "Total Cost : \x9C"  << vecJourneyCollection[i].totalCost << "\n";
			printf("Tax Reclaimable : \x9C%.2f\n", vecJourneyCollection[i].taxReclaim);
			printf("Final payment made : \x9C%.2f\n", vecJourneyCollection[i].finalPayment);
			std::cout << " " << "\n";
		}
		else {
			std::cout << "Travel type : " << ((((int)vecJourneyCollection[i].travelType) == 0) ? "Travel" : "Travel and Expenses") << "\n";
			std::cout << "Travel Cost : \x9C" << vecJourneyCollection[i].travelCost << "\n";
			std::cout << "Expense Cost : \x9C" << vecJourneyCollection[i].expenseCost << "\n";
			std::cout << "Total Cost : \x9C" << vecJourneyCollection[i].totalCost << "\n";
			printf("Tax Reclaimable : \x9C%.2f\n", vecJourneyCollection[i].taxReclaim);
			printf("Expenses Payable : \x9C%.2f\n", vecJourneyCollection[i].expensePayable);
			printf("Final payment made : \x9C%.2f\n", vecJourneyCollection[i].finalPayment);
			std::cout << " " << "\n";
		}
	}

	return 0;
}