#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main (){
    string s;
    cin >> s;
    int s_len = s.length();
    vector <char> braces;
    vector <int> op_index;
    int mistakes = 0;
    int index = 1;
    for (int i = 0; i < s_len; i++){
        if (s[i] == '[' || s[i] == '{' || s[i] == '('){braces.push_back(s[i]); op_index.push_back(i + 1);}
        else if (s[i] == ']' || s[i] == '}' || s[i] == ')') {
            if (braces.size() == 0){++mistakes; index = i + 1; break;}
            else if (braces.back() == '[' && s[i] != ']' || braces.back() == '{' && s[i] != '}' || braces.back() == '(' && s[i] != ')') {
                ++mistakes;
                index = i + 1;
                break;
            }
            else {braces.pop_back();op_index.pop_back();}
        }
    }
    if (mistakes == 0 && braces.size() == 0){cout << "Success" ;}
    else if (mistakes == 0 && braces.size() > 0){cout << op_index.front();}
    else {cout << index ;}
    return 0;
}
