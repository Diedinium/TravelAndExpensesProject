#include "Structs.h"
#include "MiscFunctions.h"
#include "CalcFunctions.h"

// Calculation Functions

/// <summary>
/// Calculates totals for all journeys.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <returns></returns>
ResultTravelExpense CalculateAllSummaryTotals(std::vector<Journey>* vecJourneyCollection) {
	// Declare variables.
	ResultTravelExpense SummaryTotals = ResultTravelExpense();

	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		// Adds all values up, then returns results.
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

/// <summary>
/// Calculates totals for travel journeys only.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <returns></returns>
ResultTravel CalculateTravelSummaryTotals(std::vector<Journey>* vecJourneyCollection) {
	// Declare variables.
	ResultTravel SummaryTotals = ResultTravel();

	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		// Adds all values up, then returns results - but for travel only journeys.
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

/// <summary>
/// Calculates totals for travel and expenses journeys only.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <returns></returns>
ResultTravelExpense CalculateTravelExpenseSummaryTotals(std::vector<Journey>* vecJourneyCollection) {
	// Declare variables
	ResultTravelExpense SummaryTotals = ResultTravelExpense();

	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		// Adds all values up, then returns result - But only for travel and expense journeys.
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

/// <summary>
/// Calculates average of all journeys.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <returns></returns>
ResultTravelExpense CalculateAllSummaryAverage(std::vector<Journey>* vecJourneyCollection) {
	// Declare variables.
	ResultTravelExpense SummaryTotals = ResultTravelExpense();
	std::size_t NumOfRecords = 0;

	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		// Find number of records.
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			NumOfRecords++;
		}
		// Add up all values.
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			SummaryTotals.Travel += vecJourneyCollection->at(i).travelCost;
			SummaryTotals.Expense += vecJourneyCollection->at(i).expenseCost;
			SummaryTotals.Totals += vecJourneyCollection->at(i).totalCost;
			SummaryTotals.ExpensePay += vecJourneyCollection->at(i).expensePayable;
			SummaryTotals.TaxReclaim += vecJourneyCollection->at(i).taxReclaim;
			SummaryTotals.ExpenseNotCovered += vecJourneyCollection->at(i).expenseNotCovered;
			SummaryTotals.FinalPay += vecJourneyCollection->at(i).finalPayment;
		}

		// Sets values and returns results - divides by number of journeys.
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

/// <summary>
/// Calculates average of travel journeys only.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <returns></returns>
ResultTravel CalculateTravelSummaryAverage(std::vector<Journey>* vecJourneyCollection) {
	// Declare variables. 
	ResultTravel SummaryTotals = ResultTravel();
	std::size_t NumOfRecords = 0;

	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		// Find number of travel journeys.
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			if (vecJourneyCollection->at(i).travelType == TravelType::Travel) {
				NumOfRecords++;
			}
		}
		// Add all values up.
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			if (vecJourneyCollection->at(i).travelType == TravelType::Travel) {
				SummaryTotals.Travel += vecJourneyCollection->at(i).travelCost;
				SummaryTotals.TaxReclaim += vecJourneyCollection->at(i).taxReclaim;
				SummaryTotals.FinalPay += vecJourneyCollection->at(i).finalPayment;
			}
		}

		// Sets values and returns results - divides by number of journeys.
		SummaryTotals.Travel /= NumOfRecords;
		SummaryTotals.TaxReclaim /= NumOfRecords;
		SummaryTotals.FinalPay /= NumOfRecords;
		return SummaryTotals;
	}

}

/// <summary>
/// Calculates average of travel and expense journeys only.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <returns></returns>
ResultTravelExpense CalculateTravelExpenseSummaryAverage(std::vector<Journey>* vecJourneyCollection) {
	// Declare variables.
	ResultTravelExpense SummaryTotals = ResultTravelExpense();
	std::size_t NumOfRecords = 0;

	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		// Find number of travel and expense journeys.
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			if (vecJourneyCollection->at(i).travelType == TravelType::TravelAndExpense) {
				NumOfRecords++;
			}
		}
		// Add up all values.
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

		// Sets values and returns results - divides by number of journeys.
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


