#include <bits/stdc++.h>

using namespace std;

//defining constants
static const long long X_1 = 19;
static const long long X_2 = 29;
static const long long MODD_1 = 1000000007;
static const long long MODD_2 = 1000000009;
static const int MAX_SIZE_HASH = 1000000010;
static const int MAX_SIZE_POW = 100001;

//constants for integer hashing
static const int X = 263;
static const int A = 17;
static const int B = 14017;
static const int MODD_P = 1000000021;
static const int M = 100001;

static long long hash_integer(long long number){
    long long ans = ((A * number + B) % MODD_P) % M;
    return ans;
}

static void fill_x_pow_i(vector <long long>& arr, const int x, const long long prime_p){
    arr[0] = 1;
    for (int i = 1; i < MAX_SIZE_POW; i++){
        arr[i] = arr[i - 1] * x;
        if (arr[i] >= prime_p){arr[i] %= prime_p;}
    }
}

static void check_MODD(long long& number, const long long prime_p){
    if (number < 0) {number += prime_p;}
    if (number >= prime_p){number %= prime_p;}
}

static long long hash_string(const string& text, const int index, const int len, const vector <long long>& x_pow, const long long prime_p){
    long long ans = 0;
    for (int i = index; i < index + len; i++){
        ans += (text[i] * x_pow[i - index]) % prime_p;
        if (ans >= prime_p){ans %= prime_p;}
    }

    return ans;
}

static void clear_hash_array(vector <vector <pair <int, long long> > >& hash_array){
    int arr_size = hash_array.size();
    for (int i = 0; i < arr_size; i++){
        if (hash_array[i].size() > 0) {hash_array[i].clear();}
    }
}

static void fill_hash_array(vector <vector <pair <int, long long> > >& hash_array, const long long string_hash, const int str_index){
    int index = hash_integer(string_hash);
    hash_array[index].push_back({str_index, string_hash});
}

static void precompute_hashes(vector <vector <pair <int, long long> > >& hash_array, const string& text, const int len, const vector <long long>& x_pow, const long long prime_p){
    clear_hash_array(hash_array);

    int text_len = text.size();
    long long prev_hash = hash_string(text, text_len - len, len, x_pow, prime_p);
    fill_hash_array(hash_array, prev_hash, text_len - len);

    long long new_hash;
    for (int i = text_len - len - 1; i >= 0; i--){
        new_hash = (x_pow[1] * prev_hash + text[i] - (x_pow[len] * text[i + len]) % prime_p) % prime_p;
        check_MODD(new_hash, prime_p);
        prev_hash = new_hash;
        fill_hash_array(hash_array, prev_hash, i);
    }
}

static void find_hash(const vector <vector <pair <int, long long> > >& compare_hash, const long long string_hash, const int str_index, set <pair <int, int>>& ans){
    int index = hash_integer(string_hash);
    for (int i = 0; i < compare_hash[index].size(); i++){
        if (compare_hash[index][i].second == string_hash){
            ans.insert({compare_hash[index][i].first, str_index});
        }
    }
}

static set <pair <int, int> > check_hashes(const vector <vector <pair <int, long long> > >& compare_hash, const string& pattern, const int len, const vector <long long>& x_pow, const long long prime_p){
    set <pair <int, int> > ans;

    int pattern_len = pattern.size();
    long long prev_hash = hash_string(pattern, pattern_len - len, len, x_pow, prime_p);
    find_hash(compare_hash, prev_hash, pattern_len - len, ans);

    long long new_hash;
    for (int i = pattern_len - len - 1; i >= 0; i--){
        new_hash = (x_pow[1] * prev_hash + pattern[i] - (x_pow[len] * pattern[i + len]) % prime_p) % prime_p;
        check_MODD(new_hash, prime_p);
        prev_hash = new_hash;
        find_hash(compare_hash, prev_hash, i, ans);
    }
    return ans;
}

static void search_substr(pair <int, pair <int, int> >& ans, int left, int right, const string& s_a, const string& s_b, vector <vector <pair <int, long long> > >& arr1, vector <vector <pair <int, long long> > >& arr2, const vector <long long>& x_pow_1, const vector <long long>& x_pow_2){
    if (left > right){
        return;
    }
    int mid = (left + right) / 2;
    set <pair <int, int> > temp_ans_1, temp_ans_2;

    precompute_hashes(arr1, s_a, mid + 1, x_pow_1, MODD_1);
    precompute_hashes(arr2, s_a, mid + 1, x_pow_2, MODD_2);

    temp_ans_1 = check_hashes(arr1, s_b, mid + 1, x_pow_1, MODD_1);
    if (!temp_ans_1.empty()){
        //check for second hash function only if first matches
        temp_ans_2 = check_hashes(arr2, s_b, mid + 1, x_pow_2, MODD_2);
    }

    if (!temp_ans_1.empty() && !temp_ans_2.empty()){
        for (auto itr = temp_ans_1.begin(); itr != temp_ans_1.end(); itr++){
            if (temp_ans_2.find(*itr) != temp_ans_2.end()){
                ans.first = mid + 1;
                ans.second = *itr;
                break;
            }
        }

        left = mid + 1;
        search_substr(ans, left, right, s_a, s_b, arr1, arr2, x_pow_1, x_pow_2);
    }
    else if (temp_ans_1.empty()){
        right = mid - 1;
        search_substr(ans, left, right, s_a, s_b, arr1, arr2, x_pow_1, x_pow_2);
    }
}


int main(){
    string s_a, s_b;
    //vector of vectors of pairs of int and long long for storing string hashes and indices
    vector <vector <pair <int, long long> > > hash_lookup_1, hash_lookup_2;
    hash_lookup_1.reserve(M);
    hash_lookup_2.reserve(M);

    //pre-computing pow(x, i) for both hash functions
    vector <long long> x_pow_1, x_pow_2;
    x_pow_1.reserve(MAX_SIZE_POW);
    x_pow_2.reserve(MAX_SIZE_POW);

    fill_x_pow_i(x_pow_1, X_1, MODD_1);
    fill_x_pow_i(x_pow_2, X_2, MODD_2);

    while (cin >> s_a >> s_b){
        pair <int, pair <int, int> > ans;
        vector <vector <pair <int, long long> > > hash_lookup_1, hash_lookup_2;
        hash_lookup_1.reserve(M);
        hash_lookup_2.reserve(M);
        ans.first = 0;
        ans.second = {0, 0};
        int len_a = s_a.size();
        int len_b = s_b.size();
        if (len_a <= len_b){
            search_substr(ans, 0, len_a - 1, s_a, s_b, hash_lookup_1, hash_lookup_2, x_pow_1, x_pow_2);
            cout << ans.second.first << " " << ans.second.second << " " << ans.first << "\n";
        }
        else {
            search_substr(ans, 0, len_b - 1, s_b, s_a, hash_lookup_1, hash_lookup_2, x_pow_1, x_pow_2);
            cout << ans.second.second << " " << ans.second.first << " " << ans.first << "\n";
        }
    }

    return 0;
}
