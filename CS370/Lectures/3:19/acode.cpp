#include <iostream>
#include <string>
#define get_digit(c) (int(int(c)-int('0')))

using namespace std;

int main() {
	while(1) {
		string str;
		cin >> str;
		if (str[0] == '0') {
			break;
		}
		long long int size = str.length();
		if (size == 1) {
			cout << 1 << endl;
			continue;
		}
		unsigned long long int *dp = new unsigned long long int [size + 1];
		dp[size] = 1;
		if (str[size-1] != '0') {
			dp[size-1] = 1;
		} else {
			dp[size-1] = 0;
		}
		for (long long int i = size-2; i >=0; --i) {
			if (str[i] == '0') {
				dp[i] = 0;
			} else if (get_digit(str[i]) > 2) {
				dp[i] = dp[i+1];
			} else if (get_digit(str[i]) == 2) {
				if (get_digit(str[i+1]) > 6) {
					dp[i] = dp[i+1];
				} else {
					dp[i] = dp[i+1] + dp[i+2];
				}
			} else {
				dp[i] = dp[i+1] + dp[i+2];
			}
		}
		cout << dp[0] << endl;
	}
}