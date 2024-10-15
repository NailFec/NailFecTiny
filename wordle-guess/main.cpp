// wordle - guess
#include <bits/stdc++.h>
using namespace std;
bool without[26], is[26], isnt[26];
struct ndStatus {
    // 0: don't know; -1: without; 1: isn't; 2: is
    int mode;
    bool is[5], isnt[5];
} status[26];
vector<string> words;

int main() {
    ifstream file("lessWords.txt");
    if(!file) return 0 * printf("NailERROR: cannot open file\n");
    string s;
    while(getline(file, s)) {
        if(s == "EOF") break;
        words.push_back(s);
    }
    printf("loaded %llu words\n", words.size());
    string guess = "nails";
    for(int iRole = 0; iRole < 6; iRole ++) {
        debug:
        printf("times #%d: ", iRole);
        cout << guess << endl;
        printf("wordle result (mode):");
        for(int i = 0, ia; i < 5; i ++) {
            scanf("%d", &ia);
            if(ia == 27) {
                printf("change word:");
                cin >> guess;
                goto debug;
            }
            status[guess[i] - 'a'].mode = ia;
            if(ia == -1)
                without[guess[i] - 'a'] = true;
            else if(ia == 1)
                isnt[guess[i] - 'a'] = true, status[guess[i] - 'a'].isnt[i] = true;
            else if(ia == 2)
                is[guess[i] - 'a'] = true, status[guess[i] - 'a'].is[i] = true;
            else
                return 0 * printf("NailERROR: invalid input mode\n");
        }
        for(string tryS : words) {
            bool can = true;
            for(int i = 0; i < 26; i ++) {
                if(without[i]) {
                    bool consist = false;
                    for(const char c : tryS)
                        if(c - 'a' == i) { consist = true; break; }
                    if(consist) { can = false; break; }
                }
                // if(!can) break;
                if(is[i]) {
                    for(int j = 0; j < 5; j ++) {
                        if(status[i].is[j])
                            if(tryS[j] - 'a' != i) { can = false; break; }
                    }
                }
                if(!can) break;
                if(isnt[i]) {
                    bool consist = false;
                    for(const char c : tryS)
                        if(c - 'a' == i) { consist = true; break; }
                    if(!consist) { can = false; break; }
                    for(int j = 0; j < 5; j ++) {
                        if(status[i].isnt[j])
                            if(tryS[j] - 'a' == i) { can = false; break; }
                    }
                }
                if(!can) break;
            }
            if(can) {
                if(iRole == 5) cout << "> " << tryS << endl;
                guess = tryS;
                vector<bool> checker(26, false);
                bool great = true;
                for(const char c : tryS)
                    if(checker[c - 'a']) {great = false; break; }
                    else checker[c - 'a'] = true;
                if(great) break;
            }
        }
    }
    return 0;
}