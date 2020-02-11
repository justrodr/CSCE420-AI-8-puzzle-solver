#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include<tuple>
using namespace std;

// g++ -o main main.cpp
// Format for input: bfs 123456780 
// No spaces, no parenthesis, etc

// ***Node Implementation***

struct node {
  vector<int> currentState;
  int hVal; // Use h1 (number of tiles out-of-place), and h2 (sum of manhattan distance) for those requiring heuristics (make the functions to take the function as an argument)
  int depth;
  vector<string> path;
  node(vector<int> state, int h, int d, vector<string> p){
      currentState = state;
      hVal = h;
      depth = d;
      path = p;
  };
};

// ***Algorithms***

void bfs(vector<int> initialState) {
    vector<string> path;
    node initialNode = node(initialState, 0, 0, path);

    
}

// ***Helpers***

void printVector(vector<string> vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec.at(i) << " ";
    }
    cout << endl;
}

void printVector(vector<int> vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec.at(i) << " ";
    }
    cout << endl;
}

vector<int> strToVec(string input) {
    vector<int> vec;
    for (int i = 0; i < input.length(); i++) {
        int x = input[i] - '0';
        vec.push_back(x);
    }
    return vec;
}

int main(int argc, char** argv) 
{ 

    //  Take inputs

    if (argc < 3) { return 0; }
    vector<string> inputs;
    for (int i = 1; i < argc; ++i) { 
        istringstream ss(argv[i]);
        string x;
        if (!(ss >> x)) {
            std::cerr << "Invalid number: " << argv[1] << '\n';
        } else if (!ss.eof()) {
            std::cerr << "Trailing characters after number: " << argv[1] << '\n';
        } else {
            inputs.push_back(x);
        }
    }

    //  Select algorithm & process initial state

    cout << "***INPUTS***" << endl; 

    string selectedAlgorithm = inputs.at(0);
    string initialStateStr = inputs.at(1);
    string selectedHeuristic = "";
    if (inputs.size() > 2) {
        selectedHeuristic = inputs.at(2);
    }

    cout << "Selected Algorithm: " << selectedAlgorithm << endl;
    vector<int> initialState = strToVec(inputs.at(1));
    cout << "Initial State: ";
    printVector(initialState);
    cout << "Selected Heuristic: " << selectedHeuristic << endl;
    cout << endl;

    // Perform search

    if (selectedAlgorithm == "bfs") {
        bfs(initialState);
    }

  
    return 0; 
} 

