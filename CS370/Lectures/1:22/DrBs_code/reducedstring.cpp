/*******************************************************************************
 * Name          : reducedstring.cpp
 * Author        : Brian S. Borowski
 * Version       : 1.1
 * Date          : January 22, 2018
 * Last modified : January 23, 2018
 * Description   : Solution to HackerRank -> Algorithms -> Strings ->
                   Super Reduced String
 ******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    size_t i = 1, len = s.length();
    while (i < len) {
        if (s[i] == s[i - 1]) {
            if (i <= len - 2) {
                // The duplicate characters are in the middle of the string.
                // Make a new string with the duplicates eliminated.
                s = s.substr(0, i - 1) + s.substr(i + 1);
            } else {
                // The duplicate characters are at the end.
                // Make a new string up to where the duplicates start.
                s = s.substr(0, i - 1);
            }
            // Quick and dirty hack to start over at the beginning of the
            // string.
            i = 1;
        } else {
            i++;
        }
        len = s.length();
    }

    cout << (s == "" ? "Empty String" : s) << endl;
    return 0;
}
