/*
 * gcd.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: Kaitlynn Prescott
 *      Pledge: I pledge my honot that I have abided by the Stevens honor system.
 */

#include <iostream>

#include <sstream>

using namespace std;

int gcdrec(int a, int b)
{
	if (a == 0)
	{
		return b;
	}
	if (b == 0)
	{
		return a;
	}
	if (a % b == 0)
	{
		return b;
	}
	else
	{
		return gcdrec(b, a % b);
	}
}

int gcditer(int a, int b)
{
	int c;
	while (b != 0)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}


int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
		return 1;
	}
	int a; int b;
	istringstream iss(argv[1]);
	istringstream iss2(argv[2]);

	if (!(iss >> a))
	{
		cerr << "Error: The first argument is not a valid integer." << endl;
		return 1;
	}
	if (!(iss2 >> b))
	{
		cerr << "Error: The second argument is not a valid integer." << endl;
		return 1;
	}
	cout << "Iterative: gcd(" << a << ", " << b << ") = " << gcditer(a, b) << endl;
	cout << "Recursive: gcd(" << a << ", " << b << ") = " << gcdrec(a, b) << endl;
	return 0;
}

