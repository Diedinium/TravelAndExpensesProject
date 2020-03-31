#include "Structs.h"
#include "MiscFunctions.h"

/// <summary>
/// Validates that input is an int.
/// </summary>
/// <param name="hConsole"></param>
/// <returns></returns>
int ValidateIntInput(HANDLE* hConsole) {
	int ChoiceValue;

	// While cin is not valid, loop.
	while (!(std::cin >> ChoiceValue && std::isspace(std::cin.peek()))) {
		SetConsoleTextAttribute(*hConsole, 12);
		std::cout << "Error: a whole number must be entered : ";
		SetConsoleTextAttribute(*hConsole, 15);
		// Clear cin
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}

	return ChoiceValue;
}

/// <summary>
/// Validates that input is a double.
/// </summary>
/// <param name="hConsole"></param>
/// <returns></returns>
double ValidateDoubleInput(HANDLE* hConsole) {
	double DoubleValue = 0;

	while (DoubleValue <= 0) {
		// While cin is not valid, loop.
		while (!(std::cin >> DoubleValue)) {
			SetConsoleTextAttribute(*hConsole, 12);
			std::cout << "Error: a decimal number must be entered : ";
			SetConsoleTextAttribute(*hConsole, 15);
			// Clear cin
			std::cin.clear();
			std::cin.ignore(123, '\n');
		}
		if (DoubleValue <= 0) {
			SetConsoleTextAttribute(*hConsole, 12);
			std::cout << "Error: Value cannot be less than or equal to 0 : ";
			SetConsoleTextAttribute(*hConsole, 15);
		}
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
bool FileExists(std::string fileName) {
	std::ifstream ifile(fileName);
	return ifile.good();
}

/// <summary>
/// Pauses console by waiting for input.
/// </summary>
/// <param name="hConsole"></param>
void Pause(HANDLE* hConsole)
{
	std::cout << "\n";
	SetConsoleTextAttribute(*hConsole, 9);
	std::cout << "Press any key to continue...";
	SetConsoleTextAttribute(*hConsole, 15);
	_getch();
}

/// <summary>
/// Finds number of journeys. Will return could of Travel or Travel and Expense depending on what traveltype is set to.
/// </summary>
/// <param name="vecJourneyCollection"></param>
/// <param name="travelType"></param>
/// <returns></returns>
int FindNumOfJourneys(std::vector<Journey>* vecJourneyCollection, TravelType travelType) {
	// Variable declarations
	int intNumOfJourneys = 0;

	// if travelType is travel, find total number of travel journeys.
	if (travelType == TravelType::Travel) {
		for (size_t i = 0; i < vecJourneyCollection->size(); i++)
		{
			if (vecJourneyCollection->at(i).travelType == TravelType::Travel) {
				intNumOfJourneys++;
			}
		}
	}
	// if travelType is travel and expense, find total number of travel and expense journeys.
	else if (travelType == TravelType::TravelAndExpense)
	{
		for (size_t i = 0; i < vecJourneyCollection->size(); i++)
		{
			if (vecJourneyCollection->at(i).travelType == TravelType::TravelAndExpense) {
				intNumOfJourneys++;
			}
		}
	}

	return intNumOfJourneys;
}