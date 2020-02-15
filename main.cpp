#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include<queue>
#include <cmath> 
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
  node() {
      vector<int> emptyState;
      vector<string> emptyPath;
      state = emptyState;
      hVal = 100000;
      depth = 0;
      path = emptyPath;
  }
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
        cout << "Front Node: " << endl; 
        printNode(currentFrontNode);
        
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
            node leftNode = node(stateAfterLeftMove, 0, leftDepth, leftPath);
            if (!vecsEqual(leftNode.state, currentFrontNode.state)) {
                processQueue.push(leftNode);
                // cout << "Pushed Left" << endl; 
            }

            vector<int> stateAfterRightMove = right(currentFrontNode.state);
            int rightDepth = currentFrontNode.depth++;
            vector<string> rightPath = currentFrontNode.path;
            rightPath.push_back("RIGHT");
            node rightNode = node(stateAfterRightMove, 0, rightDepth, rightPath);
            if (!vecsEqual(rightNode.state, currentFrontNode.state)) {
                processQueue.push(rightNode);
            }

            vector<int> stateAfterUpMove = up(currentFrontNode.state);
            int upDepth = currentFrontNode.depth++;
            vector<string> upPath = currentFrontNode.path;
            upPath.push_back("UP");
            node upNode = node(stateAfterUpMove, 0, upDepth, upPath);
            if (!vecsEqual(upNode.state, currentFrontNode.state)) {
                processQueue.push(upNode);
            }

            vector<int> stateAfterDownMove = down(currentFrontNode.state);
            int downDepth = currentFrontNode.depth++;
            vector<string> downPath = currentFrontNode.path;
            downPath.push_back("DOWN");
            node downNode = node(stateAfterDownMove, 0, downDepth, downPath);
            if (!vecsEqual(downNode.state, currentFrontNode.state)) {
                processQueue.push(downNode);
            }
        }
        processQueue.pop();
    }
    if (processQueue.empty()) {
        cout << "Never Found a solution..." << endl;
    }

}

int getH1(vector<int> currentState, vector<int> targetState) {
    // cout << "Getting H1..." << endl;
    int hVal = 0;
    for (int i = 0; i < currentState.size(); i++) {
        if (currentState.at(i) != targetState.at(i) && currentState.at(i) != 0) {
            hVal++;
        }
    }
    // cout << "hVal: " << hVal << endl << endl;
    return hVal;
}

int getH2(vector<int> currentState, vector<int> targetState) {
    // cout << "Getting H2..." << endl;
    int h2 = 0;
    for (int i = 0; i < currentState.size(); i++) {
        for (int j = 0; j < targetState.size(); j++) {
            if (currentState.at(i) == targetState.at(j) && currentState.at(i) != 0) {
                int horizontalDist = abs((i % 3) - (j % 3));
                int verticalDist = abs((i / 3) - (j / 3));
                h2 = h2 + horizontalDist + verticalDist;
                // cout << "Distance between i=" << i << " and j=" << j << " is:  " <<  horizontalDist + verticalDist << endl;
            }
        }
    }
    // cout << "H2 = " << h2 << endl;
    return h2;
}

int getHeuristic(node n, vector<int> targetState, string selectedHeuristic) {
    if (selectedHeuristic == "h1") {
        return getH1(n.state, targetState);
    } else {
        return getH2(n.state, targetState);
    }
}

bool isOppositeDirection(string d1, string d2) {
    if (d1 == "RIGHT" && d2 == "LEFT") {
        return true;
    }else if (d1 == "LEFT" && d2 == "RIGHT") {
        return true;
    } else if (d1 == "UP" && d2 == "DOWN") {
        return true;
    } else if (d1 == "DOWN" && d2 == "UP") {
        return true;
    } else {
        return false;
    }
}

bool stateAlreadyVisited(vector<int> state, vector<vector<int> > visitedStates) {
    for (int i= 0; i < visitedStates.size(); i++) {
        if (vecsEqual(state, visitedStates.at(i))) {
            return true;
        }
    }
    return false;
}

