#pragma once

#include <vector>
#include <windows.h>
#include <iostream>
#include <iomanip>

#ifndef CALCFUNCTIONS_H
#define CALCFUNCTIONS_H

// Calculation function declarations.

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


