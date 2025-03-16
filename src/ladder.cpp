#include "ladder.h"
#include <algorithm>
using namespace std;

void error(string word1, string word2, string msg) {
    cout << "Error: " << msg  << " Word1: " << word1 << ", Word2: " << word2 << endl;
}

bool edit_distance_within(const string& s, const string& t, int d) {
    
}

bool is_adjacent(const string& word1, const string& word2) {
    if(word1 == word2)
        return false;
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {

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
            cout << " -> ";
    }
    cout << endl;
}
void verify_word_ladder() {

}
