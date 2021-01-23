#include <iostream>
#include <vector>

using namespace std;

void my_swap(vector <long long>& threads, int i, int j){
    int temp = threads[i];
    threads[i] = threads[j];
    threads[j] = temp;
}

//approach -

int main(){
    int n, m;
    cin >> n >> m;
    vector <long long> p_times(m); //stores the processing times of given tasks
    vector <long long> thread_queue(n); //stores the current instance of the queue in which threads are available
    vector <long long> thread_priority(n, 0);  //stores the priority of each thread - simply the sum of processing times of all tasks assigned to it

    for (int i = 0; i < n; i++){
        thread_queue[i] = i;
    }

    cout << thread_priority[0] << thread_priority[1] << endl;

    for (int i = 0; i < m; i++){
        cin >> p_times[i];
    }

    int thread_index, process_time;
    int l_child_index, r_child_index, l_child, r_child, min_child_index, min_child;

    for (int i = 0; i < m; i++){        //iterating over the given tasks
        thread_index = thread_queue[0];  //picking the thread which is in the front of the thread queue
        process_time = thread_priority[thread_index];  //time in seconds when a given thread will start processing the given task
        cout << thread_index << " " << process_time << endl;
        thread_priority[thread_index] += p_times[i]; //updating the priority of the thread once the task is assigned to it

        for (int i = 0; i < n; i++){cout << "thread_status" << endl; cout << thread_queue[i] << " " << thread_priority[i] << endl;}

        int index = 0, parent = thread_priority[thread_index];
        l_child = -1;
        r_child = -1;
        while (index < n){
            l_child_index = 2 * index + 1;
            r_child_index = 2 * index + 2;

            if (l_child_index < n){l_child = thread_priority[l_child_index];}
            else {min_child = -1;}

            if (r_child_index < n){r_child = thread_priority[r_child_index];}
            else {min_child = max(-1, l_child);}

            if (l_child >= 0 && r_child >= 0){
                if (l_child > r_child){
                    min_child = r_child;
                    min_child_index = r_child_index;
                }
                else if (l_child < r_child){
                    min_child = l_child;
                    min_child_index = l_child_index;
                }
                else {
                    min_child = l_child;
                    min_child_index = min(l_child_index, r_child_index);
                }
            }

            if (min_child < parent && min_child >= 0){
                my_swap(thread_queue, index, min_child_index);
                index = min_child_index;
            }
            else if (min_child == parent && thread_queue[index] > thread_queue[min_child_index]){
                my_swap(thread_queue, index, min_child_index);
                index = min_child_index;
            }
            else {index = n;}
        }
    }
    return 0;
}
