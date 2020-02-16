#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>

using namespace std;

int getMax(vector<int> vec) {
    int max = -10000;
    for (int i = 0; i < vec.size(); i++) {
        if (vec.at(i) > max) {
            max = vec.at(i);
        }
    }
    return max;
}

int getMin(vector<int> vec) {
    int min = 10000;
    for (int i = 0; i < vec.size(); i++) {
        if (vec.at(i) < min) {
            min = vec.at(i);
        }
    }
    return min;
}

void printVector(vector<int> vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec.at(i) << " ";
    }
    cout << endl;
}

int minMax(string input, bool max) {
    input.pop_back();
    input.erase(0,1);
    stack<int> openParentheses;
    vector<int> numbersToEvaluate;
    if (max) {
        cout << "Max: " << input << endl;
    } else {
        cout << "Min: " << input << endl;
    }

    for (int i = 0; i < input.length(); i++) {
        if (!isspace(input[i]) && isdigit(input[i]) && openParentheses.empty()) {
            int num = input[i] - '0';
            numbersToEvaluate.push_back(num);
        } else if (input[i] == '(') {
            openParentheses.push(i);
        } else if (input[i] == ')') {
            if (openParentheses.size() == 1) {
                string nextInput = input.substr(openParentheses.top(),i - openParentheses.top() + 1);
                numbersToEvaluate.push_back(minMax(nextInput, !max));
            }
            openParentheses.pop();
        } else if (input[i] == '-' && openParentheses.empty()) {
            int num = input[i + 1] - '0';
            num = 0 - num;
            numbersToEvaluate.push_back(num);
            i += 1;
        }
    }

    
    // printVector(numbersToEvaluate);

    if (max) {
        return getMax(numbersToEvaluate);
    } else {
        return getMin(numbersToEvaluate);
    }
    return 0;
}

int main(int argc, char *argv[])
{
  // check if there is more than one argument and use the second one
  //  (the first argument is the executable)
  if (argc > 1)
  {
    string arg1(argv[1]);
    cout << arg1 << endl;
    int finalAnswer =  minMax(arg1, true);
    cout << "Final answer: " << finalAnswer << endl;
  }
}
