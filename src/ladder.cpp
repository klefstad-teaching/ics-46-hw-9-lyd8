#include "ladder.h"
#include <algorithm>
#include <cassert>

using namespace std;

void error(string word1, string word2, string msg) {
    cout << "Error: " << msg  << " Word1: " << word1 << ", Word2: " << word2 << endl;
}

bool one_substitution(const string &s, const string &t) {
    int diff = 0;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] != t[i])
            diff++;
        if (diff > 1)
            return false;
    }
    return diff == 1;
}

bool one_insertion(const string &shorter, const string &longer) {
    size_t i = 0, j = 0;
    bool foundDiff = false;
    while (i < shorter.size() && j < longer.size()) {
        if (shorter[i] == longer[j]) {
            i++;
            j++;
        } else {
            if (foundDiff)
                return false;
            foundDiff = true;
            j++;
        }
    }
    return true;
}

bool edit_distance_within(const string& s, const string& t, int d) {
    if (d < 0) return false;
    int lenDiff = abs((int)s.size() - (int)t.size());
    if (lenDiff > d) return false;
    if (d == 0) return s == t;
    
    if (d == 1) {
        if (s.size() == t.size())
            return one_substitution(s, t);
        else if (s.size() + 1 == t.size())
            return one_insertion(s, t);
        else if (t.size() + 1 == s.size())
            return one_insertion(t, s);
        else
            return false;
    }
    
    vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
    for (size_t i = 0; i <= s.size(); i++)
        dp[i][0] = i;
    for (size_t j = 0; j <= t.size(); j++)
        dp[0][j] = j;
    for (size_t i = 1; i <= s.size(); i++) {
        for (size_t j = 1; j <= t.size(); j++) {
            if (s[i - 1] == t[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
        }
    }
    return dp[s.size()][t.size()] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    if(word1 == word2)
        return false;
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    vector<string> start_ladder;
    start_ladder.push_back(begin_word);
    ladder_queue.push(start_ladder);

    set<string> visited;
    visited.insert(begin_word);

    while(!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        
        for(const string& word : word_list) {
            if(is_adjacent(last_word, word)) {
                if(visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if(word == end_word) {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return vector<string>();
}
  
void load_words(set<string> & word_list, const string& file_name) {
    ifstream infile(file_name);
    if(!infile) {
        cout << "Cant open file: " << file_name << endl;
        exit(1);
    }
    string word;
    while(infile >> word) {
        for (char &c : word) {
            c = std::tolower(c);
        }
        word_list.insert(word);
    }
    infile.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if(ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    for(size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
        if(i < ladder.size() - 1)
            cout << " ";
    }
    cout << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    assert(generate_word_ladder("code", "data", word_list).size() == 6);
    assert(generate_word_ladder("work", "play", word_list).size() == 6);
    assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
