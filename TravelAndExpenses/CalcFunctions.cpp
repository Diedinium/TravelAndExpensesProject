#include "MiscFunctions.h"
#include "CalcFunctions.h"

// Calculation Functions
ResultTravelExpense CalculateAllSummaryTotals(std::vector<Journey>* vecJourneyCollection) {
	//struct result { double TotalTravel; double TotalExpense; double TotalOfTotals; double TotalExpensePay; double TotalTaxReclaim; double ExpenseNotCovered; double TotalFinalPay; };
	ResultTravelExpense SummaryTotals = ResultTravelExpense();
	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			SummaryTotals.Travel += vecJourneyCollection->at(i).travelCost;
			SummaryTotals.Expense += vecJourneyCollection->at(i).expenseCost;
			SummaryTotals.Totals += vecJourneyCollection->at(i).totalCost;
			SummaryTotals.ExpensePay += vecJourneyCollection->at(i).expensePayable;
			SummaryTotals.TaxReclaim += vecJourneyCollection->at(i).taxReclaim;
			SummaryTotals.ExpenseNotCovered += vecJourneyCollection->at(i).expenseNotCovered;
			SummaryTotals.FinalPay += vecJourneyCollection->at(i).finalPayment;
		}
		return SummaryTotals;
	}

}

ResultTravel CalculateTravelSummaryTotals(std::vector<Journey>* vecJourneyCollection) {
	//struct result { double TotalTravel; double TotalTaxReclaim; double TotalFinalPay; };
	ResultTravel SummaryTotals = ResultTravel();
	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			if (vecJourneyCollection->at(i).travelType == TravelType::Travel) {
				SummaryTotals.Travel += vecJourneyCollection->at(i).travelCost;
				SummaryTotals.TaxReclaim += vecJourneyCollection->at(i).taxReclaim;
				SummaryTotals.FinalPay += vecJourneyCollection->at(i).finalPayment;
			}
		}
		return SummaryTotals;
	}
}

ResultTravelExpense CalculateTravelExpenseSummaryTotals(std::vector<Journey>* vecJourneyCollection) {
	//struct result { double TotalTravel; double TotalExpense; double TotalOfTotals; double TotalExpensePay; double TotalTaxReclaim; double ExpenseNotCovered; double TotalFinalPay; };
	ResultTravelExpense SummaryTotals = ResultTravelExpense();
	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			if (vecJourneyCollection->at(i).travelType == TravelType::TravelAndExpense) {
				SummaryTotals.Travel += vecJourneyCollection->at(i).travelCost;
				SummaryTotals.Expense += vecJourneyCollection->at(i).expenseCost;
				SummaryTotals.Totals += vecJourneyCollection->at(i).totalCost;
				SummaryTotals.ExpensePay += vecJourneyCollection->at(i).expensePayable;
				SummaryTotals.TaxReclaim += vecJourneyCollection->at(i).taxReclaim;
				SummaryTotals.ExpenseNotCovered += vecJourneyCollection->at(i).expenseNotCovered;
				SummaryTotals.FinalPay += vecJourneyCollection->at(i).finalPayment;
			}

		}
		return SummaryTotals;
	}
}

ResultTravelExpense CalculateAllSummaryAverage(std::vector<Journey>* vecJourneyCollection) {
	//struct result { double AverageTravel; double AverageExpense; double AverageOfTotals; double AverageExpensePay; double AverageTaxReclaim; double AverageNotCovered; double AverageFinalPay; };
	ResultTravelExpense SummaryTotals = ResultTravelExpense();
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
			SummaryTotals.Travel += vecJourneyCollection->at(i).travelCost;
			SummaryTotals.Expense += vecJourneyCollection->at(i).expenseCost;
			SummaryTotals.Totals += vecJourneyCollection->at(i).totalCost;
			SummaryTotals.ExpensePay += vecJourneyCollection->at(i).expensePayable;
			SummaryTotals.TaxReclaim += vecJourneyCollection->at(i).taxReclaim;
			SummaryTotals.ExpenseNotCovered += vecJourneyCollection->at(i).expenseNotCovered;
			SummaryTotals.FinalPay += vecJourneyCollection->at(i).finalPayment;
		}
		SummaryTotals.Travel /= NumOfRecords;
		SummaryTotals.Expense /= NumOfRecords;
		SummaryTotals.Totals /= NumOfRecords;
		SummaryTotals.ExpensePay /= NumOfRecords;
		SummaryTotals.TaxReclaim /= NumOfRecords;
		SummaryTotals.ExpenseNotCovered /= NumOfRecords;
		SummaryTotals.FinalPay /= NumOfRecords;
		return SummaryTotals;
	}
}

