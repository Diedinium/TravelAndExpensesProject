#pragma once

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

//int ValidateIntInput();
//double ValidateDoubleInput();
//auto CalculateAllSummaryTotals(std::vector<Journey>* vecJourneyCollection);
//auto CalculateTravelSummaryTotals(std::vector<Journey>* vecJourneyCollection);
//auto CalculateTravelExpenseSummaryTotals(std::vector<Journey>* vecJourneyCollection);
//auto CalculateAllSummaryAverage(std::vector<Journey>* vecJourneyCollection);
//auto CalculateTravelSummaryAverage(std::vector<Journey>* vecJourneyCollection);
//auto CalculateTravelExpenseSummaryAverage(std::vector<Journey>* vecJourneyCollection);
//auto CalculateAllSummaryLargest(std::vector<Journey>* vecJourneyCollection);
//auto CalculateTravelSummaryLargest(std::vector<Journey>* vecJourneyCollection);
//auto CalculateTravelExpenseSummaryLargest(std::vector<Journey>* vecJourneyCollection);
//bool InRange(int low, int high, int compare);

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

/// <summary>
/// Checks if file name is already in use.
/// </summary>
/// <param name="fileName"></param>
/// <returns></returns>
bool fileExists(std::string fileName) {
	std::ifstream ifile(fileName);
	return ifile.good();
}