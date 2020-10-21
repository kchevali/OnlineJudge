#include <bits/stdc++.h>
using namespace std;
typedef long long l;
#define iinf 0x3f3f3f3fLL
#define gc getchar_unlocked

#define db(args...)                          \
  {                                          \
    string _s = #args;                       \
    replace(_s.begin(), _s.end(), ',', ' '); \
    stringstream _ss(_s);                    \
    istream_iterator<string> _it(_ss);       \
    err(_it, args);                          \
    cerr << "\n";                            \
  }
void err(istream_iterator<string> it) {}
template <typename T, typename... Args>

void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " = " << a << "   ";
  err(++it, args...);
}

// Aho-Corasick Algorith
// Most efficient string matching to several queries
// Finds substrings in string from a dictionary
map<l, map<char, l>> go_to;
vector<l> failure;
map<l, vector<l>> output;
vector<list<l>> positions;

// n_dict - # of letters per entry
const l N_MSG = 300000, N_WORD = 50000, N_DICT = 10000;
l qry_size, dp[N_MSG];
vector<l> getEntries[N_MSG];
char qry[N_WORD][N_DICT], withVowels[N_WORD][N_DICT];
l qry_length[N_WORD];
l w_vowel_length[N_WORD];
l vowelCount[N_WORD];
l word[N_MSG], n_msg;
char msg[N_MSG];

void create_failure() {
  queue<l> q;
  l current, state;
  for (auto it = go_to[0].begin(); it != go_to[0].end(); it++) {
    if (it->second != 0) {
      q.push(it->second);
      failure[it->second] = 0;
    }
  }
  while (!q.empty()) {
    current = q.front();
    q.pop();
    state = failure[current];

    for (auto it = go_to[current].begin(); it != go_to[current].end(); it++) {
      if (go_to[current].count(it->first) != 0) {
        q.push(it->second);
        state = failure[current];
        while (go_to[state].count(it->first) == 0) {
          state = failure[state];
        }
        failure[it->second] = go_to[state][it->first];
        output[it->second].insert(output[it->second].end(),
                                  output[failure[it->second]].begin(),
                                  output[failure[it->second]].end());
      }
    }
  }
}

void create_goto() {
  l new_state = 0;
  positions.resize(qry_size);
  for (l i = 0; i < qry_size; i++) {
    l state = 0, j;
    for (j = 0; j < qry_length[i] && go_to[state].count(qry[i][j]) >= 1; j++) {
      state = go_to[state][qry[i][j]];
    }
    for (l k = j; k < qry_length[i]; k++) {
      go_to[state][qry[i][k]] = ++new_state;
      state = new_state;
    }
    if (output.find(state) == output.end())
      output[state] = vector<l>(1, i);
    else
      output[state].emplace_back(i);
  }
  failure.resize(new_state + 1, 0);
  for (char i = ' '; i <= '~'; i++) {
    if (go_to[0].count(i) == 0) go_to[0][i] = 0;
  }
  create_failure();
}

void find_matches(const string &T) {
  l state = 0, t;
  for (l i = 0; i < n_msg; i++) {
    while (go_to[state].count(T[i]) == 0) {
      state = failure[state];
    }
    state = go_to[state][T[i]];
    if (output.count(state) > 0) {
      t = output[state].size();
      vector<l> temp = output[state];
      for (l j = 0; j < t; j++) {
        positions[temp[j]].emplace_back(i);
      }
    }
  }
}

void aho_corasick(const string &s) {
  create_goto();
  find_matches(s);
  for (l i = 0; i < qry_size; i++) {
    for (auto it = positions[i].begin(); it != positions[i].end(); it++) {
      *it -= (qry_length[i] - 1);
    }
  }
}

l maxVowel(l index) {
  if (index >= n_msg) return 0;
  if (dp[index] >= 0) return dp[index];

  // cout << "Index: " << index << "\n";
  l mx = -iinf, best_i = -1;
  l m = getEntries[index].size();
  for (l j = 0; j < m; j++) {
    l i = getEntries[index][j];
    // db(index, i, qry[i]);
    l vowel = maxVowel(index + qry_length[i]) + vowelCount[i];
    if (vowel > mx) {
      mx = vowel;
      best_i = i;
    }
  }
  // cout << "Vowel: " << mx << " " << best_i << "\n";
  word[index] = best_i;
  // db(index, mx);
  return dp[index] = mx;
}

void read(l &x) {
  l c = gc();
  x = 0;
  for (; ((c < 48 || c > 57)); c = gc())
    ;
  for (; c > 47 && c < 58; c = gc()) {
    x = (x << 1) + (x << 3) + c - 48;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  read(qry_size);
  for (l i = 0; i < qry_size; i++) {
    char ch = gc();
    l j = 0, k = 0;
    while (ch != '\n') {
      withVowels[i][j++] = ch;
      if (ch != 'A' && ch != 'E' && ch != 'I' && ch != 'O' && ch != 'U')
        qry[i][k++] = ch;
      ch = gc();
    }
    vowelCount[i] = (w_vowel_length[i] = j) - (qry_length[i] = k);
  }

  char ch = gc();
  n_msg = 0;
  while (ch != '\n') {
    msg[n_msg++] += ch;
    ch = gc();
  }
  for (l i = 0; i < n_msg; i++) {
    word[i] = -1;
    dp[i] = -1;
  }
  aho_corasick(msg);
  l m = positions.size();
  for (l i = 0; i < m; i++) {
    for (auto it = positions[i].begin(); it != positions[i].end(); it++) {
      getEntries[*it].emplace_back(i);
    }
  }
  maxVowel(0);
  for (l i = 0; i < n_msg; i++) {
    if (word[i] != -1) {
      for (l j = 0; j < w_vowel_length[word[i]]; j++) {
        printf("%c", withVowels[word[i]][j]);
      }
      printf(" ");
      i += qry_length[word[i]] - 1;
    }
  }
  printf("\n");

  return 0;
}

/*
9
THE
DAY
IS
BRIGHT
BUT
SOME
DAYS
ARE
BEST
THDYSBRGHTBTSMDYSRBST

2
ATA
TBE
TTB



*/