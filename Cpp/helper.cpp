#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <math.h>

//---------------------------------------------------------------Cheat Sheet
// Check if string palidrome: equal(s.begin(), s.begin() + s.size()/2, s.rbegin())

// Typing
using l = int;
using o = double;

// Input
#define gc getchar_unlocked
void readInt(l &x) {
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

// Floating Point
#define dc(x) fixed << setprecision(x) <<
#define EPS = 1e-6;
inline bool fls(double a, double b){
  return a < b && (b - a > EPS);
}
inline bool fgr(double a, double b){
  return b < a && (a - b > EPS);
}
inline bool feq(double a, double b){
  return fabs(a - b) < EPS;
}

#define MID(x, y) (y - x) / 2 + x


// CONSTANTS
#define inf 0x3f3f3f3fLL
#define linf 0x3f3f3f3f3f3f3f3fLL
#define dinf numeric_limits<double>::infinity()
const double pi = 2 * acos(0.0);

// BITS
#define count_bits __builtin_popcountll     // number of 'on' bits in long long
#define trail_bits __builtin_ffsll          // number of leading zeros (most significant)
#define lead_bits __builtin_clzll           // number of trailing zeros (least significant)
#define bit(x, b) bitset<b>(x).to_string()  // prints x with b bits
#define LSOne(x) x &(-x)                    // least significant bit

//---------------------------------------------------------------DEBUGGING
#ifndef NDEBUG
#define ASSERT(condition, message) \
  do { \
      if (! (condition)) { \
          std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                    << " line " << __LINE__ << ": " << message << std::endl; \
          std::terminate(); \
      } \
  } while (false)

#define dbarr(x) std::cerr << "[";for (auto &y : x) std::cout << y << " "; std::cerr << "]\n";

template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
  std::cerr << (*it).substr(it->length() <= 1 ? 0 : 1) << " = " << a << "   ";
  err(++it, args...);
};
#define db(args...)                           \
  {                                           \
    std::string _s = #args;                        \
    replace(_s.begin(), _s.end(), ' ', '\0'); \
    replace(_s.begin(), _s.end(), ',', ' ');  \
    std::stringstream _ss(_s);                     \
    std::istream_iterator<std::string> _it(_ss);        \
    err(_it, args);                           \
    std::cerr << "\n";                             \
  }

#define cbounds(x, a, b) ASSERT(x >= a && x < b, "Out of bounds")
#else
#   define ASSERT(condition, message)
#endif

void splitPair(const std::string& s, const std::string& delim, std::string& a, std::string& b){
  auto next = s.find(delim, 0);
  a = s.substr(0, next), b = s.substr(next, s.length());
}

using Strings = std::vector<std::string>;
Strings split(const std::string& s, char delim){
  std::stringstream test(s);
  std::string segment;
  Strings seglist;

  while(std::getline(test, segment, delim))
  {
    seglist.push_back(segment);
  }
}

//-----------------------------------------------------String Parsing
// sscanf(line.c_str(),"%lld %*s %s %lld",&num1,string,&num2)
// discard parameter with * in '%*s'

//---------------------------------------------------------------Sorting
// sort(v.begin(), v.end(), [](const auto &a, const auto &b) {
//   return a.first == b.first ? a.second > b.second : a.first < b.first;
// });

//---------------------------------------------------------------Custom Priority Queue
// typedef pair<l, l> ll;
// struct PQC{
//  bool operator()(ll const& a, ll const& b) const{
//    return a.second < b.second || a.second == b.second && a.first < b.first;
//  }
// };
// typedef priority_queue< ll, std::vector<ll>, PQC > pq;

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
