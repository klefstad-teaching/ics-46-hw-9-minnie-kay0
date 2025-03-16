#include "ladder.h"
#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <unordered_set>
#include <fstream>
#include <string>
#define my_assert(e) {cout << #e << ((e) ? " passed" : " failed") << endl;}
using namespace std;

void error(string word1, string word2, string msg) {
    cout << "Error: " << word1 << word2 << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
	int m = str1.size();
	int n = str2.size();

	if (abs(m - n) > d) { 
		return false; 
	}

	vector<vector<int>> dp(m + 1, vector<int>(n + 1));
	for (int i = 0; i <= m; ++i) {
		dp[i][0] = i; 
	}
	for (int j = 0; j <= n; ++j) { 
		dp[0][j] = j;
	}

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			int cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
			dp[i][j] = min(min(dp[i - 1][j] + 1, 
				dp[i][j - 1] + 1), dp[i - 1][j - 1] + cost);
		}
	}
	return dp[m][n] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
	int m = word1.size();
	int n = word2.size();

	if (abs(m - n) > 1) { return false; }

	int i = 0;
	int j = 0; 
	int count = 0;
	while (i < m && j < n) {
		if (word1[i] != word2[j]) {
			if (++count > 1) { return false; }
			
			if (m > n) { ++i; }
			else if (m < n) { ++j; }
			else { ++i; ++j; }
			
		} else {
			++i; 
			++j;
		}
	}

	return true; 
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
	if (begin_word == end_word) { return {}; }
	queue<vector<string>> ladder_queue;
	ladder_queue.push({begin_word});
	unordered_set<string> visited;
	visited.insert(begin_word);

	while (!ladder_queue.empty()) {
		for (int i = 0; i < ladder_queue.size(); ++i) {
			vector<string> ladder = ladder_queue.front();
			ladder_queue.pop();
			string last_word = ladder.back();

			if (last_word == end_word) { return ladder; }

			for (const string& word : word_list) {
				if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
					vector<string> new_ladder = ladder;
					new_ladder.push_back(word);
					ladder_queue.push(new_ladder);
					visited.insert(word);
				}
			}
		}
	}
	return {};
}

void load_words(set<string> & word_list, const string& file_name) {
	ifstream in(file_name);
	string word;
	while (in >> word) {
		word_list.insert(word);
	}
}

void print_word_ladder(const vector<string>& ladder) {
	if (ladder.empty()) { cout << "No word ladder found." << endl; return; }
	cout << "Word ladder found: ";
	for (size_t i = 0; i < ladder.size(); ++i) {
		cout << ladder[i] << " ";
	}
	cout << endl;
}

void verify_word_ladder() {
	set<string> word_list;
	load_words(word_list, "src/words.txt");

	// my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
	vector<string> cog = generate_word_ladder("sleep", "awake", word_list);
	print_word_ladder(cog);
	my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
	my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
	my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
	my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
	my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
	my_assert(generate_word_ladder("were", "were", word_list).size() == 0);
}