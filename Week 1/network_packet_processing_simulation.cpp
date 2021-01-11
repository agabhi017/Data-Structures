#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){
    int s, n;
    cin >> s >> n;
    int finish_time = 0;
    queue <int> packet_times;
    vector <int> process_times;
    process_times.resize(n);
    int local_time = 0;
    fill_n(process_times.begin(), n, -1);

    for (int i = 0; i < n; i++){
        int t, p;
        cin >> t >> p;
        if (packet_times.size() > 0){
            local_time = packet_times.front();
            while (t >= local_time){
                packet_times.pop();
                if (packet_times.size() > 0) {local_time = packet_times.front();}
                else {break;}
            }
        }
        if (packet_times.size() < s){
            if (t < finish_time){finish_time += p;}
            else {finish_time = p + t;}
            packet_times.push(finish_time);
            process_times[i] = finish_time - p;
        }
    }
    for (int i = 0; i < n; i++){
        cout << process_times[i] << endl;
    }
    return 0;
}
