/*******************************************************************************
 * Name          : puzzlesolver.cpp
 * Author        : Brian S. Borowski
 * Version       : 1.0
 * Date          : January 11, 2017
 * Last modified : March 3, 2018
 * Description   : Finds solutions to the scramble squares picture puzzle.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>
#include <cstring>
#include <ctime>

using namespace std;

enum directions_t { NORTH, EAST, SOUTH, WEST };

class Tile {
public:
    Tile(unsigned int tile_num,
         const string &s1,
         const string &s2,
         const string &s3,
         const string &s4): tile_num_(tile_num), offset_(0) {
        images_[0] = s1;
        images_[1] = s2;
        images_[2] = s3;
        images_[3] = s4;
    }

    inline string& operator[] (const int index) {
        // x % 4 == x & 3
        return images_[(index + 4 - offset_) & 3];
    }

    inline void rotate_right() {
        offset_ = (offset_ + 1) & 3;
    }

    inline int number() const {
        return tile_num_;
    }

    friend std::ostream& operator<<(std::ostream& os, Tile &tile) {
        os << tile.tile_num_ << ". "
           << "<" << tile[NORTH] << ","
           << " " << tile[EAST] << ","
           << " " << tile[SOUTH] << ","
           << " " << tile[WEST] << ">";
        os.flush();
        return os;
    }

private:
    string images_[4];
    unsigned int tile_num_, offset_;
};

class PuzzleSolver {
public:
    explicit PuzzleSolver(const string &filename) : swap_str_("         ") {
        parse_file(filename);
        display_input();
    }

    void solve() {
        char s1[10] = "";
        char s2[10] = "012345678";
        generate_permutations(s1, 0, s2, 9);
        size_t n = solutions_.size();
        if (n == 0) {
            cout << "No solution found." << "\n";
            return;
        }
        cout << n << " unique solution" << (n != 1 ? "s" : "")
             << " found:" << "\n";
        for (size_t i = 0; i < n; i++) {
            if (i != 0) {
                cout << "\n";
            }
            draw_solution(solutions_[i]);
        }
    }

private:
    vector<Tile> tile_set_;
    vector< pair<string, vector<Tile> > > solutions_;
    string swap_str_;

    void display_input() {
        cout << "Input tiles:" << "\n";
        for (size_t i = 0, len = tile_set_.size(); i < len; i++) {
            cout << tile_set_[i] << "\n";
        }
        cout << "\n";
    }

    /**
     * Rotates the entire configuration 90 degrees to the right.
     * Implementation is fixed for a 3x3 grid and relies on swap_str_ for
     * external storage.
     */
    void rotate_right(string &order) {
        swap_str_[0] = order[6]; swap_str_[1] = order[3];
        swap_str_[2] = order[0]; swap_str_[3] = order[7];
        swap_str_[4] = order[4]; swap_str_[5] = order[1];
        swap_str_[6] = order[8]; swap_str_[7] = order[5];
        swap_str_[8] = order[2];
        for (int i = 0; i < 9; i++) {
            order[i] = swap_str_[i];
        }
    }

    bool is_unique_solution(const string &order) {
        size_t n = solutions_.size();
        if (n == 0) {
            return true;
        }
        string cpy(order);
        for (size_t i = 0; i < n; i++) {
            string &solution = solutions_[i].first;
            for (int j = 0; j < 4; j++) {
                rotate_right(cpy);
                if (cpy == solution) {
                    return false;
                }
            }
        }
        return true;
    }

    char remove_char_at_index(char *s, const int len, const int index) {
        char c = s[index];
        for (int i = index; i < len; i++) {
            s[i] = s[i + 1];
        }
        return c;
    }

    void restore_char_at_index(
            char *s, const int len, char c, const int index) {
        s[len + 1] = '\0';
        for (int i = static_cast<int>(len); i > index; i--) {
            s[i] = s[i - 1];
        }
        s[index] = c;
    }

    /**
     * Generates all permutations of the string "012345678" in lexicographic
     * order. As the characters are moved from s2 to s1, the sub-solution is
     * checked for validity. If the last move is not valid, that path is pruned,
     * and the algorithm backtracks to the last working sub-solution.
     */
    void generate_permutations(
            char *s1, size_t s1_len, char *s2, size_t s2_len) {
        if (s2_len == 0) {
            // All nine tiles have been placed.
            if (is_unique_solution(s1)) {
                // The solution is not a rotation of another solution.
                solutions_.push_back(make_pair(s1, tile_set_));
            }
            return;
        }
        const size_t new_s2_len = s2_len - 1;
        for (size_t i = 0; i < s2_len; i++) {
            const size_t new_s1_len = s1_len + 1;
            s1[s1_len] = s2[i];
            s1[new_s1_len] = '\0';

            int tile_num = s2[i] - 48;
            for (int j = 0; j < 4; j++) {
                // Check all the rotations of the tile.
                tile_set_[tile_num].rotate_right();
                if (is_solution(s1, new_s1_len)) {
                    // The move is valid, so continue recursing.
                    char c = remove_char_at_index(s2, s2_len, i);
                    generate_permutations(s1, new_s1_len, s2, new_s2_len);
                    restore_char_at_index(s2, new_s2_len, c, i);
                    if (new_s1_len != 1) {
                        break;
                    }
                }
            }

            s1[s1_len] = '\0';
        }
    }

    void draw_solution(pair<string, vector<Tile> > &solution) {
        cout << "+--------+--------+--------+" << "\n";
        int i = 0;
        for (int row = 0; row < 3; row++) {
            for (int line = 0; line < 3; line++) {
                for (int col = 0; col < 3; col++) {
                    Tile &tile = solution.second[solution.first[i + col] - 48];
                    if (line == 0) {
                        cout << "|" << tile.number() << "  " << tile[NORTH]
                             << "   ";
                    } else if (line == 1) {
                        cout << "|" << tile[WEST] << "    " << tile[EAST];
                    } else {
                        cout << "|   " << tile[SOUTH] << "   ";
                    }
                }
                cout << "|" << "\n";

            }
            cout << "+--------+--------+--------+" << "\n";
            i += 3;
        }
    }

    /**
     * Determines if a move is valid by checking the images at the tiles
     * in (index1, dir1) and (index2, dir2). If they match, the first letter
     * will be the same, and there will be a difference of 1 in the second
     * part of the string.
     */
    inline bool is_move_valid(char *order, int index1, int index2,
            directions_t dir1, directions_t dir2) {
        string &image1 = tile_set_[order[index1] - 48][dir1];
        string &image2 = tile_set_[order[index2] - 48][dir2];
        return image1[0] == image2[0] && abs(image1[1] - image2[1]) == 1;
    }

    /**
     * Determines if the solution is valid by determining if the last
     * tile placed results in a valid sub-solution.
     */
    bool is_solution(char *order, size_t length) {
        switch (length) {
            case 1:
                return true;
            case 2:
                return is_move_valid(order, 0, 1, EAST, WEST);
            case 3:
                return is_move_valid(order, 1, 2, EAST, WEST);
            case 4:
                return is_move_valid(order, 0, 3, SOUTH, NORTH);
            case 5:
                return is_move_valid(order, 3, 4, EAST, WEST) &&
                       is_move_valid(order, 1, 4, SOUTH, NORTH);
            case 6:
                return is_move_valid(order, 4, 5, EAST, WEST) &&
                       is_move_valid(order, 2, 5, SOUTH, NORTH);
            case 7:
                return is_move_valid(order, 3, 6, SOUTH, NORTH);
            case 8:
                return is_move_valid(order, 6, 7, EAST, WEST) &&
                       is_move_valid(order, 4, 7, SOUTH, NORTH);
            case 9:
                return is_move_valid(order, 7, 8, EAST, WEST) &&
                       is_move_valid(order, 5, 8, SOUTH, NORTH);
            default:
                break;
        }
        return true;
    }

    void parse_file(const string &filename) {
        ifstream input_file(filename.c_str());
        if (!input_file) {
            throw runtime_error("Cannot open file '" + filename + "'.");
        }
        input_file.exceptions(ifstream::badbit);
        string line, word;
        try {
            vector<string> tokens(4, "");
            unsigned int line_number = 1;
            while (getline(input_file, line)) {
                if (line_number > 9) {
                    throw runtime_error(
                        "File '" + filename + " contains more than 9 lines'.");
                }
                line = trim(line);
                tokens.clear();
                size_t start_pos = 0, end_pos = 0;
                while ((end_pos = line.find(",", start_pos)) != string::npos) {
                    tokens.push_back(
                            line.substr(start_pos, end_pos - start_pos));
                    start_pos = end_pos + 1;
                }
                tokens.push_back(line.substr(start_pos));
                if (tokens.size() != 4) {
                    ostringstream oss;
                    oss << "Line number " << line_number << " does not"
                        << " contain 4 fields.";
                    throw runtime_error(oss.str());
                }
                tile_set_.push_back(
                    Tile(line_number++,
                         tokens[0], tokens[1], tokens[2], tokens[3]));
            }
        } catch (const ifstream::failure &f) {
            throw runtime_error(
                    "An I/O error occurred reading '" + filename + "'.");
        }
    }

    /**
     * Returns a new string with leading and trailing whitespace removed.
     */
    string trim(const string& str) {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (string::npos == first) {
            return str;
        }
        return str.substr(first, str.find_last_not_of(" \t\r\n") - first + 1);
    }
};

int main(int argc, char * const argv[]) {
    clock_t start = clock();
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << "\n";
        return 1;
    }
    try {
        PuzzleSolver solver(argv[1]);
        solver.solve();
        double time = (double)(clock() - start) / CLOCKS_PER_SEC * 1000.0;
        cout << "Elapsed time: " << fixed << setprecision(2) << time
             << " ms" << "\n";
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
