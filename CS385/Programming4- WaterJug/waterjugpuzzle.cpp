/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Katie Prescott, collaborated with Carla Noshi
 * Date        : March 9, 2016
 * Description : Solve the famous water jug puzzle using breadth-first search.
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ******************************************************************************/
#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <sstream>


using namespace std;

int cap_a, cap_b, cap_c;
int goal[2];
string text;
bool success = 0;

// class to represent what state its in
class State
{
private:
	int currA, currB, currC;
	vector<string> steps;


public:
	// Constructor
	State(int a, int b, int c, vector<string> adj)
	{
		currA = a;
		currB = b;
		currC = c;
		steps = adj;
	}

	// getter for steps
	vector<string> get_steps()
	{
		return steps;
	}

	// print the steps out
	void printSteps()
	{
		for (unsigned int i = 0; i < steps.size(); i++)
		{
			cout << steps[i] << endl;
		}
	}

	// getters for a, b, c
	int getA()
	{
		return currA;
	}

	int getB()
	{
		return currB;
	}

	int getC()
	{
		return currC;
	}

};

// function to check if a certain state is the goal state
bool goal_check(int a, int b)
{
	if ((a == goal[0]) && (b == goal[1]))
	{
		return true;
	}
	return false;
}

// function to generate next steps
vector<string> generate_steps(int a, int b, int c)
{
	vector<string> steps;
	stringstream iss;
	iss << "Initial state. (" << a << ", " << b << ", " << c << ")";
	steps.push_back(iss.str());
	return steps;
}

// function to build the string up
string build(int a, int b, int c)
{
	string new_string;
	stringstream iss;
	iss << "(" << a << ", " << b << ", " << c << ")";
	new_string = iss.str();
	return new_string;
}

// initialize a queue of states.
queue<State> q;

