#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void my_swap(vector <int>& num, int i, int j){
    int temp = num[i];
    num[i] = num[j];
    num[j] = temp;
}

int main(){
    int n;
    cin >> n;
    vector <int> num;
    num.resize(n);
    for (int i = 0; i <n; i++){
        cin >> num[i];
    }
    vector <int> index_a;
    vector <int> index_b;
    int num_swaps = 0;
    int child, parent, parent_index, child_index;
    for (int i = n - 1; i >= 0; i--){
        child_index = i;
        parent_index = floor((int)((float)(child_index - 1) / 2));
        while (parent_index >= 0){
            parent = num[parent_index];
            child = num[child_index];
            if (child < parent){
                my_swap(num, child_index, parent_index);
                ++num_swaps;
                index_a.push_back(parent_index);
                index_b.push_back(child_index);
                child_index = parent_index;
                parent_index = floor((int)((float)(child_index - 1) / 2));
            }
            else {
                parent_index = -1;
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
