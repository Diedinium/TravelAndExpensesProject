#pragma once

#include <vector>
#include <windows.h>
#include <iostream>
#include <iomanip>

#ifndef CALCFUNCTIONS_H
#define CALCFUNCTIONS_H

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

struct ResultTravelExpense {
	double Travel;
	double Expense;
	double Totals;
	double ExpensePay;
	double TaxReclaim;
	double ExpenseNotCovered;
	double FinalPay;
};

struct ResultTravel {
	double Travel;
	double TaxReclaim;
	double FinalPay;
};

ResultTravelExpense CalculateAllSummaryTotals(std::vector<Journey>* vecJourneyCollection);
ResultTravel CalculateTravelSummaryTotals(std::vector<Journey>* vecJourneyCollection);
ResultTravelExpense CalculateTravelExpenseSummaryTotals(std::vector<Journey>* vecJourneyCollection);
ResultTravelExpense CalculateAllSummaryAverage(std::vector<Journey>* vecJourneyCollection);
ResultTravel CalculateTravelSummaryAverage(std::vector<Journey>* vecJourneyCollection);
ResultTravelExpense CalculateTravelExpenseSummaryAverage(std::vector<Journey>* vecJourneyCollection);
ResultTravelExpense CalculateAllSummaryLargest(std::vector<Journey>* vecJourneyCollection);
ResultTravel CalculateTravelSummaryLargest(std::vector<Journey>* vecJourneyCollection);
ResultTravelExpense CalculateTravelExpenseSummaryLargest(std::vector<Journey>* vecJourneyCollection);
ResultTravelExpense CalculateTwoItemComparison(std::vector<Journey>* vecJourneyCollection);

#endif // !CALCFUNCTIONS_H


