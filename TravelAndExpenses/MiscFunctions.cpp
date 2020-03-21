#include "MiscFunctions.h"

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

void Pause(HANDLE* hConsole)
{
	std::cout << "\n";
	SetConsoleTextAttribute(*hConsole, 9);
	std::cout << "Press any key to continue...";
	SetConsoleTextAttribute(*hConsole, 15);
	_getch();
}