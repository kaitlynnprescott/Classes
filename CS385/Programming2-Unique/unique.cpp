/*******************************************************************************
 * Name        : unique.cpp
 * Author      :
 * Date        :
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      :
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.

	// set low = true, this is the boolean value to be returned
	bool low = true;
	// for loop from first letter to last letter of the string
	for (int i = 0; i <= s.length(); i++)
	{
		// check if its a number
		if (isdigit(s[i]))
		{
			low = false;
			break;
		}
		// check if its a letter
		if(isalpha(s[i]))
		{
			// check if its a lowercase
			if(!(islower(s[i])))
			{
				// if not, its false, break from the loop.
				low = false;
				break;
			}
		}

	}
	// return low
	return low;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.

	// assume that all letters are unique.
	bool is_true = true;
	// create a bitset of 32 bits called letters
	int letters = 0; //32 zeros
	// loop through the string
	for (int i= 0; i <= s.length(); i++)
	{
		// find how many 0s to pad the bitset with
		int pad = s[i] - 97,
				// pad the bitset and & with 1 to see if there have been any of that letter
			d = (letters >> pad) & 1;
		// if there has been that letter
		if (d == 1)
		{
			// not unique-- change to false, break from loop
			is_true = false;
			break;
		}
		if (d == 0)
		{
			d = d | 1;
			letters = (d << pad) | letters;
		}



	}
	return is_true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

	if (argc != 2)
	{
		// check Case 1: No input arguments and Case 2: Too many input arguments
		cerr << "Usage: " << argv[0] << " <string>" << endl;
		return 1;
	}

	if (!(is_all_lowercase(argv[1])))
	{
		// check Case 3: Bad input (capitals) and Case 4: Bad input (numbers)
		cerr << "Error: String must contain only lowercase letters." << endl;
		return 1;
	}

	if (all_unique_letters(argv[1]))
	{
		// check Case 5: Unique
		cout << "All letters are unique." << endl;
		return 0;
	}
	if (!all_unique_letters(argv[1]))
	{
		// check Case 6: Duplicates
		cout << "Duplicate letters found." << endl;
		return 1;
	}
}



