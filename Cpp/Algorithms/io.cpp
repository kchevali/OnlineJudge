#include "../all.cpp"

// getline(cin, str); - used w/ cin.ignore();

void readd(double &x) { scanf("%lf", &x); }

l readBinary() {
  string str;
  cin >> str;
  return bitset<64>(str).to_ullong();
}

l readHex() {
  l x;
  scanf("%llx", &x);
  // cin >> hex >> x;
  return x;
}

l readOct() {
  l x;
  scanf("%llo", &x);
  // cin >> oct >> x;
  return x;
}

int main() {
  l x = readBinary(), y = readHex(), z = readOct();
  cout << "Bin:" << x << " Hex:" << y << " Oct:" << z << "\n";
}