void greedy(vector<int> initialState, vector<int> targetState, string selectedHeuristic) {
    vector<string> path;
    node initialNode = node(initialState, 0, 0, path);
    initialNode.hVal = getHeuristic(initialNode, targetState, selectedHeuristic);
    queue<node> processQueue;
    processQueue.push(initialNode);
    vector<vector<int> > visitedStates;
    visitedStates.push_back(initialNode.state);

    while (!processQueue.empty()) {
        node currentFrontNode = processQueue.front();
        cout << "***Front Node: ***" << endl; 
        printNode(currentFrontNode);
        
        if (vecsEqual(currentFrontNode.state, targetState)) {
            cout << "Solution Found!" << endl;
            break;
            printNode(currentFrontNode);
        } else {
            // node nextNode = currentFrontNode;
            vector<node> possibleMoves;

            vector<int> stateAfterLeftMove = left(currentFrontNode.state);
            int leftDepth = currentFrontNode.depth + 1;
            vector<string> leftPath = currentFrontNode.path;
            leftPath.push_back("LEFT");
            node leftNode = node(stateAfterLeftMove, 0, leftDepth, leftPath);
            // cout << "Getting hVal for left move..." << endl;
            leftNode.hVal = getHeuristic(leftNode, targetState, selectedHeuristic);
            cout << "Left Node: " << endl;
            printNode(leftNode);
            if (!vecsEqual(leftNode.state, currentFrontNode.state)) { // If left move is possible
                cout << "Left move is valid" << endl;
                possibleMoves.push_back(leftNode);
            }

            vector<int> stateAfterRightMove = right(currentFrontNode.state);
            int rightDepth = currentFrontNode.depth + 1;
            vector<string> rightPath = currentFrontNode.path;
            rightPath.push_back("RIGHT");
            node rightNode = node(stateAfterRightMove, 0, rightDepth, rightPath);
            // cout << "Getting hVal for right move..." << endl;
            rightNode.hVal = getHeuristic(rightNode, targetState, selectedHeuristic);
            cout << "Right Node: " << endl;
            printNode(rightNode);
            if (!vecsEqual(rightNode.state, currentFrontNode.state)) { // If right move is possible
                cout << "Right move is valid" << endl;
                possibleMoves.push_back(rightNode);
            }

            vector<int> stateAfterUpMove = up(currentFrontNode.state);
            int upDepth = currentFrontNode.depth + 1;
            vector<string> upPath = currentFrontNode.path;
            upPath.push_back("UP");
            node upNode = node(stateAfterUpMove, 0, upDepth, upPath);
            // cout << "Getting hVal for up move..." << endl;
            upNode.hVal = getHeuristic(upNode, targetState, selectedHeuristic);
            cout << "Up Node: " << endl;
            printNode(upNode);
            if (!vecsEqual(upNode.state, currentFrontNode.state)) { // If up move is possible
                cout << "Up move is valid" << endl;
                possibleMoves.push_back(upNode);
            }

            vector<int> stateAfterDownMove = down(currentFrontNode.state);
            int downDepth = currentFrontNode.depth + 1;
            vector<string> downPath = currentFrontNode.path;
            downPath.push_back("DOWN");
            node downNode = node(stateAfterDownMove, 0, downDepth, downPath);
            // cout << "Getting hVal for down move..." << endl;
            downNode.hVal = getHeuristic(downNode, targetState, selectedHeuristic);
            cout << "Down node: " << endl;
            printNode(downNode);
            if (!vecsEqual(downNode.state, currentFrontNode.state)) { // If down move is possible
                cout << "Down move is valid" << endl;
                possibleMoves.push_back(downNode);
            }

            processQueue.pop();

            int minHVal = 10000;
            int index = -1;
            for (int i = 0; i < possibleMoves.size(); i++) {
                // cout << "MinVal: " << minHVal << endl;
                // cout << "moveVal: " << possibleMoves.at(i).hVal << endl;
                if (!stateAlreadyVisited(possibleMoves.at(i).state, visitedStates)) {
                    if (possibleMoves.at(i).hVal < minHVal) {
                        minHVal = possibleMoves.at(i).hVal;
                    }
                }
            }

            cout << "***Next Nodes to process***" << endl;
            for (int i = 0; i < possibleMoves.size(); i++) {
                if (!stateAlreadyVisited(possibleMoves.at(i).state, visitedStates)) {
                    if (possibleMoves.at(i).hVal == minHVal) {
                        printNode(possibleMoves.at(i));
                        processQueue.push(possibleMoves.at(i));
                        visitedStates.push_back(possibleMoves.at(i).state);
                        cout << "number of visited states: " << visitedStates.size() << endl;
                        cout << "number of nodes to process: " << processQueue.size() << endl;
                    }
                }
            }
            // int x;
            // cin >> x;
            //*** What to do in the case of ties???
        }
    }
}

