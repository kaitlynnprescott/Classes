/*******************************************************************************
 * Name        : xordecryption.cpp
 * Author      : Brian S. Borowski
 * Version     : 1.0
 * Date        : March 23, 2015
 * Description : Solution to Project Euler #59
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int DEFAULT_SIZE = 4096;
const float THRESHOLD = 0.95;

char *original_data, *copy_data;
int num_chars, required_chars;

void display_text() {
    for (int i = 0; i < num_chars; i++) {
        cout << copy_data[i];
    }
    cout << endl;
}

int get_ascii_sum() {
    int sum = 0;
    for (int i = 0; i < num_chars; i++) {
        sum += copy_data[i];
    }
    return sum;
}

bool try_key(char key[]) {
    int count = 0;
    for (int i = 0, j = 0; i < num_chars; ) {
        char c = copy_data[i] = (char)(original_data[i] ^ key[j]);
        i++;
        j++;
        if (j == 3) {
            j = 0;
        }
        if ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') || c == ' ' || c == '.') {
            count++;
        }
    }

    if (count >= required_chars) {
        cout << "key = " << key << ", sum = " << get_ascii_sum() << ": ";
        display_text();
        return true;
    }
    return false;
}

void brute_force_keys() {
    char key[4];
    key[3] = '\0';
    for (char x = 'a'; x <= 'z'; x++) {
        key[0] = x;
        for (char y = 'a'; y <= 'z'; y++) {
            key[1] = y;
            for (char z = 'a'; z <= 'z'; z++) {
                key[2] = z;
                if (try_key(key)) {
                    return;
                }
            }
        }
    }
}

int main() {
    ifstream input_file("cipher.txt");
    // If the file does not exist, print an error message and exit the program.
    if (!input_file) {
        cerr << "Error: Cannot read file 'cipher.txt'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);

    vector<int> ascii_values;
    int i, t = 0, size = DEFAULT_SIZE;
    char c;
    try {
        while ((c = input_file.get()) != EOF) {
            if (c == ',' || c == '\n') {
                ascii_values.push_back(t);
                t = 0;
            } else {
                t = t * 10 + (c - '0');
            }
        }
        // Don't forget to close the file.
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading 'cipher.txt'.";
        return 1;
    }

    num_chars = ascii_values.size();
    required_chars = (int)(THRESHOLD * num_chars);

    original_data = new char[num_chars];
    copy_data = new char[num_chars];
    for (i = 0; i < num_chars; i++) {
        original_data[i] = (char)ascii_values[i];
    }
    brute_force_keys();

    delete [] original_data;
    delete [] copy_data;

    return 0;
}
