#include <iostream>
#include <regex>
#include <fstream>
#include <vector>
#include <numeric>
#include <utility>

using namespace std;

int main() {
    regex correct(R"(mul\((\d{1,3}),(\d{1,3})\))");
    regex enable(R"(do\(\))");
    regex disable(R"(don't\(\))");

    ifstream file("T3_data.txt");
    if (!file) {
        cout << "File not found" << endl;
        return 1;
    }

    bool flag = false;  // Initially, set flag to false (don't process any mul initially)
    string line;
    vector<pair<int, int>> numberPairs;

    while (getline(file, line)) {
        // Debug: Print the current line being processed
        cout << "Processing line: " << line << endl;

        // Flip the flag based on 'do()' and 'don't()'
        sregex_iterator enable_begin(line.begin(), line.end(), enable);
        sregex_iterator disable_begin(line.begin(), line.end(), disable);
        sregex_iterator end;

        // If 'do()' is found, set flag to true (start adding mul pairs)
        for (auto it = enable_begin; it != end; ++it) {
            flag = true;
            cout << "Flag enabled (do())" << endl;
        }

        // If 'don't()' is found, set flag to false (stop adding mul pairs)
        for (auto it = disable_begin; it != end; ++it) {
            flag = false;
            cout << "Flag disabled (don't())" << endl;
        }

        // If the flag is true, process the mul(x, y) pairs in the line

            sregex_iterator begin(line.begin(), line.end(), correct);
            for (auto it = begin; it != end; ++it) {
                int num1 = stoi(it->str(1)); // First number in mul(x,y)
                int num2 = stoi(it->str(2)); // Second number in mul(x,y)
                if (flag) {
                // Debug: Print when a mul pair is found and added based on flag
                cout << "Found and added mul(" << num1 << "," << num2 << ") to vector." << endl;
                numberPairs.push_back(make_pair(num1, num2));
            }
        }
    }

    // Debug: Print the content of the vector with all mul(x,y) pairs
    cout << "Number pairs collected: " << endl;
    for (const auto& p : numberPairs) {
        cout << "(" << p.first << "," << p.second << ")" << endl;
    }

    // Calculate sum of products of all pairs
    int sum = transform_reduce(numberPairs.begin(), numberPairs.end(), 0, plus<>(),
        [](const pair<int, int>& p) {
            int product = p.first * p.second;
            return product;
        });

    cout << "Sum of all products: " << sum << endl;

    return 0;
}