void astar(vector<int> initialState, vector<int> targetState, string selectedHeuristic) {
    vector<string> path;
    vector<vector<int> > visitedStates;
    node initialNode = node(initialState, 0, 0, path);
    initialNode.hVal = getHeuristic(initialNode, targetState, selectedHeuristic);
    queue<node> processQueue;
    processQueue.push(initialNode);
    visitedStates.push_back(initialNode.state);

    while (!processQueue.empty()) {
        node currentFrontNode = processQueue.front();
        cout << "***Front Node: ***" << endl; 
        printNode(currentFrontNode);
        
        if (vecsEqual(currentFrontNode.state, targetState)) {
            cout << "Solution Found!" << endl;
            break;
            printNode(currentFrontNode);
        } else {
            // node nextNode = currentFrontNode;
            vector<node> possibleMoves;

            vector<int> stateAfterLeftMove = left(currentFrontNode.state);
            int leftDepth = currentFrontNode.depth + 1;
            vector<string> leftPath = currentFrontNode.path;
            leftPath.push_back("LEFT");
            node leftNode = node(stateAfterLeftMove, 0, leftDepth, leftPath);
            // cout << "Getting hVal for left move..." << endl;
            leftNode.hVal = getHeuristic(leftNode, targetState, selectedHeuristic);
            cout << "Left Node: " << endl;
            printNode(leftNode);
            if (!vecsEqual(leftNode.state, currentFrontNode.state)) { // If left move is possible
                cout << "Left move is valid" << endl;
                possibleMoves.push_back(leftNode);
            }

            vector<int> stateAfterRightMove = right(currentFrontNode.state);
            int rightDepth = currentFrontNode.depth + 1;
            vector<string> rightPath = currentFrontNode.path;
            rightPath.push_back("RIGHT");
            node rightNode = node(stateAfterRightMove, 0, rightDepth, rightPath);
            // cout << "Getting hVal for right move..." << endl;
            rightNode.hVal = getHeuristic(rightNode, targetState, selectedHeuristic);
            cout << "Right Node: " << endl;
            printNode(rightNode);
            if (!vecsEqual(rightNode.state, currentFrontNode.state)) { // If right move is possible
                cout << "Right move is valid" << endl;
                possibleMoves.push_back(rightNode);
            }

            vector<int> stateAfterUpMove = up(currentFrontNode.state);
            int upDepth = currentFrontNode.depth + 1;
            vector<string> upPath = currentFrontNode.path;
            upPath.push_back("UP");
            node upNode = node(stateAfterUpMove, 0, upDepth, upPath);
            // cout << "Getting hVal for up move..." << endl;
            upNode.hVal = getHeuristic(upNode, targetState, selectedHeuristic);
            cout << "Up Node: " << endl;
            printNode(upNode);
            if (!vecsEqual(upNode.state, currentFrontNode.state)) { // If up move is possible
                cout << "Up move is valid" << endl;
                possibleMoves.push_back(upNode);
            }

            vector<int> stateAfterDownMove = down(currentFrontNode.state);
            int downDepth = currentFrontNode.depth + 1;
            vector<string> downPath = currentFrontNode.path;
            downPath.push_back("DOWN");
            node downNode = node(stateAfterDownMove, 0, downDepth, downPath);
            // cout << "Getting hVal for down move..." << endl;
            downNode.hVal = getHeuristic(downNode, targetState, selectedHeuristic);
            cout << "Down node: " << endl;
            printNode(downNode);
            if (!vecsEqual(downNode.state, currentFrontNode.state)) { // If down move is possible
                cout << "Down move is valid" << endl;
                possibleMoves.push_back(downNode);
            }

            // From possible moves, find all that don't repeat.
            // Out of all possible moves that don't repeat any past moves, get min val

            processQueue.pop();

            int minHVal = 10000;
            int index = -1;
            for (int i = 0; i < possibleMoves.size(); i++) {
                // cout << "MinVal: " << minHVal << endl;
                // cout << "moveVal: " << possibleMoves.at(i).hVal << endl;
                if (!stateAlreadyVisited(possibleMoves.at(i).state, visitedStates)) {
                    if (possibleMoves.at(i).hVal + possibleMoves.at(i).depth < minHVal) {
                        minHVal = possibleMoves.at(i).hVal + possibleMoves.at(i).depth;
                    }
                }
            }

            cout << "***Next Nodes to process***" << endl;
            for (int i = 0; i < possibleMoves.size(); i++) {
                if (!stateAlreadyVisited(possibleMoves.at(i).state, visitedStates)) {
                    if (possibleMoves.at(i).hVal + possibleMoves.at(i).depth == minHVal) {
                        printNode(possibleMoves.at(i));
                        processQueue.push(possibleMoves.at(i));
                        visitedStates.push_back(possibleMoves.at(i).state);
                        cout << "number of visited states: " << visitedStates.size() << endl;
                        cout << "number of nodes to process: " << processQueue.size() << endl;
                    }
                }
            }
        }
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

    // vector<int> targetState; 
    // targetState.push_back(0);
    // targetState.push_back(1);
    // targetState.push_back(2);
    // targetState.push_back(3);
    // targetState.push_back(4);
    // targetState.push_back(5);
    // targetState.push_back(6);
    // targetState.push_back(7);
    // targetState.push_back(8);

    // Perform search

    cout << "***Target Vector***" << endl;
    printVector(targetState);

    if (selectedAlgorithm == "bfs") {
        bfs(initialState, targetState);
    } else if (selectedAlgorithm == "greedy") {
        greedy(initialState, targetState, selectedHeuristic);
    } else if (selectedAlgorithm == "astar") {
        astar(initialState, targetState, selectedHeuristic);
    }

  
    return 0; 
} 

