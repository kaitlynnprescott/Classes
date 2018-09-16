/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Katie Prescott
 * Date        : February 22, 2016
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

// create vector of vectors
vector< vector<int> > outer;
vector<int> inner;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

	if (num_stairs <= 0)
	{
		outer.push_back(inner);
	}
	// are the number of stairs greater than or equal to 1?
		// can we go up 1 at a time?
	if (num_stairs >= 1)
	{
		// go up 1 stair
		inner.push_back(1);
		// recursive call
		get_ways(num_stairs - 1);
		// go back to previous number to move on
		inner.pop_back();
	}
	// are the number of stairs greater than or equal to 2?
		// can we go up 2 at a time?
	if (num_stairs >= 2)
	{
		// go up 2
		inner.push_back(2);
		// recursive call
		get_ways(num_stairs - 2);
		// go back to previous number to move on
		inner.pop_back();
	}
	// are the number of stairs greater than or equal to 3?
		// can we go up 3 at a time?
	if (num_stairs >= 3)
	{
		// go up 1
		inner.push_back(3);
		// recursive call
		get_ways(num_stairs - 3);
		// go back to previous number to move on
		inner.pop_back();
	}
	return outer;
}

int num_digits(int num) {
        // : write code to determine how many digits are in an integer
        // Hint: No strings are needed. Keep dividing by 10.

    	// set number of digits to 0
    	int digits = 0;
    	// as long as the number given is greater than 1
    	while (num >= 1)
    	{
    		// divide the number by 10
    		num = num / 10;
    		// add one to digits, takes away one place
    		digits++;
    	}
    	// returns the number of digits in a number
    	return digits;
    }

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.

	// go through each vector in the vector of vectors
	for (unsigned int i = 0; i < ways.size(); i++)
	{

		cout << setw(num_digits(ways.size()));
		// way number, with bracket
		cout << i + 1 << ". " << "[";
		// go into vector at i
		for (unsigned int j = 0; j < ways[i].size(); j++)
		{
			// check if its larger than 1 element
			if (j != ways[i].size() - 1)
			{
				// if so, print with a comma
				cout << ways[i][j] << ", ";
			}
			else
			{
				// if not, print without a comma
				cout << ways[i][j];
			}
		}
		// print end bracket, end line.
		cout << "]" << endl;
	}
}

int main(int argc, char * const argv[]) {
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
		return 1;
	}
	int a;

	istringstream iss(argv[1]);
	if (!(iss >> a))
	{
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	if (a <= 0)
	{
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	vector< vector<int> > ways = get_ways(a);
	int size = ways.size();

	if (size == 1)
	{
		cout << size << " way to climb " << a << " stair." << endl;
		display_ways(ways);
	}
	else
	{
		cout << size << " ways to climb " << a << " stairs." << endl;
		display_ways(ways);
	}

}
