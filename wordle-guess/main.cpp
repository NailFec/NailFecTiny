// wordle - guess
// by NailFec 20241014 finished in a rush
// TODO: guess more possible words first
#include <bits/stdc++.h>
using namespace std;
bool without[26], isnt[26];
struct ndStatus {
    // 0: don't know; -1: without; 1: isn't; 2: is
    int mode;
    int is;
    bool isnt[5];
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
        printf("times #%d: ", iRole);
        cout << guess << endl;
        printf("wordle result (mode): ");
        for(int i = 0, ia; i < 5; i ++) {
            scanf("%d", &ia);
            status[guess[i] - 'a'].mode = ia;
            if(ia == -1) without[guess[i] - 'a'] = true;
            else if(ia == 1) status[guess[i] - 'a'].isnt[i] = true, isnt[guess[i] - 'a'] = true;
            else if(ia == 2) status[guess[i] - 'a'].is = i;
            else return 0 * printf("NailERROR: invalid input mode\n");
        }
        cout << endl;
        for(string tryS : words) {
            bool can = true;
            for(int i = 0; i < 26; i ++) if(isnt[i]) {
                bool consist = false;
                for (const char c : tryS)
                    if(c - 'a' == i) { consist = true; break; }
                if(!consist) { can = false; break; }
            }
            for(const char c : tryS) {
                if(without[c - 'a']) { can = false; break; }
                if(status[c - 'a'].mode == 0) continue;
                if(status[c - 'a'].mode == 2)
                    if(tryS[status[c - 'a'].is] != c) { can = false; break; }
                if(status[c - 'a'].mode == 1)
                    for(int i = 0; i < 5; i ++)
                        if(status[c - 'a'].isnt[i] && tryS[i] == c) { can = false; break; }
            }
            if(can) {
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