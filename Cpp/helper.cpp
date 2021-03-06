#include "Template.cpp"
//---------------------------------------------------------------Cheat Sheet
// Fast Counting: if(cond) x++ -> x += cond
// Check even: "its " + (num & 1 ? "odd" : "even");
// Check if string palidrome: equal(s.begin(), s.begin() + s.size()/2,
// s.rbegin())

#define gc getchar_unlocked
typedef double o;

void read(l &x) {
  l c = gc();
  x = 0;
  int neg = 0;
  for (; ((c < 48 || c > 57) && c != '-'); c = gc())
    ;
  if (c == '-') {
    neg = 1;
    c = gc();
  }
  for (; c > 47 && c < 58; c = gc()) {
    x = (x << 1) + (x << 3) + c - 48;
  }
  if (neg) x = -x;
}

#define dc(x) fixed << setprecision(x) <<
#define MID(x, y) x + (y - x) / 2
#define inf 0x3f3f3f3fLL
#define linf 0x3f3f3f3f3f3f3f3fLL
#define dinf numeric_limits<double>::infinity()

// CONSTANTS
const double pi = 2 * acos(0.0);
const double EPS = 1e-6;

//---------------------------------------------------------------BITS
#define count_bits __builtin_popcountll     // number of 'on' bits in long long
#define trail_bits __builtin_ffsll          // number of leading zeros (most significant)
#define lead_bits __builtin_clzll           // number of trailing zeros (least significant)
#define bit(x, b) bitset<b>(x).to_string()  // prints x with b bits
#define LSOne(x) x &(-x)                    // least significant bit

//---------------------------------------------------------------DEBUGGING
#define con(x, a, b) \
  if (x < a || x >= b) cerr << "Out of Bounds: " << #x << endl;
#define arr(x)                  \
  C "[";                        \
  for (auto &y : x) C y << " "; \
  C "]" E;
#define db(args...)                           \
  {                                           \
    string _s = #args;                        \
    replace(_s.begin(), _s.end(), ' ', '\0'); \
    replace(_s.begin(), _s.end(), ',', ' ');  \
    stringstream _ss(_s);                     \
    istream_iterator<string> _it(_ss);        \
    err(_it, args);                           \
    cerr << "\n";                             \
  }
void err(istream_iterator<string> it) {}
template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
  cerr << (*it).substr(it->length() <= 1 ? 0 : 1) << " = " << a << "   ";
  err(++it, args...);
}

void tokenize() {
  string line, token;
  while (getline(cin, line)) {
    cout << line << "\n";
    stringstream ss(line);
    while (ss >> token) {
      cout << "Token: " << token << "\n";
    }
  }
}

//-----------------------------------------------------String Parsing
// sscanf(line.c_str(),"%lld %*s %s %lld",&num1,string,&num2)
// discard parameter with * in '%*s'

//---------------------------------------------------------------Sorting
// sort(v.begin(), v.end(), [](const auto &a, const auto &b) {
//   return a.first == b.first ? a.second > b.second : a.first < b.first;
// });

//---------------------------------------------------------------Custom PQ
// typedef pair<l, l> ll;
// struct PQC{
//  bool operator()(ll const& a, ll const& b) const{
//    return a.second < b.second || a.second == b.second && a.first < b.first;
//  }
// };
// typedef priority_queue< ll, vector<ll>, PQC > pq;

//---------------------------------------------------------------DATA STRUCTURES

/*
// Simple import

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

using namespace std;
*/