// Breadth First Search algorithm
void bfs(int currA, int currB, int currC)
{
	// initialize boolean array to see if a state has been visited or not.
	bool **visited = new bool*[cap_a + 1];
	for (int i = 0; i < cap_a + 1; i++)
	{
		// make it a 2D array
		visited[i] = new bool[cap_b + 1];
		// fill with falses
		fill(visited[i], visited[i] + cap_b + 1, false);
	}
	// instantiating the current state
	State states(currA, currB, currC, generate_steps(currA, currB, currC));
	q.push(states);
	while (!q.empty())
	{
		// inserting data from current state
		currA = q.front().getA();
		currB = q.front().getB();
		currC = q.front().getC();

		// show its been visited
		visited[currA][currB] = true;

		// check if its the goal state
		if (goal_check(currA, currB))
		{
			// print out the queue
			q.front().printSteps();
			// show it was successful, and done.
			success = 1;
			break;
		}

		// pop the current state from the queue
		State first = q.front();
		q.pop();

		// pouring C to A
		if (currA < cap_a)
		{
			// pour into a
			// change a, b, and c as needed (capacity, 0, etc)
			int a = currA + currC;
			int b = currB;
			if (a > cap_a)
			{
				a = cap_a;
			}
			int c = currC - (a - currA);
			if (b > cap_b)
			{
				b = cap_b;
			}
			// save the step
			stringstream iss;
			if((a - currA) > 1)
			{
				iss << a - currA;
				text = "Pour " + iss.str() + " gallons from C to A. ";
			}
			else
			{
				iss << a - currA;
				text = "Pour" + iss.str() + " gallon from C to A. ";
			}
			// check if its been visited, if not:
			if (!visited[a][b])
			{
				// push step onto vector (path) of steps
				vector<string> path = first.get_steps();
				path.push_back(text + build(a, b, c));
				State c_to_a(a, b, c, path);
				q.push(c_to_a);
			}
		}

		// pouring B to A
		if (currA < cap_a)
		{
			// make sure b isn't empty
			if (currB != 0)
			{
				// pour into a
				// change a, b, and c as needed (capacity, 0, etc.)
				int c = currC;
				int a = currA + currB;
				if (a > cap_a)
				{
					a = cap_a;
				}
				int b = currB - (a - currA);
				if (b < 0)
				{
					b = 0;
				}
				if (b > cap_b)
				{
					b = cap_b;
				}
				// save step
				stringstream iss;
				if((currB - b) > 1)
				{
					iss << currB - b;
					text = "Pour " + iss.str() + " gallons from B to A. ";
				}
				else
				{
					iss << currB - b;
					text = "Pour " + iss.str() + " gallon from B to A. ";
				}
				// check if its been visited, if not:
				if (!visited[a][b])
				{
					// push step to vector (path) of steps
					vector<string> path = first.get_steps();
					path.push_back(text + build(a, b, c));
					State b_to_a(a, b, c, path);
					q.push(b_to_a);
				}
			}
		}

		// pouring C to B
		if (currB < cap_b)
		{
			// pour into b
			// change a, b, and c as needed (capacity, 0, etc)
			int b = currB + currC;
			int a = currA;
			if (b > cap_b)
			{
				b = cap_b;
			}
			int c = currC - (b - currB);
			if (a > cap_a)
			{
				a = cap_a;
			}
			// save the step
			stringstream iss;
			if((b - currB) > 1)
			{
				iss << b - currB;
				text = "Pour " + iss.str() + " gallons from C to B. ";
			}
			else
			{
				iss << b - currB;
				text = "Pour " + iss.str() + " gallon from C to B. ";
			}
			// check if step has been visited, if not:
			if (!visited[a][b])
			{
				// push step onto vector (path) of steps
				vector<string> path = first.get_steps();
				path.push_back(text + build(a, b, c));
				State c_to_b(a, b, c, path);
				q.push(c_to_b);
			}
		}

		// pouring A to B
		if (currB < cap_b)
		{
			// make sure a isn't empty
			if (currA != 0)
			{
				// pour into b
				// change a, b, and c as needed (capacity, 0, etc.)
				int c = currC;
				int a;
				int b = currA + currB;
				if (b > cap_b)
				{
					b = cap_b;
					a = currA - (b - currB);
				}
				else
				{
					a = 0;
				}
				if (a < 0)
				{
					a = 0;
				}
				if (a > cap_a)
				{
					a = cap_a;
				}
				// save the step
				stringstream iss;
				if((b - currB) > 1)
				{
					iss << b - currB;
					text = "Pour " + iss.str() + " gallons from A to B. ";
				}
				else
				{
					iss << b - currB;
					text = "Pour " + iss.str() + " gallon from A to B. ";
				}
				// check if its been visited, if not:
				if (!visited[a][b])
				{
					// push the step onto the vector (path) of steps
					vector<string> path = first.get_steps();
					path.push_back(text + build(a, b, c));
					State a_to_b(a, b, c, path);
					q.push(a_to_b);
				}
			}
		}

		// pouring B to C
		if (currA + currB < cap_c)
		{
			// make sure b isn't empty
			if (currB != 0)
			{
				// pour into c
				// change a, b, and c as needed (capacity, 0, etc)
				int c = currC + currB;
				if (c > cap_c)
				{
					c = cap_c;
				}
				int b = currC - c;
				int a = currA;
				if (b > cap_b)
				{
					b = cap_b;
				}
				if (b < 0)
				{
					b = 0;
				}
				if (a > cap_a)
				{
					a = cap_a;
				}
				// save the step
				stringstream iss;
				if((currB - b) > 1)
				{
					iss << currB - b;
					text = "Pour " + iss.str() + " gallons from B to C. ";
				}
				else
				{
					iss << currB - b;
					text = "Pour " + iss.str() + " gallon from B to C. ";
				}
				// check if its been visited
				if (!visited[a][b])
				{
					// push the step onto the vector (path) of steps
					vector<string> path = first.get_steps();
					path.push_back(text + build(a, b, c));
					State b_to_c(a, b, c, path);
					q.push(b_to_c);
				}
			}
		}

		// pouring A to C
		if (currA + currB < cap_c)
		{
			// make sure a isn't empty
			if (currA != 0)
			{
				// pour into c
				// change a, b, and c as needed (capacity, 0, etc.)
				int c = currC + currA;
				if (c > cap_c)
				{
					c = cap_c;
				}
				int a = currA - (c - currC);
				if (a > cap_a)
				{
					a = cap_a;
				}
				if (a < 0)
				{
					a = 0;
				}
				int b = currB;
				// save the step
				stringstream iss;
				if((currA - a) > 1)
				{
					iss << currA - a;
					text = "Pour " + iss.str() + " gallons from A to C. ";
				}
				else
				{
					iss << currA - a;
					text = "Pour " + iss.str() + " gallon from A to C. ";
				}
				// check if its been visited
				if (!visited[a][b])
				{
					// push the step onto the vector (path) of steps
					vector<string> path = first.get_steps();
					path.push_back(text + build(a, b, c));
					State a_to_c(a, b, c, path);
					q.push(a_to_c);
				}
			}
		}
	}

	// if a success is not found, print out no solution
	if (!success)
	{
		cout << "No solution." << endl;
	}

	// delete from memory
	for (int i = 0; i <= cap_a; i++)
	{
		delete [] visited[i];
	}

	delete [] visited;
}


