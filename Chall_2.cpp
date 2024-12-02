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

int tainted_level = 0;
int tainted_index = 0;
bool dampen = false;

bool distance(Pair p) {
    int diff = abs(p.a - p.b);
    return (diff >= 1 && diff <= 3);
}

void report_dampener(vector<int>& reports) {
    if (tainted_index + 1 < reports.size()) {
        reports.erase(reports.begin() + tainted_index + 1);
    }
}

bool is_constant(const vector<int>& reports) {
    if (reports.size() < 2) return true; // Short sequences are constant by default

    bool increasing = true, decreasing = true;

    for (size_t i = 0; i < reports.size() - 1; ++i) {
        if (reports[i] < reports[i + 1]) decreasing = false;
        if (reports[i] > reports[i + 1]) increasing = false;
    }

    return increasing || decreasing; // True if strictly one or the other
}


bool is_safe(vector<int>& reports) {
    tainted_level = 0; // Reset tainted level at the start
    tainted_index = -1; // Initialize to an invalid index
    Pair p;
    bool found_invalid_distance = false;

    // Check for invalid distances
    for (size_t i = 0; i < reports.size() - 1; ++i) {
        p.a = reports[i];
        p.b = reports[i + 1];
        if (!distance(p)) {
            if (!found_invalid_distance) {
                tainted_level++;
                tainted_index = i; // Mark the problematic pair
                found_invalid_distance = true;
            }
        }
    }

    // Check for strictly increasing or decreasing order
    if (!is_constant(reports)) {
        tainted_level++;
        if (tainted_index == -1) {
            tainted_index = 0; // Set to the first index if not already set
        }
    }


    // If only one issue, attempt dampening
    if (tainted_level == 1 && !dampen) {
        dampen = true;
        if (tainted_index + 1 < reports.size()) {
            reports.erase(reports.begin() + tainted_index + 1); // Remove the element causing the issue
        }
        bool result = is_safe(reports); // Recheck safety after dampening
        dampen = false; // Reset dampening
        return result;
    }

    // Unsafe if multiple issues or dampening failed
    return tainted_level > 0;
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
     while (getline(file, line)) { // Uncomment for file input
//    while (getline(cin, line)) { // For standard input
        istringstream iss(line);
        int a;
        while (iss >> a) {
            reports.push_back(a);
        }
        if (is_safe(reports)) {
            correct_arr.push_back(0);
            //cout << "Tainted" << endl;
        } else {
            correct_arr.push_back(1);
            //cout << "Safe" << endl;
        }
        reports.clear();
    }

    cout << accumulate(correct_arr.begin(), correct_arr.end(), correct) << endl;
    return 0;
}
