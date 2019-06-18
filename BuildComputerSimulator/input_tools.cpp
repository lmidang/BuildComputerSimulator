#include "input_tools.h"

// Let the user input a string
string inputString(bool allowEmptyString, string prefix) {
	string input;
	bool exit = false;

	while (!exit) {
		cout << prefix;
		getline(cin, input);
		cout << endl;

		// Make sure the user inputs something
		if (input == "" && !allowEmptyString)
			cerr << "You did not input anything!\n\n";
		else
			exit = true;
	}

	return input;
}

// Let the user input a number within a specified range
double inputNumber(double min, double max, string prefix) {
	string input;
	double num;
	bool exit = false;

	while (!exit) {
		input = inputString(false, prefix);

		try {
			num = stod(input);

			// Make sure the number is within the specified range
			if (num < min || num > max) {				
				if (min == -DBL_MAX && max != DBL_MAX)
					cerr << "Input must be less than or equal to " << max << "!\n\n";
				else if (min != -DBL_MAX && max == DBL_MAX)
					cerr << "Input must be greater than or equal to " << min << "!\n\n";
				else
					cerr << "Input must be between " << min << " and " << max << "!\n\n";
			}
			else
				exit = true;
		}
		// Make sure the input is a valid number
		catch (const invalid_argument &ia) {
			cerr << ia.what() << "; You must enter a number!\n\n";
		}
	}

	return num;
}