/// <summary>
/// Calculates largest value of all journeys.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <returns></returns>
ResultTravelExpense CalculateAllSummaryLargest(std::vector<Journey>* vecJourneyCollection) {
	// Declare variables.
	ResultTravelExpense SummaryTotals = ResultTravelExpense();
	double dTravelLargest = 0, dExpenseLargest = 0, dTotalsLargest = 0, dExpensePayLargest = 0, dTaxReclaimLargest = 0, dNotCoveredLargest = 0, dFinalPayLargest = 0;

	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		// Finds largest value by setting appropriate value if item is bigger than current stored value. 
		// Once entire vector is iterated through, the largest found value will be contained in each variable.
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

		// Sets values and returns results.
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
/// Calculates largest value of travel journeys only.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <returns></returns>
ResultTravel CalculateTravelSummaryLargest(std::vector<Journey>* vecJourneyCollection) {
	// Declare variables.
	ResultTravel SummaryTotals = ResultTravel();
	double dTravelLargest = 0, dTaxReclaimLargest = 0, dFinalPayLargest = 0;

	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		// Finds largest value by setting appropriate value if item is bigger than current stored value. 
		// Once entire vector is iterated through, the largest found value will be contained in each variable.
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			// Only attempts to find largest for travel journey types.
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

		// Sets values and returns results.
		SummaryTotals.Travel = dTravelLargest;
		SummaryTotals.TaxReclaim = dTaxReclaimLargest;
		SummaryTotals.FinalPay = dFinalPayLargest;
		return SummaryTotals;
	}
}

/// <summary>
/// Calculates largest value of travel and expense journeys only.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <returns></returns>
ResultTravelExpense CalculateTravelExpenseSummaryLargest(std::vector<Journey>* vecJourneyCollection) {
	// Declare variables.
	ResultTravelExpense SummaryTotals = ResultTravelExpense();
	double dTravelLargest = 0, dExpenseLargest = 0, dTotalsLargest = 0, dExpensePayLargest = 0, dTaxReclaimLargest = 0, dNotCoveredLargest = 0, dFinalPayLargest = 0;

	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
		return SummaryTotals;
	}
	else {
		// Finds largest value by setting appropriate value if item is bigger than current stored value. 
		// Once entire vector is iterated through, the largest found value will be contained in each variable.
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			// Only attempts to find largest for travel and expense journey types.
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

		// Sets values and returns results.
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
/// Calculates difference between two journeys. Expects pass of only two items, since function only compares first two items regardless, will ignore any extra items if they end up (somehow) being passed.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <returns></returns>
ResultTravelExpense CalculateTwoItemComparison(std::vector<Journey>* vecJourneyCollection) {
	// Declare variables.
	ResultTravelExpense SummaryTotals = ResultTravelExpense();
	double dTravelDiff = 0, dExpenseDiff = 0, dTotalsDiff = 0, dExpensePayDiff = 0, dTaxReclaimDiff = 0, dNotCoveredDiff = 0, dFinalPayDiff = 0;

	// Ensures that lower value is taken from higher in order to find difference.
	// If value is 0 for both.
	if (vecJourneyCollection->at(0).travelCost == 0 && vecJourneyCollection->at(1).travelCost == 0) {
		dTravelDiff = 0;
	}
	else {
		// If values match for both.
		if (vecJourneyCollection->at(0).travelCost == vecJourneyCollection->at(1).travelCost) {
			dTravelDiff = 0;
		}
		else {
			// If value for journey 0 is greater than value for journey 1, take journey 1 value from journey 0
			if (vecJourneyCollection->at(0).travelCost > vecJourneyCollection->at(1).travelCost) {
				dTravelDiff = vecJourneyCollection->at(0).travelCost - vecJourneyCollection->at(1).travelCost;
			}
			// Else, journey 1 must be greater than journey 0. Take Journey 0 from journey 1.
			else {
				dTravelDiff = vecJourneyCollection->at(1).travelCost - vecJourneyCollection->at(0).travelCost;
			}
		}
	}

	// Above if statement repeats for other 6 values.

	// Finds difference for expense cost.
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

	// Finds difference for total cost.
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

	// Finds difference for expense payable.
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

	// Finds difference for tax reclaim.
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

	// Finds difference for expense not covered.
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

	// Finds difference for final payment.
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

	// Sets values and returns result.
	SummaryTotals.Travel = dTravelDiff;
	SummaryTotals.Expense = dExpenseDiff;
	SummaryTotals.Totals = dTotalsDiff;
	SummaryTotals.ExpensePay = dExpensePayDiff;
	SummaryTotals.TaxReclaim = dTaxReclaimDiff;
	SummaryTotals.ExpenseNotCovered = dNotCoveredDiff;
	SummaryTotals.FinalPay = dFinalPayDiff;
	return SummaryTotals;
}

