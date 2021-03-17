#include <bits/stdc++.h>

using namespace std;

const int MAX_SIZE = (int)1e7;

int main(){
    int q;
    cin >> q;
    string command, name;
    int number;
    vector <string> contacts(MAX_SIZE, "not found");
    while (q--){
        cin >> command >> number;
        if (command == "add"){
            cin >> name;
            contacts[number] = name;
        }
        else if (command == "find"){
            cout << contacts[number] << "\n";
        }
        else if (command == "del"){
            contacts[number] = "not found";
        }
    }
    return 0;
}
