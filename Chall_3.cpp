#include <iostream>
#include <regex>
#include <fstream>
#include <vector>
#include <numeric>
#include <utility> // For std::pair

using namespace std;

int main() {
    regex correct(R"(mul\((\d{1,3}),(\d{1,3})\))");

    ifstream file("T3_data.txt");
    if (!file) {
        cout << "File not found" << endl;
        return 1;
    }

    string line;
    vector<pair<int, int>> numberPairs;

    while (getline(file, line)) {
        sregex_iterator begin(line.begin(), line.end(), correct);
        sregex_iterator end;

        for (auto it = begin; it != end; ++it) {
            int num1 = stoi(it->str(1));
            int num2 = stoi(it->str(2));
            numberPairs.push_back(make_pair(num1, num2));
        }
    }

    // cout << "Extracted pairs:" << endl;
    // for (const auto& p : numberPairs) {
    //     cout << "(" << p.first << ", " << p.second << ")" << endl;
    // }

    int sum = transform_reduce(numberPairs.begin(), numberPairs.end(), 0, plus<>(),
        [](const pair<int, int>& p) {
            int product = p.first * p.second;
//            cout << "Multiplying: " << p.first << " * " << p.second << " = " << product << endl;
            return product;
        });

    cout << "Sum of all products: " << sum << endl;
    return 0;
}
