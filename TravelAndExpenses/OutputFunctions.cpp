#include "Structs.h"
#include "MiscFunctions.h"
#include "CalcFunctions.h"
#include "OutputFunctions.h"

/// <summary>
/// Prints the intro warning/notice when loading the program.
/// </summary>
/// <param name="hConsole"></param>
void OutputIntro(HANDLE* hConsole) {
	SetConsoleTextAttribute(*hConsole, 12);
	std::cout << "### NOTICE ###\n";
	SetConsoleTextAttribute(*hConsole, 14);
	std::cout << "Any files created/interacted with during the use of this program are saved in the same directory that you have run this application from. ";
	std::cout << "The console window should have automatically resized itself to be the correct size, if not, please drag the console window wider so that ";
	std::cout << "output tables within the application display correctly.\n";
	SetConsoleTextAttribute(*hConsole, 12);
	std::cout << "### NOTICE ###\n";
	SetConsoleTextAttribute(*hConsole, 15);

	Pause(hConsole);
}

/// <summary>
/// Takes a list of ChoiceOptions, introText and options to use dashes and clear screen. Based on these options, menu screen choices are output.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="vecJourneyCollection"></param>
/// <param name="vecChoiceCollection"></param>
/// <param name="introText"></param>
/// <param name="boolUseDashes"></param>
/// <param name="boolClearScreen"></param>
void OutputMenu(HANDLE* hConsole, std::vector<Journey>* vecJourneyCollection, std::vector<ChoiceOption>* vecChoiceCollection, std::string introText, bool boolUseDashes, bool boolClearScreen) {
	// Clears screen if boolClearScreen is true.
	if (boolClearScreen) {
		system("cls");
	}

	// Dashes are displayed when boolUseDashes is true.
	SetConsoleTextAttribute(*hConsole, 6);
	if (boolUseDashes) {
		std::cout << "-------------------------------------------\n";
	}
	SetConsoleTextAttribute(*hConsole, 15);
	std::cout << "\n";
	
	// Intro text is displayed.
	SetConsoleTextAttribute(*hConsole, 14);
	std::cout << introText;
	std::cout << "\nPlease specify your option :\n";
	std::cout << "\n";

	// Outputs choice options
	SetConsoleTextAttribute(*hConsole, 15);
	for (size_t i = 0; i < vecChoiceCollection->size(); i++)
	{
		// If hide threshold is not default value.
		if (vecChoiceCollection->at(i).OptionHideThreshold != 99) {
			// If option should be hidden when not greater than 0
			if (vecChoiceCollection->at(i).OptionHideThreshold == 0) {
				// Ouputs option if vector size is greater than the option threshold (0)
				if (vecJourneyCollection->size() > vecChoiceCollection->at(i).OptionHideThreshold) {
					SetConsoleTextAttribute(*hConsole, 10);
					std::cout << "Option " << vecChoiceCollection->at(i).OptionNumber << " : ";
					SetConsoleTextAttribute(*hConsole, 15);
					std::cout << vecChoiceCollection->at(i).OptionText << "\n";
				}
			}
			// For all other choice options that need to be hidden when not greater than or equal to specified hide threshold
			else {
				// Outputs option if vector size is greater than or equal to threshold (1 and above)
				if (vecJourneyCollection->size() >= vecChoiceCollection->at(i).OptionHideThreshold) {
					SetConsoleTextAttribute(*hConsole, 10);
					std::cout << "Option " << vecChoiceCollection->at(i).OptionNumber << " : ";
					SetConsoleTextAttribute(*hConsole, 15);
					std::cout << vecChoiceCollection->at(i).OptionText << "\n";
				}
			}
		}
		// Default output for options that are always visible regardless of number of journeys.
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
		OutputError(hConsole, "Header could not be rendered.");
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
		OutputError(hConsole, "There are currently no stored journeys");
	}
	else {
		for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
			// Output numbering
			std::cout.precision(2);
			SetConsoleTextAttribute(*hConsole, 9);
			std::cout << std::setw(5) << (i + 1);
			// Output travel type
			std::cout.precision(2);
			SetConsoleTextAttribute(*hConsole, 10);
			std::cout << std::setw(*intWidth) << ((((int)vecJourneyCollection->at(i).travelType) == 0) ? "Travel" : "Travel & Exp");
			// Output other 7 values.
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
			OutputError(hConsole, "There are currently no stored journeys");
		}
		else {
			for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
				if (vecJourneyCollection->at(i).travelType == TravelType::TravelAndExpense) {
					// Output travel type
					std::cout.precision(2);
					SetConsoleTextAttribute(*hConsole, 10);
					std::cout << std::setw(*intWidth) << ((((int)vecJourneyCollection->at(i).travelType) == 0) ? "Travel" : "Travel & Exp");
					// Output other 7 values.
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
			OutputError(hConsole, "There are currently no stored journeys");
		}
		else {
			for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
				if (vecJourneyCollection->at(i).travelType == TravelType::Travel) {
					// Output travel type
					std::cout.precision(2);
					SetConsoleTextAttribute(*hConsole, 10);
					std::cout << std::setw(*intWidth) << ((((int)vecJourneyCollection->at(i).travelType) == 0) ? "Travel" : "Travel & Exp");
					// Output other 7 values.
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
			OutputError(hConsole, "There are currently no stored journeys");
		}
		else {
			for (std::size_t i = 0; i < vecJourneyCollection->size(); ++i) {
				if (vecJourneyCollection->at(i).travelType == TravelType::Travel) {
					// Output travel type
					std::cout.precision(2);
					SetConsoleTextAttribute(*hConsole, 10);
					std::cout << std::setw(*intWidth) << ((((int)vecJourneyCollection->at(i).travelType) == 0) ? "Travel" : "Travel & Exp");
					// Output other 7 values.
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
		OutputError(hConsole, "Table could not be rendered");
		break;
	}
	}
}

/// <summary>
/// Outputs results for travel only items. resultType specifies the type of comparison, for example; total, difference, average.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="resultTravel"></param>
/// <param name="intWidth"></param>
/// <param name="resultType"></param>
void OutputResults(HANDLE* hConsole, ResultTravel* resultTravel, int* intWidth, std::string strResultType) {
	// Add colon to result type
	strResultType += " :";
	std::cout << "\n";
	// Output result type.
	std::cout.precision(2);
	SetConsoleTextAttribute(*hConsole, 13);
	std::cout << std::fixed << std::setw(*intWidth) << strResultType;
	// Output result values
	std::cout.precision(2);
	SetConsoleTextAttribute(*hConsole, 15);
	std::cout
		<< std::fixed << std::setw(*intWidth) << resultTravel->Travel
		<< std::fixed << std::setw(*intWidth) << resultTravel->TaxReclaim
		<< std::fixed << std::setw(*intWidth) << resultTravel->FinalPay << "\n";
}

/// <summary>
/// Outputs results for travel and expense. resultType specifies the type of comparison, for example; total, difference, average.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="resultTravelExpense"></param>
/// <param name="intWidth"></param>
/// <param name="resultType"></param>
void OutputResults(HANDLE* hConsole, ResultTravelExpense* resultTravelExpense, int* intWidth, std::string strResultType) {
	// Add colon to result type
	strResultType += " :";
	std::cout << "\n";
	// Output result type.
	std::cout.precision(2);
	SetConsoleTextAttribute(*hConsole, 13);
	std::cout << std::fixed << std::setw(*intWidth) << strResultType;
	// Output result values
	std::cout.precision(2);
	SetConsoleTextAttribute(*hConsole, 15);
	std::cout
		<< std::fixed << std::setw(*intWidth) << resultTravelExpense->Travel
		<< std::fixed << std::setw(*intWidth) << resultTravelExpense->Expense
		<< std::fixed << std::setw(*intWidth) << resultTravelExpense->Totals
		<< std::fixed << std::setw(*intWidth) << resultTravelExpense->ExpensePay
		<< std::fixed << std::setw(*intWidth) << resultTravelExpense->TaxReclaim
		<< std::fixed << std::setw(*intWidth) << resultTravelExpense->ExpenseNotCovered
		<< std::fixed << std::setw(*intWidth) << resultTravelExpense->FinalPay << "\n";
}

/// <summary>
/// Outputs results for travel and expense, but spaced differently for when numbered table/header is used.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="resultTravelExpense"></param>
/// <param name="intWidth"></param>
/// <param name="strResultType"></param>
/// <param name="boolIsNumbered"></param>
void OutputResults(HANDLE* hConsole, ResultTravelExpense* resultTravelExpense, int* intWidth, std::string strResultType, bool boolIsNumbered) {
	// Add colon to result type
	strResultType += " :";
	std::cout << "\n";
	// Output result type.
	std::cout.precision(2);
	SetConsoleTextAttribute(*hConsole, 13);
	std::cout << std::fixed << std::setw(20) << strResultType;
	// Output result values
	std::cout.precision(2);
	SetConsoleTextAttribute(*hConsole, 15);
	std::cout
		<< std::fixed << std::setw(*intWidth) << resultTravelExpense->Travel
		<< std::fixed << std::setw(*intWidth) << resultTravelExpense->Expense
		<< std::fixed << std::setw(*intWidth) << resultTravelExpense->Totals
		<< std::fixed << std::setw(*intWidth) << resultTravelExpense->ExpensePay
		<< std::fixed << std::setw(*intWidth) << resultTravelExpense->TaxReclaim
		<< std::fixed << std::setw(*intWidth) << resultTravelExpense->ExpenseNotCovered
		<< std::fixed << std::setw(*intWidth) << resultTravelExpense->FinalPay << "\n";
}

/// <summary>
/// Outputs an error to the console.
/// </summary>
/// <param name="hConsole"></param>
/// <param name="strErrorText"></param>
void OutputError(HANDLE* hConsole, std::string strErrorText) {
	SetConsoleTextAttribute(*hConsole, 12);
	std::cout << "Error : " << strErrorText << "\n";
	SetConsoleTextAttribute(*hConsole, 15);
}

/// <summary>
/// Outputs an error to the console, when boolNewLine is true, extra new line is added. Without, error is inline (no ending newline);
/// </summary>
/// <param name="hConsole"></param>
/// <param name="strErrorText"></param>
/// <param name="boolNewLine"></param>
void OutputError(HANDLE* hConsole, std::string strErrorText, bool boolNewLine) {
	if (boolNewLine) {
		std::cout << "\n";
	}
	SetConsoleTextAttribute(*hConsole, 12);
	std::cout << "Error : " << strErrorText << (boolNewLine ? "\n" : "");
	SetConsoleTextAttribute(*hConsole, 15);
}