int main(int argc, char * const argv[])
{
	// check it takes in required number of arguments
	if (argc != 7)
	{
		cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}
	// check for valid inputs
	for (int i = 0; i <= 6; i++)
	{
		int temp;
		istringstream iss(argv[i]);
		// if arg not #, or a -#, or the cap_c = 0 gallons
		if (!(iss >> temp) || (temp < 0) || (temp == 0 && i == 3))
		{
			// capacity for jug A
			if (i == 1)
			{
				cerr << "Error: Invalid capacity '" << argv[i] << "' for jug A." << endl;
				return 1;
			}
			// cap for jug B
			if (i == 2)
			{
				cerr << "Error: Invalid capacity '" << argv[i] << "' for jug B." << endl;
				return 1;
			}
			// cap for jug C
			if (i == 3)
			{
				cerr << "Error: Invalid capacity '" << argv[i] << "' for jug C." << endl;
				return 1;
			}
			// goal for jug A
			if (i == 4)
			{
				cerr << "Error: Invalid goal '" << argv[i] << "' for jug A." << endl;
				return 1;
			}
			// goal for jug B
			if (i == 5)
			{
				cerr << "Error: Invalid goal '" << argv[i] << "' for jug B." << endl;
				return 1;
			}
			// goal for jug C
			if (i == 6)
			{
				cerr << "Error: Invalid goal '" << argv[i] << "' for jug C." << endl;
				return 1;
			}
		}
	}
	// check if goal for jug x <= capacity for jug x
	for (int i = 1, j = 4; i <= 3 && j <= 6; i++, j++)
	{
		int Itemp, Jtemp;
		istringstream issI(argv[i]);
		issI >> Itemp;
		istringstream issJ(argv[j]);
		issJ >> Jtemp;
		// check jug A
		if ((Jtemp > Itemp) && i == 1)
		{
			cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
			return 1;
		}
		// check jug B
		if ((Jtemp > Itemp) && i == 2)
		{
			cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
			return 1;
		}
		// check for jug C
		if ((Jtemp > Itemp) && i == 3)
		{
			cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
			return 1;
		}
	}

	// make sure #gallons in goal state = #gallons in start state
	int goal_state, capC;
	goal_state = 0;
	// capacity of c
	istringstream iss(argv[3]);
	iss >> capC;
	// add up gallons in goal
	for (int i = 4; i <= 6; i++)
	{
		int temp;
		istringstream it(argv[i]);
		it >> temp;
		goal_state += temp;
	}
	// check if they match up
	if (goal_state != capC)
	{
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}

// NO ERRORS! NOW COMPUTE...

	// set goal array
	for (int i = 4; i <= 6; i++)
	{
		istringstream iss (argv[i]);
		int temp;
		iss >> temp;
		goal[i - 4] = temp;
	}

	// make inputs usable by breadth first search algorithm
	istringstream iss1(argv[1]);
	int temp;
	iss1 >> temp;
	cap_a = temp;
	istringstream iss2(argv[2]);
	iss2 >> temp;
	cap_b = temp;
	istringstream iss3(argv[3]);
	iss3 >> temp;
	cap_c = temp;

	// time for the heavy lifting...
	bfs(0, 0, cap_c);
}

