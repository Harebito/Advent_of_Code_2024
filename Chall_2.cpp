#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <numeric>


using namespace std;

struct Pair{
    int a = 0;
    int b = 0;
};

int pair_distance(Pair pair) {
    return abs(pair.a - pair.b);
}

bool increase_decrease(Pair pair) {
    if(pair.a > pair.b) {
        return true;
    }
    return false;
}

// bool is_safe(vector<int> reports) {
//     Pair pair;
//     pair.a = reports[0];
//     pair.b = reports[1];
//     bool tainted = false;
//     for(int i = 0; i < reports.size(); i++) {
//         pair.a = reports[0];
//         pair.b = reports[1];
//         while(pair.b < reports.size() - 1) {
//             if(pair_distance(pair) >3 && pair_distance(pair) < 1 && !increase_decrease(pair)) {
//                 tainted = true;
//             }
//             pair.a++;
//             pair.b++;
//         }
//     }
//     return tainted;
// }
bool is_safe(vector<int> reports) {
    if (reports.size() < 2) {
        return false;
    }

    bool tainted = false;
    for (size_t i = 0; i < reports.size() - 1; ++i) {
        Pair pair;
        pair.a = reports[i];
        pair.b = reports[i + 1];

        if (pair_distance(pair) > 3 || pair_distance(pair) < 1 || !increase_decrease(pair)) {
            tainted = true;
        }
    }
    return tainted;
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
            correct_arr.push_back(0);
        } else {
            correct_arr.push_back(1);
        }
        reports.clear();
    }

    cout << accumulate(correct_arr.begin(), correct_arr.end(), correct) << endl;

    return 0;
}