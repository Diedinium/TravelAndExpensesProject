#include "CalcFunctions.h"
#include "OutputFunctions.h"

/// <summary>
/// Prints the intro warning/notice when loading the program.
/// </summary>
/// <param name="hConsole"></param>
void OutputIntro(HANDLE* hConsole) {
	// Notice for users about setup needed to ensure proper formatted output.
	SetConsoleTextAttribute(*hConsole, 12);
	std::cout << "### NOTICE ###\n";
	SetConsoleTextAttribute(*hConsole, 14);
	std::cout << "To ensure proper text formatting while in use, please make sure you widen the console window. ";
	std::cout << "You can do this by dragging the window larger or by right clicking on the top of this window then go to properties, ";
	std::cout << "and the layout tab. Setting the console width to 127 is recommended. Not doing this could result in text being wrapped ";
	std::cout << "ruining some of the output tables.\n";
	SetConsoleTextAttribute(*hConsole, 12);
	std::cout << "### NOTICE ###\n";
	SetConsoleTextAttribute(*hConsole, 15);

	Pause(hConsole);
}

void OutputMenu(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, std::vector<ChoiceOption>* vecChoiceCollection, std::string introText, bool boolUseDashes, bool boolClearScreen) {
	if (boolClearScreen) {
		system("cls");
	}
	SetConsoleTextAttribute(*hConsole, 6);
	if (boolUseDashes) {
		std::cout << "-------------------------------------------\n";
	}
	SetConsoleTextAttribute(*hConsole, 15);
	std::cout << "\n";
	SetConsoleTextAttribute(*hConsole, 14);
	std::cout << introText;
	std::cout << "\nPlease specify your option :\n";
	std::cout << "\n";
	SetConsoleTextAttribute(*hConsole, 15);
	for (size_t i = 0; i < vecChoiceCollection->size(); i++)
	{
		if (vecChoiceCollection->at(i).OptionHideThreshold != 99) {
			if (vecChoiceCollection->at(i).OptionHideThreshold == 0) {
				if (vecJourneyCollection->size() > vecChoiceCollection->at(i).OptionHideThreshold) {
					SetConsoleTextAttribute(*hConsole, 10);
					std::cout << "Option " << vecChoiceCollection->at(i).OptionNumber << " : ";
					SetConsoleTextAttribute(*hConsole, 15);
					std::cout << vecChoiceCollection->at(i).OptionText << "\n";
				}
			}
			else {
				if (vecJourneyCollection->size() >= vecChoiceCollection->at(i).OptionHideThreshold) {
					SetConsoleTextAttribute(*hConsole, 10);
					std::cout << "Option " << vecChoiceCollection->at(i).OptionNumber << " : ";
					SetConsoleTextAttribute(*hConsole, 15);
					std::cout << vecChoiceCollection->at(i).OptionText << "\n";
				}
			}
		}
		else {
			SetConsoleTextAttribute(*hConsole, 10);
			std::cout << "Option " << vecChoiceCollection->at(i).OptionNumber << " : ";
			SetConsoleTextAttribute(*hConsole, 15);
			std::cout << vecChoiceCollection->at(i).OptionText << "\n";
		}
	}
	std::cout << "\n";
	if (boolUseDashes) {
		SetConsoleTextAttribute(*hConsole, 6);
		std::cout << "-------------------------------------------\n";
		SetConsoleTextAttribute(*hConsole, 15);
	}
}

/// <summary>
/// Outputs standard 7 item header, accepts different titles when header text is set to non-empty value.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="intWidth"></param>
/// <param name="headerText"></param>
void OutputHeader(HANDLE* hConsole, int* intWidth, std::string headerText) {
	// Print header text if set
	if (!headerText.empty()) {
		SetConsoleTextAttribute(*hConsole, 14);
		std::cout << headerText << "\n";
	}
	else {
		// Use default if string is empty
		SetConsoleTextAttribute(*hConsole, 14);
		std::cout << "All Journeys" << "\n";
	}

	// Output standard 7 item header
	SetConsoleTextAttribute(*hConsole, 6);
	std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
	SetConsoleTextAttribute(*hConsole, 13);
	std::cout << std::setw(*intWidth) << "Travel Type" << std::setw(*intWidth) << "Travel Cost" << std::setw(*intWidth) << "Exp Cost" << std::setw(*intWidth) << "Total Cost" << std::setw(*intWidth) << "Exp Payable" << std::setw(*intWidth) << "Tax Reclaim" << std::setw(*intWidth) << "Exp not Cvrd" << std::setw(*intWidth) << "Final Pay\n";
	SetConsoleTextAttribute(*hConsole, 6);
	std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
	SetConsoleTextAttribute(*hConsole, 15);
}

