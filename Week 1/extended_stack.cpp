#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class stackExt {
    public :
        vector <int> numbers;
        vector <int> max_numbers;

        void push(int a){
            int temp = a;
            numbers.push_back(a);
            if (max_numbers.size() > 0){temp = max_numbers.back();}
            if (max_numbers.size() == 0){max_numbers.push_back(temp);}
            else {
                if (temp > a){max_numbers.push_back(temp);}
                else {max_numbers.push_back(a);}
            }
        }
        int max(){
            return max_numbers.back();
        }
        void pop(){
            numbers.pop_back();
            max_numbers.pop_back();
        }
};

int main(){
    int q;
    cin >> q;
    string s;
    int v = 0;
    stackExt newstack;
    for (int i = 0; i < q; i++){
        v = -1;
        cin >> s;
        if (s == "push"){
            cin >> v;
            newstack.push(v);
        }
        else if (s == "max"){
            cout << newstack.max() << endl;
        }
        else {newstack.pop();}
    }
    return 0;
}
