#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <numeric>

using namespace std;

struct Pair {
    int a = 0;
    int b = 0;
};

bool distance(Pair p) {
    int diff = abs(p.a - p.b);
    return diff >= 1 && diff <= 3;
}

bool is_constant(vector<int>& reports) {
    bool increase = false;
    bool decrease = false;
    for (int j = 0; j < reports.size() - 1; j++) {
        if (reports.at(j) > reports.at(j + 1)) {
            decrease = true;
        } else if (reports.at(j) < reports.at(j + 1)) {
            increase = true;
        } else {
            return false;
        }
    }
    return increase ^ decrease;
}

bool is_safe(vector<int>& reports) {
    for (int i = 0; i < reports.size() - 1; i++) {
        Pair p = {reports.at(i), reports.at(i + 1)};
        if (!distance(p)) {
            return false;
        }
    }
    return is_constant(reports);
}

bool can_be_fixed(vector<int>& reports) {
    for (int i = 0; i < reports.size(); i++) {
        vector<int> temp = reports;
        temp.erase(temp.begin() + i);
        if (is_safe(temp)) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream file("T2_data.txt");
    vector<int> reports;
    vector<int> correct_arr;
    int correct = 0;

    if (!file) {
        cout << "File not found" << endl;
        return -1;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int a;
        while (iss >> a) {
            reports.push_back(a);
        }
        if (is_safe(reports)) {
            correct_arr.push_back(1);
            cout << "Safe" << endl;
        } else if (can_be_fixed(reports)) {
            correct_arr.push_back(1);
            cout << "Fixed and Safe" << endl;
        } else {
            correct_arr.push_back(0);
            cout << "Tainted" << endl;
        }
        reports.clear();
    }

    cout << accumulate(correct_arr.begin(), correct_arr.end(), correct) << endl;

    return 0;
}