/// <summary>
/// Outputs header variants, overload of OutputHeader. Variants include 1 and 2. 1 is header with number column, 2 is short 4 item header (for travel only items)
/// If header text is set to empty (""), defaults to "All Journeys".
/// </summary>
/// <param name="hConsole"></param>
/// <param name="intWidth"></param>
/// <param name="headerText"></param>
/// <param name="headerType"></param>
void OutputHeader(HANDLE* hConsole, int* intWidth, std::string headerText, int headerType) {
	// Print header text if set
	if (!headerText.empty()) {
		SetConsoleTextAttribute(*hConsole, 14);
		std::cout << headerText << "\n";
	}
	else {
		// Use default if string is empty
		SetConsoleTextAttribute(*hConsole, 14);
		std::cout << "All Journeys" << "\n";
	}
	switch (headerType)
	{
	case 1: {
		// Standard 7 item header with numbers column
		SetConsoleTextAttribute(*hConsole, 6);
		std::cout << "------------------------------------------------------------------------------------------------------------------------------\n";
		SetConsoleTextAttribute(*hConsole, 13);
		std::cout << std::setw(5) << "Number" << std::setw(*intWidth) << "Travel Type" << std::setw(*intWidth) << "Travel Cost" << std::setw(*intWidth) << "Exp Cost" << std::setw(*intWidth) << "Total Cost" << std::setw(*intWidth) << "Exp Payable" << std::setw(*intWidth) << "Tax Reclaim" << std::setw(*intWidth) << "Exp not Cvrd" << std::setw(*intWidth) << "Final Pay\n";
		SetConsoleTextAttribute(*hConsole, 6);
		std::cout << "------------------------------------------------------------------------------------------------------------------------------\n";
		SetConsoleTextAttribute(*hConsole, 15);
		break;
	}
	case 2: {
		// Short 4 item header
		SetConsoleTextAttribute(*hConsole, 6);
		std::cout << "------------------------------------------------------------\n";
		SetConsoleTextAttribute(*hConsole, 13);
		std::cout << std::setw(*intWidth) << "Travel Type" << std::setw(*intWidth) << "Travel Cost" << std::setw(*intWidth) << "Tax Reclaim" << std::setw(*intWidth) << "Final Pay" << "\n";
		SetConsoleTextAttribute(*hConsole, 6);
		std::cout << "------------------------------------------------------------\n";
		SetConsoleTextAttribute(*hConsole, 15);
		break;
	}
	default: {
		SetConsoleTextAttribute(*hConsole, 12);
		std::cout << "Error : Header could not be rendered\n";
		SetConsoleTextAttribute(*hConsole, 15);
		break;
	}
	}
}

/// <summary>
/// Outputs a standard 7 item table with numbering, outputs all journeys passed in vector.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
void OutputTable(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth) {
	// Output standard 7 item table
	if (vecJourneyCollection->size() <= 0) {
		std::cout << "There are currently no stored journeys\n";
	}
	else {
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			std::cout.precision(2);
			SetConsoleTextAttribute(*hConsole, 9);
			std::cout << std::setw(5) << (i + 1);
			std::cout.precision(2);
			SetConsoleTextAttribute(*hConsole, 10);
			std::cout << std::setw(*intWidth) << ((((int)vecJourneyCollection->at(i).travelType) == 0) ? "Travel" : "Travel & Exp");
			std::cout.precision(2);
			SetConsoleTextAttribute(*hConsole, 15);
			std::cout
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

/// <summary>
/// Overload of OutputTable that outputs non standard table variants. Option 1 outputs travel and expense only, option 2 outputs 4 item table (travel only) and option 3 outputs 
/// the same travel only journeys, but with all 7 columns.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="intWidth"></param>
/// <param name="tableType"></param>
void OutputTable(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, int* intWidth, int tableType) {
	switch (tableType)
	{
	case 1: {
		// Output travel and expense journeys only
		if (vecJourneyCollection->size() <= 0) {
			SetConsoleTextAttribute(*hConsole, 12);
			std::cout << "There are currently no stored journeys\n";
			SetConsoleTextAttribute(*hConsole, 15);
		}
		else {
			for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
				if (vecJourneyCollection->at(i).travelType == TravelType::TravelAndExpense) {
					std::cout.precision(2);
					SetConsoleTextAttribute(*hConsole, 10);
					std::cout << std::setw(*intWidth) << ((((int)vecJourneyCollection->at(i).travelType) == 0) ? "Travel" : "Travel & Exp");
					std::cout.precision(2);
					SetConsoleTextAttribute(*hConsole, 15);
					std::cout
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
		break;
	}
	case 2: {
		// Output travel journeys only
		if (vecJourneyCollection->size() <= 0) {
			SetConsoleTextAttribute(*hConsole, 12);
			std::cout << "There are currently no stored journeys\n";
			SetConsoleTextAttribute(*hConsole, 15);
		}
		else {
			for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
				if (vecJourneyCollection->at(i).travelType == TravelType::Travel) {
					std::cout.precision(2);
					SetConsoleTextAttribute(*hConsole, 10);
					std::cout << std::setw(*intWidth) << ((((int)vecJourneyCollection->at(i).travelType) == 0) ? "Travel" : "Travel & Exp");
					std::cout.precision(2);
					SetConsoleTextAttribute(*hConsole, 15);
					std::cout
						<< std::setw(*intWidth) << std::fixed << vecJourneyCollection->at(i).travelCost
						<< std::setw(*intWidth) << std::fixed << vecJourneyCollection->at(i).taxReclaim
						<< std::setw(*intWidth) << std::fixed << vecJourneyCollection->at(i).finalPayment << "\n";
				}
			}
		}
		break;
	}
	case 3: {
		// Output travel journeys only, but all 7 columns
		if (vecJourneyCollection->size() <= 0) {
			SetConsoleTextAttribute(*hConsole, 12);
			std::cout << "There are currently no stored journeys\n";
			SetConsoleTextAttribute(*hConsole, 15);
		}
		else {
			for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
				if (vecJourneyCollection->at(i).travelType == TravelType::Travel) {
					std::cout.precision(2);
					SetConsoleTextAttribute(*hConsole, 10);
					std::cout << std::setw(*intWidth) << ((((int)vecJourneyCollection->at(i).travelType) == 0) ? "Travel" : "Travel & Exp");
					std::cout.precision(2);
					SetConsoleTextAttribute(*hConsole, 15);
					std::cout
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
		break;
	}
	default: {
		SetConsoleTextAttribute(*hConsole, 12);
		std::cout << "Error : Table could not be rendered\n";
		SetConsoleTextAttribute(*hConsole, 15);
		break;
	}
	}
}