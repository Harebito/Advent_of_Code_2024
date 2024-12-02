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

bool distance(Pair p) {
    return 3 >= abs(p.a - p.b) >= 1;
}

bool is_constant(vector<int>* reports) {
    bool increase = false;
    bool decrease = false;
    for(int j = 0; j < reports->size() - 1; j++) {
        if(reports->at(j) > reports->at(j + 1)) {
            increase = true;
        } else if(reports -> at(j) < reports->at(j + 1)) {
            decrease = true;
        }
        if(reports -> at(j) == reports->at(j + 1)) {
            increase = false;
            decrease = false;
            break;
        }
    }
    return increase ^ decrease;
}

bool is_safe(vector<int>* reports) {
    bool tainted = false;
    Pair p;
    for(int i = 0; i < reports->size() - 1; i++) {
        p.a = reports->at(i);
        p.b = reports->at(i + 1);
        if(!distance(p)) {
            tainted = true;
        }

    }
    if(!is_constant(reports)) {
        tainted = true;
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
        if (is_safe(&reports)) {
            correct_arr.push_back(0);
        } else {
            correct_arr.push_back(1);
        }
        reports.clear();
    }

    cout << accumulate(correct_arr.begin(), correct_arr.end(), correct) << endl;

    return 0;
}