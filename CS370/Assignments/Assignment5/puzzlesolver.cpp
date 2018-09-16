/*
Kaitlynn Prescott, Meng Qui, Christopher Rudel
3/5/18
puzzlesolver.cpp
We pledge our honor that we have abided by the stevens honor system
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

enum position { TOP, LEFT, BOTTOM, RIGHT };


class Square {

private:
    string color[4];
    int sqNum, place;

public:
    Square(int squareNum, string &s1, string &s2, string &s3, string &s4){
        color[0] = s1;
        color[1] = s2;
        color[2] = s3;
        color[3] = s4;
	sqNum = squareNum;
	place = 0;
    }

    string& operator[] (const int index) {
        int c = index+4 - place;
	return color[c & 3];
    }

    // Prints Input squares
    friend std::ostream& operator<<(std::ostream& os, Square &tile) {
        os << tile.sqNum << ". <" << tile[TOP] << ", " << tile[LEFT] << ", " << tile[BOTTOM] << ", " << tile[RIGHT] << ">";
         return os;
    }

    void rotateR() {
	int c = place+1;
	place = c & 3;
    }


    int number() const{
	return sqNum;
    }

    int getID() const {
        return sqNum;
    }
};

class Puzzle {
public:
    Puzzle(const string &filename) : strSwap("         ") {
        readFile(filename);
        showBoard();
    }

    void solve() {
        generatePerm("", "012345678");
        int n = solutions.size();
        if (n == 0) {
            cout << "No solution found." << "\n";
            return;
        }
        if(n==1)//assignment asked to have this
	    cout << n << ". unique solution found\n";
	else
	    cout << n << ". unique solutions found\n";
        for (int i = 0; i < n; i++) {
            if (i != 0) {
                cout << "\n";
            }
            drawSolution(solutions[i]);
        }
    }

private:
    vector<Square> sqSet;
    vector< pair<string, vector<Square> > > solutions;
    string strSwap;

    // prints out the input tiles 
    void showBoard() {
        cout << ":" << "\n";
        for (int i = 0, len = sqSet.size(); i < len; i++) {
            cout << sqSet[i] << "\n";
        }
        cout << "\n";
    }

    //rotates puzzle board to the right 
    void rotateRight(string &pos) {
        strSwap[0] = pos[6];
        strSwap[1] = pos[3];
        strSwap[2] = pos[0]; 
        strSwap[3] = pos[7];
        strSwap[4] = pos[4]; 
        strSwap[5] = pos[1];
        strSwap[6] = pos[8]; 
        strSwap[7] = pos[5];
        strSwap[8] = pos[2];
        for (int i = 0; i < 9; i++) {
            pos[i] = strSwap[i];
        }
    }

    // checks if the solution is unique
    bool uniqueSol(const string &pos) {
        int n = solutions.size();
        if (n == 0) {
            return true;
        }
        string cpy(pos);
        for (int i = 0; i < n; i++) {
            string &solution = solutions[i].first;
            for (int j = 0; j < 4; j++) {
                rotateRight(cpy);
                if (cpy == solution) {
                    return false;
                }
            }
        }
        return true;
    }


    // Generates all permutaions on 012345678
    void generatePerm(const string &s1, const string &s2) {
        if (s2 == "") {
            if (uniqueSol(s1)) {
                solutions.push_back(make_pair(s1, sqSet));
            }
            return;
        }
        for (int i = 0, len = s2.length(); i < len; i++) {
            string new_s1 = s1 + s2[i];
            int new_s1_len = new_s1.length();
            int square_num = s2[i] - '0';

            for (int j = 0; j < 4; j++) {
                // Check all rotations of square.
                sqSet[square_num].rotateR();
                if (isSolution(new_s1)) {
                    generatePerm(
                            new_s1, s2.substr(0, i) + s2.substr(i + 1));
                    if (new_s1_len != 1) {
                        break;
                    }
                }
            }
        }
    }
    // Checks if the move is valid
    bool validMove(const string &pos, int fst, int snd, position col1,position col2) {
        string &color1 = sqSet[pos[fst] - '0'][col1];
        string &color2 = sqSet[pos[snd] - '0'][col2];
        bool equal = color1[0] == color2[0];
        bool absVal = abs(color1[1]-color2[1]) == 1;

        return equal && absVal;
    }

    // Checks if the solution is valid
    bool isSolution(const string &pos) {
        const int size = pos.size();
       	    
            if(size== 1)
                return true;
            else if(size == 2)
                return validMove(pos, 0, 1, LEFT, RIGHT);
            else if(size == 3)
                return validMove(pos, 1, 2, LEFT, RIGHT);
            else if(size == 4)
                return validMove(pos, 0, 3, BOTTOM, TOP);
            else if(size == 5)
                return validMove(pos, 3, 4, LEFT, RIGHT) &&
                       validMove(pos, 1, 4, BOTTOM, TOP);
            else if(size == 6)
                return validMove(pos, 4, 5, LEFT, RIGHT) &&
                       validMove(pos, 2, 5, BOTTOM, TOP);
            else if(size == 7)
                return validMove(pos, 3, 6, BOTTOM, TOP);
            else if(size == 8)
                return validMove(pos, 6, 7, LEFT, RIGHT) &&
                       validMove(pos, 4, 7, BOTTOM, TOP);
            else if(size == 9)
                return validMove(pos, 7, 8, LEFT, RIGHT) &&
                       validMove(pos, 5, 8, BOTTOM, TOP);
          
        return true;
    }


    // prints out the given puzzle board 
    void drawSolution(pair<string, vector<Square> > &solution) {
        cout << "+--------+--------+--------+" << "\n";
        int i = 0;
        for (int row = 0; row < 3; row++) {
            for (int line = 0; line < 3; line++) {
                for (int col = 0; col < 3; col++) {
                    Square &square = solution.second[solution.first[i + col] - '0'];
                    if (line == 0) {
                        cout << "|" << square.number() << "  " << square[TOP]
                             << "   ";
                    } else if (line == 1) {
                        cout << "|" << square[RIGHT] << "    " << square[LEFT];
                    } else {
                        cout << "|   " << square[BOTTOM] << "   ";
                    }
                }
                cout << "|" << "\n";

            }
            cout << "+--------+--------+--------+" << "\n";
            i += 3;
        }
    }

    // Reads input file
    void readFile(const string &filename) {
        ifstream input_file(filename.c_str());
        if (!input_file) {
            throw runtime_error("Cannot open file '" + filename + "'.");
        }
       string line, word;
        
         vector<string> tokens(4, "");
         int lineNum = 1;
         while (getline(input_file, line)) {
             line = rmWhitespace(line);
             tokens.clear();
             int start = 0, end = 0;
             while ((end = line.find(",", start)) != string::npos) {
                 tokens.push_back(line.substr(start, end - start));
                 start = end + 1;
             }
             tokens.push_back(line.substr(start)); 
             sqSet.push_back(
                 Square(lineNum++,
                      tokens[0], tokens[1], tokens[2], tokens[3]));
         }
        
    }

    // Removes whitespace 
    string rmWhitespace(const string& str) {
        int first = str.find_first_not_of(" \t\r\n");
        if (string::npos == first) {
            return str;
        }
        return str.substr(first, str.find_last_not_of(" \t\r\n") - first + 1);
    }
};



int main(int argc, char *argv[]) {
    clock_t start = clock(); 
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file>" << "\n";
        return 1;
    }
    Puzzle solver(argv[1]);
    solver.solve();
    double time = (double)(clock() - start) / CLOCKS_PER_SEC * 2500.0;
    cout << "Elapsed time: " << fixed << time
         << " ms" << "\n";

    return 0;
}
