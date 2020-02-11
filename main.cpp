#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include<queue>
using namespace std;

// g++ -o main main.cpp
// Format for input: bfs 123456780 
// No spaces, no parenthesis, etc
// Goal state = (1 2 3 8 0 4 7 6 5)

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

bool vecsEqual(vector<int> vec1, vector<int> vec2) {
    // cout << "vecs equal..." << endl;
    // cout << "vec1: ";
    // printVector(vec1);
    // cout << "vec2: ";
    // printVector(vec2);
    if (vec1.size() != vec2.size()) { return false; }
    for (int i = 0; i < vec1.size(); i++) {
        if (vec1.at(i) != vec2.at(i)) { return false; }
    }
    return true;
}

int getIndex(vector<int> vec, int x) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec.at(i) == x) {
            return i;
        }
    }
    return -1;
}

// ***Node Implementation***

struct node {
  vector<int> state;
  int hVal; // Use h1 (number of tiles out-of-place), and h2 (sum of manhattan distance) for those requiring heuristics (make the functions to take the function as an argument)
  int depth;
  vector<string> path;
  node(vector<int> s, int h, int d, vector<string> p){
      state = s;
      hVal = h;
      depth = d;
      path = p;
  };
};

void printNode(node n) {
    cout << "state: ";
    printVector(n.state);
    cout << "hVal: " << n.hVal << endl;
    cout << "depth: " << n.depth << endl;
    cout << "path: ";
    printVector(n.path);
    cout << endl << endl;
}

// ***Algorithms***

vector<int> left(vector<int> vec) {
    int indexOfZero = getIndex(vec, 0);
    if (indexOfZero <= 0 || indexOfZero == 3 || indexOfZero == 6) { return vec; }

    vec.at(indexOfZero) = vec.at(indexOfZero - 1);
    vec.at(indexOfZero - 1) = 0;
    return vec;
}

vector<int> right(vector<int> vec) {
    int indexOfZero = getIndex(vec, 0);
    if (indexOfZero < 0 || indexOfZero == 8 || indexOfZero == 5 || indexOfZero == 2) { return vec; }

    vec.at(indexOfZero) = vec.at(indexOfZero + 1);
    vec.at(indexOfZero + 1) = 0;
    return vec;
}

vector<int> up(vector<int> vec) {
    int indexOfZero = getIndex(vec, 0);
    if (indexOfZero < 3) { return vec; }

    vec.at(indexOfZero) = vec.at(indexOfZero - 3);
    vec.at(indexOfZero - 3) = 0;
    return vec;
}

vector<int> down(vector<int> vec) {
    int indexOfZero = getIndex(vec, 0);
    if (indexOfZero < 0 || indexOfZero > 5) { return vec; }

    vec.at(indexOfZero) = vec.at(indexOfZero + 3);
    vec.at(indexOfZero + 3) = 0;
    return vec;
}

void bfs(vector<int> initialState, vector<int> targetState) {
    vector<string> path;
    node initialNode = node(initialState, 0, 0, path);
    queue<node> processQueue;
    processQueue.push(initialNode);

    while(!processQueue.empty()) {

        node currentFrontNode = processQueue.front();
        // cout << "Front Node: " << endl; 
        // printNode(currentFrontNode);
        
        if (vecsEqual(currentFrontNode.state, targetState)) {
            cout << "Solution Found!" << endl;
            break;
            printNode(currentFrontNode);
        } else {
            //Push all possible children
            // cout << "No solution yet..." << endl;

            vector<int> stateAfterLeftMove = left(currentFrontNode.state);
            int leftDepth = currentFrontNode.depth++;
            vector<string> leftPath = currentFrontNode.path;
            leftPath.push_back("LEFT");
            node leftNode = node(stateAfterLeftMove, leftDepth, 0, leftPath);
            if (!vecsEqual(leftNode.state, currentFrontNode.state)) {
                processQueue.push(leftNode);
                // cout << "Pushed Left" << endl; 
            }

            vector<int> stateAfterRightMove = right(currentFrontNode.state);
            int rightDepth = currentFrontNode.depth++;
            vector<string> rightPath = currentFrontNode.path;
            rightPath.push_back("RIGHT");
            node rightNode = node(stateAfterRightMove, rightDepth, 0, rightPath);
            if (!vecsEqual(rightNode.state, currentFrontNode.state)) {
                processQueue.push(rightNode);
                // cout << "Pushed right" << endl;
            }

            vector<int> stateAfterUpMove = up(currentFrontNode.state);
            int upDepth = currentFrontNode.depth++;
            vector<string> upPath = currentFrontNode.path;
            upPath.push_back("UP");
            node upNode = node(stateAfterUpMove, upDepth, 0, upPath);
            if (!vecsEqual(upNode.state, currentFrontNode.state)) {
                processQueue.push(upNode);
                // cout << "Pushed up" << endl;
            }

            vector<int> stateAfterDownMove = down(currentFrontNode.state);
            int downDepth = currentFrontNode.depth++;
            vector<string> downPath = currentFrontNode.path;
            downPath.push_back("DOWN");
            node downNode = node(stateAfterDownMove, downDepth, 0, downPath);
            if (!vecsEqual(downNode.state, currentFrontNode.state)) {
                processQueue.push(downNode);
                // cout << "Pushed down" << endl;
            }
        }
        processQueue.pop();
        // int x;
        // cin >> x;
    }
    if (processQueue.empty()) {
        cout << "Never Found a solution..." << endl;
    }

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

    // Configure final state;

    vector<int> targetState; 
    targetState.push_back(1);
    targetState.push_back(2);
    targetState.push_back(3);
    targetState.push_back(8);
    targetState.push_back(0);
    targetState.push_back(4);
    targetState.push_back(7);
    targetState.push_back(6);
    targetState.push_back(5);

    // Perform search

    if (selectedAlgorithm == "bfs") {
        bfs(initialState, targetState);
    }

  
    return 0; 
} 

