#include <bits/stdc++.h>

using namespace std;

struct my_thread{
    int key;
    long long priority;
};

void my_swap(vector <my_thread>& arr, int i, int j){
    my_thread temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int main(){
    int n, t;
    cin >> n >> t;

    long long t_time;
    vector <my_thread> thread_pr(n);

    for (int i = 0; i < n; i++){
        thread_pr[i].key = i;
        thread_pr[i].priority = 0;
    }

    int thread_key;
    long long p_time;
    while (t--){
        cin >> t_time;
        thread_key = thread_pr[0].key;
        p_time = thread_pr[0].priority;

        cout << thread_key << " " << p_time << endl;
        thread_pr[0].priority += t_time;

        int parent_index = 0, l_child_index, r_child_index, min_child_index;
        long long parent, l_child = -1, r_child = -1, min_child = -1;

        while (parent_index < n){
            parent = thread_pr[parent_index].priority;
            l_child = -1;
            r_child = -1;
            min_child = -1;

            l_child_index = 2 * parent_index + 1;
            r_child_index = 2 * parent_index + 2;

            if (l_child_index < n){l_child = thread_pr[l_child_index].priority;}
            if (r_child_index < n){r_child = thread_pr[r_child_index].priority;}

            if (l_child == r_child && r_child_index < n){
                min_child = l_child;
                if (thread_pr[l_child_index].key < thread_pr[r_child_index].key){min_child_index = l_child_index;}
                else {min_child_index = r_child_index;}
            }
            else if (l_child < r_child || r_child == -1){
                min_child = l_child;
                min_child_index = l_child_index;
            }
            else if (l_child > r_child){
                min_child = r_child;
                min_child_index = r_child_index;
            }

            if (min_child == -1){break;}

            if (parent > min_child || (parent == min_child && thread_pr[parent_index].key > thread_pr[min_child_index].key)){
                my_swap (thread_pr, parent_index, min_child_index);
                parent_index = min_child_index;
            }
            else {parent_index = n;}
        }
    }

    return 0;
}
