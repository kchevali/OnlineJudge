#include <bits/stdc++.h>
using namespace std;
typedef long long l;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string targetAnimal;  // last animal given
  l n;                  // unused animals
  cin >> targetAnimal >> n;

  char target = targetAnimal[targetAnimal.length() - 1];  // get target char

  string firstFit = "";  // first animal that matches target
  // animals that end with letter _ (where 0 => a, 1 => b ...)
  string animals[26];
  l time[26];        // list index of animals that end with letter _ (...)
  l firstCount[26];  // count animals that start with letter _ (...)

  for (l i = 0; i < 26; i++) {
    animals[i] = "";
    firstCount[i] = 0;
    time[i] = -1;
  }

  for (l i = 0; i < n; i++) {
    string x;
    cin >> x;
    if (x[0] == target) {
      if (firstFit.length() == 0) {  // never fit an animal before
        firstFit = x;
      }

      l lastIndex = x[x.length() - 1] - 'a';
      string &word = animals[lastIndex];  // word with last letter

      // never fit an animal before that ends with this letter
      if (word.length() == 0) {
        word = x;
        time[lastIndex] = i;  // list index when found animal
      }
    }
    firstCount[x[0] - 'a']++;  // count first letter appearances
  }

  l minTimeIndex = -1;  // letter index with min list index
  for (l i = 0; i < 26; i++) {
    string word = animals[i];
    if (time[i] >= 0) {  // found animal that ends with letter i
      l firstIndex = word[0] - 'a';
      // check appearance of first letter is 0 (or 1 if actually self) AND its
      // first time or index is lower
      if (firstCount[i] - (firstIndex == i ? 1 : 0) == 0 &&
          (minTimeIndex == -1 || time[i] < time[minTimeIndex])) {
        minTimeIndex = i;
      }
    }
  }

  if (minTimeIndex >= 0) {
    cout << animals[minTimeIndex] << "!\n";
  } else if (firstFit.length() > 0) {
    cout << firstFit << "\n";
  } else {
    cout << "?\n";
  }
}