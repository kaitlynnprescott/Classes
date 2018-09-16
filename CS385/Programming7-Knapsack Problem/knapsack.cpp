/*******************************************************************************
 * Name        : knapsack.cpp
 * Author      : Katie Prescott
 * Date        : May 1, 2016
 * Description : Uses dynamic programming to solve the 0-1 Knapsack Problem.
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ******************************************************************************/
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cctype>
#include <cstring>


using namespace std;


struct Item {
	unsigned int item_number, weight, value;
	string description;

	explicit Item(const unsigned int item_number,
				  const unsigned int weight,
				  const unsigned int value,
				  const string &description) :
						 item_number(item_number),
						 weight(weight),
						 value(value),
						 description(description) { }

	friend std::ostream& operator<<(std::ostream& os, const Item &item)
	{
		os << "Item " << item.item_number << ": " << item.description
				<< " (" << item.weight
				<< (item.weight == 1 ? " pound" : " pounds") << ", $"
				<< item.value << ")";
		os.flush();
		return os;
	}
};

/*
 * Prints all items in vector
 * Input:
 * vector<Item> items	vector of items that can be placed in the knapsack
 * int cap				capacity of the knapsack
 * Output: 	the candidate items that can be placed in the knapsack
 * 			the max capacity of the knapsack
 */
void display_items(vector<Item> items, int cap) {
    // : Display the items by iterating over
    // the vector of vectors and printing each item.

	cout << "Candidate items to place in knapsack:" << endl;

	// loop through the vector of items
	for (unsigned int i = 0; i < items.size(); i++)
	{
		// print each item
		cout << "   " << items[i] << endl;
	}
	// print out the maximum capacity for your knapsack
	cout << "Capacity: " << cap << (cap == 1 ? " pound" : " pounds") << endl;
}

/*
 * Prints items that should be put in the knapsack
 * Input:
 * vector<Item> items	items to be put in the knapsack
 * Output:	the items that should be placed in the knapsack
 * 			the total weight of the knapsack
 * 			the total value of the knapsack
 */
void display_soln(vector<Item> items)
{
	// keep track of weight
	unsigned int weight = 0;
	// keep track of value
	unsigned int value = 0;

	cout << "Items to place in knapsack:" << endl;

	for (int i = items.size() - 1; i >= 0; i--)
	{
		// increase weight
		weight += items[i].weight;
		// increase value
		value += items[i].value;
		// print out item
		cout << "   " << items[i] << endl;
	}
	// print out total weight and value of knapsack
	cout << "Total weight: " << weight << (weight == 1 ? " pound" : " pounds") << endl;
	cout << "Total value : $" << value << endl;
}

/*
 * Returns the items that are included in the solution
 * Input:
 * vector< vector<int> > K	a 2D vector of the knapsack
 * vector<Item> items		items for the knapsack
 * int cap					capacity
 * Output:	items placed in the knapsack
 */
void get_solution(int** K, vector<Item> items, int cap)
{
	// new vector to hold solution
	vector<Item> soln;
	// set j to be the capacity of the knapsack
	int j = cap;
	// set i to be the size of vector K
	int i = items.size();

	while (i > 0 && j > 0)
	{
		if (K[i][j] > K[i-1][j])
		{
			//include item i
			// put the item into the solution vector
			soln.push_back(items[i-1]);
			// subtract the weight of that item from the total capacity
			j -= items[i-1].weight;
			// move to next row
			i--;
		}
		else
		{
			// don't include item i
			i--;
		}
	}
	// display the items used for the solution
	display_soln(soln);
}

/*
 * Solves knapsack problem with dynamic programming
 * Input:
 * int cap				capacity
 * vector<Item> items	items for the knapsack
 * Output:	value of the items in the table
 */
