#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <numeric>
#include "quicksort.h"
#include <unordered_map>


using namespace std;

int main() {
    ifstream file("T1_data.txt");

    vector<int> data_left;
    vector<int> data_right;
    vector<int> subtraction;
    vector<int> results;

    unordered_map<int, int> map;


    if (!file){
        cout << "File not found" << endl;
        return -1;
    }
    string line;
    while (getline(file, line)){
        istringstream iss(line);
        int a, b;
        if (!(iss >> a >> b)){
            cout << "Error reading file" << endl;
            return -1;
        }
        data_left.push_back(a);
        data_right.push_back(b);
    }
    //part 1
    quicksort(data_left, 0, data_left.size() - 1);
    quicksort(data_right, 0, data_right.size() - 1);
    for (int i = 0; i < data_left.size(); i++){
        // we subtract right from left but in absolute value
        subtraction.push_back(abs(data_left[i] - data_right[i]));
    }


    // part 2
    for(const auto& value : data_right){
        ++map[value];
    }
    for(const auto& left_value : data_left){
        int occurences = map[left_value];
        int result = occurences * left_value;
        results.push_back(result);
    }

    cout << accumulate(subtraction.begin(), subtraction.end(), 0) << endl;
    cout << accumulate(results.begin(), results.end(), 0) << endl;
    return 0;
}