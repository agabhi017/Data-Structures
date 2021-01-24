#include <bits/stdc++.h>

using namespace std;

struct my_table{
    int size_;
    int key_;
    my_table* s_link;
    my_table(){
        size_ = 0;
        s_link = nullptr;
        key_ = -1;
    }
};

int find_parent(vector <my_table>& vec, int index){
    int parent;
    if (vec[index - 1].s_link == nullptr){return index;}
    else {
        parent = find_parent(vec, vec[index - 1].s_link->key_ + 1);
        vec[index - 1].s_link = &vec[parent - 1];
        return parent;
    }
}

int main(){
    int n, q;
    cin >> n >> q;
    vector <my_table> tab_list (n);
    int max_size = 0;

    for (int i = 0; i < n; i++){
        cin >> tab_list[i].size_;
        tab_list[i].key_ = i;
        if (tab_list[i].size_ > max_size){max_size = tab_list[i].size_;}
    }
    int src, dest;

    while (q--){
        cin >> dest >> src;

        src = find_parent(tab_list, src);
        dest = find_parent(tab_list, dest);

        if (dest != src){
            tab_list[dest - 1].size_ += tab_list[src - 1].size_;
            tab_list[src - 1].size_ = 0;
            tab_list[src - 1].s_link = &tab_list[dest - 1];
        }

        if (tab_list[dest - 1].size_ > max_size){max_size = tab_list[dest - 1].size_;}

        cout << max_size << endl;
    }
    return 0;
}
