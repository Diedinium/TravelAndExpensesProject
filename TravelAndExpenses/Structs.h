#pragma once
#include <vector>
#include <windows.h>
#include <iostream>
#include <iomanip>

#ifndef STRUCTS_H
#define STRUCTS_H

// Travel type enum.
enum class TravelType
{
	Travel,
	TravelAndExpense
};

// Journey struct
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

// Choice option struct
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

// Full 7 item result.
struct ResultTravelExpense {
	double Travel;
	double Expense;
	double Totals;
	double ExpensePay;
	double TaxReclaim;
	double ExpenseNotCovered;
	double FinalPay;
};

// 3 item result.
struct ResultTravel {
	double Travel;
	double TaxReclaim;
	double FinalPay;
};

#endif // !STRUCTS_H