void knapsack(int cap, vector<Item> items)
{
	// assign n to be size of vector of items
	unsigned int n = items.size();
	// hold cap in capacity
	unsigned int capacity = cap;
	// create a 2D array
	int **K = new int*[n + 1];

	// Build K[][]
	for (unsigned int i = 0; i < n + 1; i++)
	{
		// fill K[i]
		K[i] = new int[cap + 1];

		for (unsigned int j = 0; j < capacity + 1; j++)
		{
			// pad array with 0s
			if (i == 0 || j == 0)
			{
				K[i][j] = 0;
			}
			// build up array
			else
			{
				// if the weight is less than or equal to the capacity
				if (j < items[i - 1].weight)
				{
					K[i][j] = K[i-1][j];
				}
				// item i is too heavy
				else
				{
					// use_it means we take item i
					int use_it = items[i - 1].value + K[i-1][j-items[i-1].weight];
					// lose_it means we skip item i
					int lose_it = K[i-1][j];

					// only take item i if use_it is greater than lose_it
					if (use_it > lose_it)
					{
						K[i][j] = use_it;
					}
					else
					{
						K[i][j] = lose_it;
					}
				}
			}
		}
	}
	 get_solution(K, items, cap);

	 // delete the 2D array
	 for (unsigned int x = 0; x < items.size() + 1; x++)
	 {
		 delete[] K[x];
	 }
	 delete[] K;
}


int main(int argc, char * const argv[])
{

	// too many or not enough arguments
	if (argc != 3)
	{
		cout << "Usage: ./knapsack <capacity> <filename>" << endl;
		return 1;
	}

	// invalid capacity (non positive numbers)
	istringstream iss(argv[1]);
	int cap;
	if (!(iss >> cap))
	{
		cerr << "Error: Bad value '" << argv[1] << "' for capacity." << endl;
		return 1;
	}
	if (cap <= 0)
	{
		cerr << "Error: Bad value '" << cap << "' for capacity." << endl;
		return 1;
	}

	// Create an ifstream object.
    ifstream input_file(argv[2]);
    // If it does not exist, print an error message.
    if (!(input_file.is_open()))
    {
        cerr << "Error: Cannot open file '" << argv[2] << "'." << endl;
        return 1;
    }


    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    int weight;
    int value;
    int index = 0;
    string description;
    string temp;
    vector<Item> list;
    stringstream ss;
    unsigned int line_number = 1;
    try
    {
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        while (getline(input_file, line))
        {
        	temp = line;
        	// check line has 3 fields.
        	if ((index = temp.find(",")) == -1)
        	{
        		cerr << "Error: Line number " << line_number << " does not contain 3 fields." << endl;
        		return 1;
        	}

        	temp.erase(0, index + 1);

        	if ((index = temp.find(",")) == -1)
        	{
        		cerr << "Error: Line number " << line_number << " does not contain 3 fields." << endl;
        		return 1;
        	}

        	temp.erase(0, index + 1);

        	if ((index = temp.find(",")) > -1)
        	{
        		cerr << "Error: Line number " << line_number << " does not contain 3 fields." << endl;
        		return 1;
        	}

        	index = line.find(",");
        	description = line.substr(0, index);
        	line.erase(0, index + 1);
        	index = line.find(",");
        	temp = line.substr(0, index);
        	ss << temp;

        	// check weight == int
        	if (!(ss >> weight) || weight <= 0)
        	{
        		cerr << "Error: Invalid weight '" << temp << "' on line number " << line_number << "." << endl;
        		return 1;
        	}

        	ss.clear();
        	line.erase(0, index + 1);
        	temp = line;
        	ss << temp;

        	// check value == int
        	if (!(ss >> value) || value < 0)
        	{
        		cerr << "Error: Invalid value '" << temp << "' on line number " << line_number << "." << endl;
        		return 1;
        	}

        	ss.clear();
        	Item item(line_number, weight, value, description);
        	list.push_back(item);
            ++line_number;
        }
        // Don't forget to close the file.
        input_file.close();
    }
    catch (const ifstream::failure &f)
    {
        cerr << "Error: Cannot open file '" << argv[1] << "'.";
        return 1;
    }

    display_items(list, cap);
    knapsack(cap, list);
    return 0;

}
