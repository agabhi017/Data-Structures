#include <bits/stdc++.h>

using namespace std;

static const int X = 1;
static const int MODD = 1000000007;

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

bool are_equal(const string& text, const string& pattern, const int index){
    int str_len = pattern.size();
    for (int i = index; i < index + str_len; i++){
        if (text[i] != pattern[i - index]){return false;}
    }
    return true;
}

int main(){
    string pattern, text;
    cin >> pattern >> text;

    int text_len = text.size();
    int pattern_len = pattern.size();
    int pattern_hash = hash_string(pattern);
    long long text_hash[text_len - pattern_len + 1];

    long long Xp = 1;
    for (int i = 1; i <= pattern_len; i++){
        Xp *= X;
        if (Xp >= MODD){
            Xp %= MODD;
        }
    }

    text_hash[text_len - pattern_len] = hash_string(text.substr(text_len - pattern_len, pattern_len));
    for (int i = text_len - pattern_len - 1; i >= 0; i--){
        text_hash[i] = (X * text_hash[i + 1]) % MODD;
        text_hash[i] += ((text[i] - Xp * text[i + pattern_len]) % MODD + MODD) % MODD;

        if (text_hash[i] >= MODD){
            text_hash[i] %= MODD;
        }
    }

    vector <int> ans;
    for (int i = 0; i < text_len - pattern_len + 1; i++){
        if (text_hash[i] != pattern_hash){
            continue;
        }
        else {
            if (are_equal(text, pattern, i)){
                ans.push_back(i);
            }
        }
    }

    for (int i = 0; i < (int)ans.size(); i++){
        cout << ans[i] << " ";
    }

    return 0;
}