ResultTravel CalculateTravelSummaryAverage(std::vector<Journey>* vecJourneyCollection) {
	//struct result { double AverageTravel; double AverageTaxReclaim; double AverageFinalPay; };
	ResultTravel SummaryTotals = ResultTravel();
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
				SummaryTotals.Travel += vecJourneyCollection->at(i).travelCost;
				SummaryTotals.TaxReclaim += vecJourneyCollection->at(i).taxReclaim;
				SummaryTotals.FinalPay += vecJourneyCollection->at(i).finalPayment;
			}
		}
		SummaryTotals.Travel /= NumOfRecords;
		SummaryTotals.TaxReclaim /= NumOfRecords;
		SummaryTotals.FinalPay /= NumOfRecords;
		return SummaryTotals;
	}

}

ResultTravelExpense CalculateTravelExpenseSummaryAverage(std::vector<Journey>* vecJourneyCollection) {
	//struct result { double AverageTravel; double AverageExpense; double AverageOfTotals; double AverageExpensePay; double AverageTaxReclaim; double AverageNotCovered; double AverageFinalPay; };
	ResultTravelExpense SummaryTotals = ResultTravelExpense();
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
				SummaryTotals.Travel += vecJourneyCollection->at(i).travelCost;
				SummaryTotals.Expense += vecJourneyCollection->at(i).expenseCost;
				SummaryTotals.Totals += vecJourneyCollection->at(i).totalCost;
				SummaryTotals.ExpensePay += vecJourneyCollection->at(i).expensePayable;
				SummaryTotals.TaxReclaim += vecJourneyCollection->at(i).taxReclaim;
				SummaryTotals.ExpenseNotCovered += vecJourneyCollection->at(i).expenseNotCovered;
				SummaryTotals.FinalPay += vecJourneyCollection->at(i).finalPayment;
			}
		}
		SummaryTotals.Travel /= NumOfRecords;
		SummaryTotals.Expense /= NumOfRecords;
		SummaryTotals.Totals /= NumOfRecords;
		SummaryTotals.ExpensePay /= NumOfRecords;
		SummaryTotals.TaxReclaim /= NumOfRecords;
		SummaryTotals.ExpenseNotCovered /= NumOfRecords;
		SummaryTotals.FinalPay /= NumOfRecords;
		return SummaryTotals;
	}
}

ResultTravelExpense CalculateAllSummaryLargest(std::vector<Journey>* vecJourneyCollection) {
	//struct result { double LargestTravel; double LargestExpense; double LargestOfTotals; double LargestExpensePay; double LargestTaxReclaim; double LargestNotCovered; double LargestFinalPay; };
	ResultTravelExpense SummaryTotals = ResultTravelExpense();
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
		SummaryTotals.Travel = dTravelLargest;
		SummaryTotals.Expense = dExpenseLargest;
		SummaryTotals.Totals = dTotalsLargest;
		SummaryTotals.ExpensePay = dExpensePayLargest;
		SummaryTotals.TaxReclaim = dTaxReclaimLargest;
		SummaryTotals.ExpenseNotCovered = dNotCoveredLargest;
		SummaryTotals.FinalPay = dFinalPayLargest;
		return SummaryTotals;
	}
}

ResultTravel CalculateTravelSummaryLargest(std::vector<Journey>* vecJourneyCollection) {
	//struct result { double LargestTravel; double LargestTaxReclaim; double LargestFinalPay; };
	ResultTravel SummaryTotals = ResultTravel();
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
		SummaryTotals.Travel = dTravelLargest;
		SummaryTotals.TaxReclaim = dTaxReclaimLargest;
		SummaryTotals.FinalPay = dFinalPayLargest;
		return SummaryTotals;
	}
}

ResultTravelExpense CalculateTravelExpenseSummaryLargest(std::vector<Journey>* vecJourneyCollection) {
	//struct result { double LargestTravel; double LargestExpense; double LargestOfTotals; double LargestExpensePay; double LargestTaxReclaim; double LargestNotCovered; double LargestFinalPay; };
	ResultTravelExpense SummaryTotals = ResultTravelExpense();
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
		SummaryTotals.Travel = dTravelLargest;
		SummaryTotals.Expense = dExpenseLargest;
		SummaryTotals.Totals = dTotalsLargest;
		SummaryTotals.ExpensePay = dExpensePayLargest;
		SummaryTotals.TaxReclaim = dTaxReclaimLargest;
		SummaryTotals.ExpenseNotCovered = dNotCoveredLargest;
		SummaryTotals.FinalPay = dFinalPayLargest;
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
ResultTravelExpense CalculateTwoItemComparison(std::vector<Journey>* vecJourneyCollection) {

	//struct result { double DiffTravel; double DiffExpense; double DiffOfTotals; double DiffExpensePay; double DiffTaxReclaim; double DifffNotCovered; double DiffFinalPay; };
	ResultTravelExpense SummaryTotals = ResultTravelExpense();
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

	SummaryTotals.Travel = dTravelDiff;
	SummaryTotals.Expense = dExpenseDiff;
	SummaryTotals.Totals = dTotalsDiff;
	SummaryTotals.ExpensePay = dExpensePayDiff;
	SummaryTotals.TaxReclaim = dTaxReclaimDiff;
	SummaryTotals.ExpenseNotCovered = dNotCoveredDiff;
	SummaryTotals.FinalPay = dFinalPayDiff;

	return SummaryTotals;
}

