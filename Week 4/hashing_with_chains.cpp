#include <bits/stdc++.h>

using namespace std;

static const int X = 263;
static const int MODD = 1000000007;
static const int MAX_SIZE = 100001;

int hash_string(const string& query){
    int q_size = query.size();
    long long ans = 0;
    for (int i = 0; i < q_size; i++){
        long long temp = 1;
        for (int j = 1; j <= i; j++){
            temp *= X;
            if (temp >= MODD) {temp %= MODD;}
        }
        ans += query[i] * temp;
        if (ans >= MODD){
            ans %= MODD;
        }
    }
    return ans;
}

int find_string(const deque <string>& my_list, const string& query){
    int l_size = my_list.size();
    for (int i = 0; i < l_size; i++){
        if (my_list[i] == query){return i;}
    }
    return -1;
}

void print_list(const deque <string>& my_list){
    int l_size = my_list.size();
    for (int i = 0; i < l_size; i++){
        cout << my_list[i] << " ";
    }
    cout << "\n";
}

int main(){
    int m, q;
    cin >> m >> q;
    deque <deque <string>> my_container(MAX_SIZE);
    string command, query;
    int index;
    while (q--){
        cin >> command;
        if (command == "check"){
            cin >> index;
            print_list(my_container[index]);
        }
        else {
            cin >> query;
            int q_hash = hash_string(query) % m;
            int found_string = find_string(my_container[q_hash], query);

            if (command == "add"){
                if (found_string == -1) {my_container[q_hash].push_front(query);}
            }
            else if (command == "find"){
                if (found_string != -1) {cout << "yes\n";}
                else {cout << "no\n";}
            }
            else if (command == "del"){
                if (found_string != -1){my_container[q_hash].erase(my_container[q_hash].begin() + found_string);}
            }
        }
    }
    return 0;
}
