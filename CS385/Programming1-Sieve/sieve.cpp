/************************************************************************************
 * Name        : sieve.cpp
 * Author      : Katie Prescott
 * Date        : Feb 2, 2016
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ***********************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>


using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit) : is_prime_(new bool[limit + 1]), limit_(limit) {
        sieve();
    }

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    inline int num_primes() const {
        return num_primes_;
    }

    void display_primes() const {
        // : write code to display the primes in the format specified in the
        // requirements document.

    	// set num_primes = the number of primes in the array
    	int num_primes = count_num_primes();
    	// what is the highest number of digits in a number in the list of primes
    	// how many numbers can we put on one line
    	const int max_prime_width = num_digits(max_prime_),
    			primes_per_row = 80 / (max_prime_width + 1);
    	// print out number of primes found and the primes
    	cout << "Number of primes found: " << num_primes << endl;
    	cout << "Primes up to " << limit_ << ":" << endl;
    	// for loop going from 2 to the limit
    	for (int i = 2, x =0; i <= limit_; i++)
    	{
    		// check if the number of primes is greater than the number of primes
    		// allowed in each row
    		if (num_primes > primes_per_row)
    		{
    			// check if its a prime
    			if (is_prime_[i] == true)
    			{
    				// increment x (keeps track of the number of primes in the row)
    				x++;
    				// is i the last prime?
    				if (i == max_prime_)
    				{
    					// if so, print i and break
    					cout << i;
    					break;
    				}
    				// check if you need a new row
    				if ((x % primes_per_row) == 0)
    				{
    					// if so, set width of new row, print i and end the line
    					cout << setw(max_prime_width);
    					cout << i << endl;
    				}
    				else
    				{
    					// otherwise, print with a space and keep going
    					cout << setw(max_prime_width);
    					cout << i << " ";
    				}
    			}
    		}
    		// if you only need 1 row
    		if (num_primes < primes_per_row)
    		{
    			// check if i is prime
    			if (is_prime_[i] == true)
    			{
    				// is it the last prime?
    				if (i == max_prime_)
    				{
    					// if so, just print it
    					cout << i;
    				}
    				else
    				{
    					// otherwise, print it with a space
    					cout << i << " ";
    				}
    			}
    		}
    	}
    }


private:
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    int count_num_primes() const {
        // : write code to count the number of primes found

    	int num_primes_ = 0;
    	for (int i = 2; i <= limit_ + 1; i++)
    	{
    		if (is_prime_[i] == true)
    		{
    			num_primes_++;
    		}
    	}
    	return num_primes_;
    }

    int num_digits(int num) const {
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

    void sieve() {
        // : write sieve algorithm

    	// input an integer n > 1
    	int n = limit_;
    	//is_prime is an array of bool values, indexed by integers 2 to n,
    	// all initially true.
    	// use a for loop to set each value including and after 2 to true
    	for (int i = 2; i <= n; i++)
    	{
    		is_prime_[i] = true;
    	}

    	// for loop for each number <= square root of n
    	for (int i = 2; i <= sqrt(n); i++)
    	{
    		// check if its prime
    		if (is_prime_[i] == true)
    		{
				// iterate through each multiple of i starting at i^2
				for (int j = i*i; j <= n; j += i)
				{
					// set as not prime
					is_prime_[j] = false;
				}
    		}
    	}
    	// code to find the maximum prime in the list.
		for (int k = limit_; k >= 2; k--)
		{
			if (is_prime_[k] == true)
			{
				max_prime_ = k;
				break;
			}
		}
    }
};

int main(void) {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // : write code that uses your class to produce the desired output.

    PrimesSieve primes(limit);
    cout << endl;
    primes.display_primes();
    return 0;
}


