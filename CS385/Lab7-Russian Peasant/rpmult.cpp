/*
 * rpmult.cpp
 *
 *  Created on: Mar 11, 2016
 *      Author: katieprescott
 */
#include <iostream>
#include <sstream>

using namespace std;

 unsigned long russian_peasant_multiplication(unsigned int m, unsigned int n)
 {
	 long sum = 0;
	 while (n > 0)
	 {
		 if (n & 1)
		 {
			sum += m;
		 }
		 m = m << 1;
		 n = n >> 1;
	 }
	 return sum;
 }

int main(int argc, char * const argv[])
{
	if (argc != 3)
	{
		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
		return 1;
	}
	int m, n;
	stringstream iss(argv[1]);
	if (!(iss >> m))
	{
		cerr << "Error: The first argument is not a valid nonnegative integer." << endl;
		return 1;
	}
	if (m < 0)
	{
		cerr << "Error: The first argument is not a valid nonnegative integer." << endl;
		return 1;
	}
	stringstream iss1(argv[2]);
	if (!(iss1 >> n))
	{
		cerr << "Error: The second argument is not a valid nonnegative integer." << endl;
		return 1;
	}
	if (n < 0)
	{
		cerr << "Error: The first argument is not a valid nonnegative integer." << endl;
		return 1;
	}

	cout << m << " x " << n << " = " << russian_peasant_multiplication(m, n) << endl;
}
