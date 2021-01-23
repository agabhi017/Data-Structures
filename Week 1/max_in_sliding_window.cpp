#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){
    int n, w;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    cin >> w;
    int local_maxima;
    queue <int> numbers;
    vector <int> maximas;
    int index = 0;
    while (index < n){
        while (index < n && numbers.size() < w){
            numbers.push(arr[index]);
            ++index;
        }
    }

    return 0;
}
