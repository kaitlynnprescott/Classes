/*******************************************************************************
 * Name        : tilepainting.cpp
 * Author      : Patrick Grasso / Brian S. Borowski
 * Version     : 1.0
 * Date        : April 17, 2016
 * Description : Solves HackerRank's 'Paint the Tiles' problem.
 ******************************************************************************/
#include <iostream>

using namespace std;

int main() {
    int num_tiles;
    cin >> num_tiles;
    string config;
    cin >> config;

    int i = 1, strokes = 1;
    while (i < num_tiles) {
        strokes += config[i-1] != config[i];
        i++;
    }

    cout << strokes << endl;
    return 0;
}
