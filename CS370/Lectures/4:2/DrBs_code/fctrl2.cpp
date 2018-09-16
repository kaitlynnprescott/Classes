/*******************************************************************************
 * Name          : fctrl2.cpp
 * Author        : Brian S. Borowski
 * Version       : 1.0
 * Date          : October 30, 2012
 * Last modified : April 3, 2018
 * Description   : Solution to SPOJ #24 - Small Factorials
 *                 http://www.spoj.com/problems/FCTRL2/
 ******************************************************************************/
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

class BigInt {
    friend ostream& operator<<(ostream& output, const BigInt& p);

    private:
        vector<int> digits;
    
    public:
        explicit BigInt(int num) {
            while (num > 0) {
                digits.push_back(num % 10);
                num /= 10;
            }
        }
        
        BigInt & operator*=(const int n) {
            int temp = 0;
            for (int i = 0, len = digits.size(); i < len; ++i) {
                int x = digits[i] * n + temp;
                digits[i] = x % 10;
                temp = x / 10; 
            }
            while (temp > 0) {
                digits.push_back(temp % 10);
                temp /= 10;
            }
            return *this;
        }
};

ostream& operator<<(ostream& output, const BigInt& bi) {
    for (int i = bi.digits.size() - 1; i >= 0; --i) {
        output << bi.digits[i];
    }
    return output;
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int how_many;
    cin >> how_many;
    int values[how_many];

    for (int i = 0; i < how_many; i++) {
        cin >> values[i];
    }

    for (int i = 0; i < how_many; i++) {
        BigInt big(values[i]);
        while (values[i] > 1) {
            --values[i];
            big *= values[i];
        }
        cout << big << "\n";
    }

    return 0;
}
