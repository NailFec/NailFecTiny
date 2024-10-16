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
vector<string> allGuesses, betterGuesses;

bool checkForm(const string &word) {
    if(word.size() != 5) return false;
    for(const char c : word)
        if(!(c >= 'a' && c <= 'z')) return false;
    return true;
}

bool ifValid(const string& tryS) {
    for(int i = 0; i < 26; i ++) {
        if(without[i] && !is[i]) {
            bool consist = false;
            for(const char c : tryS)
                if(c - 'a' == i) { consist = true; break; }
            if(consist) return false;
        }
        if(is[i]) {
            for(int j = 0; j < 5; j ++) {
                if(status[i].is[j])
                    if(tryS[j] - 'a' != i) return false;
            }
        }
        if(isnt[i] && !is[i]) {
            bool consist = false;
            for(const char c : tryS)
                if(c - 'a' == i) { consist = true; break; }
            if(!consist) return false;
            for(int j = 0; j < 5; j ++) {
                if(status[i].isnt[j])
                    if(tryS[j] - 'a' == i) return false;
            }
        }
    }
    return true;
}

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
    for(int iRole = 0; ; iRole ++) {
        debug:
        printf("times #%d: ", iRole);
        cout << guess << "; ";
        printf("with %llu guesses\n", allGuesses.size());
        printf("wordle result (mode):");
        for(int i = 0, ia; i < 5; i ++) {
            scanf("%d", &ia);
            if(ia == 27) {
                printf("change word:");
                while(cin >> guess && !checkForm(guess))
                    return 0 * printf("NailERROR: not a valid form of word\n");
                goto debug;
            }
            else if(ia == 28) {
                for(const string& guesses : allGuesses)
                    cout << "> " << guesses << endl;
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
        allGuesses.clear(), betterGuesses.clear();
        for(const string& tryS : words /*allGuesses*/) {
            if(!ifValid(tryS)) continue;
            allGuesses.push_back(tryS);
            vector<bool> checker(26, false);
            bool great = true;
            for(const char c : tryS)
                if(checker[c - 'a']) {great = false; break; }
                else checker[c - 'a'] = true;
            if(great) betterGuesses.push_back(tryS);
        }
        if(allGuesses.empty())
            return 0 * printf("NailERROR: no valid wordle\n");
        guess = betterGuesses.empty() ? allGuesses[0] : betterGuesses[0];
    }
    return 0;
}