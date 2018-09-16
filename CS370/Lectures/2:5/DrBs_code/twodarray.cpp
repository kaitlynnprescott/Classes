/*******************************************************************************
 * Name        : twodarray.cpp
 * Author      : Brian S. Borowski
 * Version     : 1.0
 * Date        : February 7, 2016
 * Description : Solution to HackerRank -> Data Structures -> Arrays ->
 *               2D Array - DS
 ******************************************************************************/
#include <vector>
#include <climits>
#include <iostream>

using namespace std;

int main() {
    vector< vector<int> > arr(6, vector<int>(6));
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            cin >> arr[i][j];
        }
    }
    int max_sum = INT_MIN;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int sum = 0;
            for (int k = 0; k < 3; k++) {
                sum += arr[i][j + k] + arr[i + 2][j + k];
            }
            sum += arr[i + 1][j + 1];
            if (sum > max_sum) {
                max_sum = sum;
            }
        }
    }
    cout << max_sum << endl;
    return 0;
}
