#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void my_swap(vector <long long>& num, int i, int j){
    long long temp = num[i];
    num[i] = num[j];
    num[j] = temp;
}

int main(){
    int n;
    cin >> n;
    vector <long long> num;
    num.resize(n);
    for (int i = 0; i <n; i++){
        cin >> num[i];
    }
    vector <int> index_a;
    vector <int> index_b;
    int num_swaps = 0;
    int parent, parent_index, l_child_index, r_child_index, min_child, l_child, r_child, min_child_index;
    for (int i = (int)floor((float)(n) /2); i >= 0; i--){
        parent_index = i;

        while (parent_index < n){
            parent = num[parent_index];
            l_child_index = 2 * parent_index + 1;
            r_child_index = 2 * parent_index + 2;
            l_child = -1;
            r_child = -1;

            if (l_child_index < n){l_child = num[l_child_index];}
            else {min_child = -1;}

            if (r_child_index < n){r_child = num[r_child_index];}
            else {min_child = max(-1, l_child);}

            if (l_child >= 0 && r_child >= 0 && l_child > r_child){
                min_child = r_child;
                min_child_index = r_child_index;
            }
            else {
                min_child = l_child;
                min_child_index = l_child_index;
            }
            if (min_child < parent && min_child >= 0){
                my_swap(num, min_child_index, parent_index);
                ++num_swaps;
                index_a.push_back(parent_index);
                index_b.push_back(min_child_index);
                parent_index = min_child_index;
            }
            else {
                parent_index = n;
            }
        }
    }
    cout << num_swaps << endl;
    if (num_swaps > 0){
        for (auto i = 0; i < index_a.size(); i++){
            cout << index_a[i] << " " << index_b[i] << endl;
        }
    }
    return 0;
}
