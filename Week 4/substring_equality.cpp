#include <bits/stdc++.h>

using namespace std;

static const int X = 259;
static const long long MODD_1 = 1000000007;
static const long long MODD_2 = 1000000009;

void fill_x_pow_i(long long* arr, const int len, const long long prime_p){
    arr[0] = 1;
    for (int i = 1; i < len; i++){
        arr[i] = arr[i - 1] * X;
        if (arr[i] >= prime_p){arr[i] %= prime_p;}
    }
}

void check_MODD(long long& number, const long long prime_p){
    if (number < 0) {number += prime_p;}
    if (number >= prime_p){number %= prime_p;}
}

int hash_string(const string& query, const int index, const long long prime_p, const long long* arr){
    int q_size = query.size();
    long long ans = 0;
    for (int i = index; i < q_size; i++){
        ans += query[i] * arr[i - index];
        check_MODD(ans, prime_p);
    }
    return ans;
}

long long my_multiply(const int a, long long b, const int times, const long long prime_p){
    for (int i = 0; i < times; i++){
        b *= a;
        check_MODD(b, prime_p);
    }
    return b;
}

int main(){
    string text;
    int q, a, b, l;
    cin >> text >> q;
    int text_len = text.size();
    long long x_pow_1[text_len], x_pow_2[text_len];
    vector <long long> text_hash_1, text_hash_2;

    text_hash_1.reserve(text_len);
    text_hash_2.reserve(text_len);

    fill_x_pow_i(x_pow_1, text_len, MODD_1);
    fill_x_pow_i(x_pow_2, text_len, MODD_2);

    text_hash_1[text_len - 1] = text[text_len - 1];
    text_hash_2[text_len - 1] = text[text_len - 1];

    for (int i = text_len - 2; i >= 0; i--){
        text_hash_1[i] = text[i] + X * text_hash_1[i + 1];
        text_hash_2[i] = text[i] + X * text_hash_2[i + 1];

        if (text_hash_1[i] >= MODD_1){text_hash_1[i] %= MODD_1;}
        if (text_hash_2[i] >= MODD_2){text_hash_2[i] %= MODD_2;}
    }

    while (q--){
        cin >> a >> b >> l;
        long long hash_a_1, hash_a_2, hash_b_1, hash_b_2;
        if (a + l == text_len){
            hash_a_1 = text_hash_1[a];
            hash_a_2 = text_hash_2[a];
        }
        else {
            hash_a_1 = (text_hash_1[a] - x_pow_1[l] * text_hash_1[a + l]) % MODD_1;
            hash_a_2 = (text_hash_2[a] - x_pow_2[l] * text_hash_2[a + l]) % MODD_2;
        }

        if (b + l == text_len){
            hash_b_1 = text_hash_1[b];
            hash_b_2 = text_hash_2[b];
        }
        else {
            hash_b_1 = (text_hash_1[b] - x_pow_1[l] * text_hash_1[b + l]) % MODD_1;
            hash_b_2 = (text_hash_2[b] - x_pow_2[l] * text_hash_2[b + l]) % MODD_2;
        }

        check_MODD(hash_a_1, MODD_1);
        check_MODD(hash_a_2, MODD_2);
        check_MODD(hash_b_1, MODD_1);
        check_MODD(hash_b_2, MODD_2);

        if (hash_a_1 == hash_b_1 && hash_a_2 == hash_b_2){
            cout << "Yes\n";
        }
        else {
            cout << "No\n";
        }

    }
    return 0;
}
