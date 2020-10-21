#include <bits/stdc++.h>
using namespace std;
typedef long long l;

struct Lane {
  l offset, interval, speed;
};

bool collide(l x, l a, l speed, l w) {
  if (a + speed < w) {
    return x >= a && x <= (a + speed);
  }
  return (x >= a && x < w) || (x >= 0 && x <= (a + speed - w));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l nlanes, width;
  cin >> nlanes >> width;

  Lane lanes[nlanes];

  for (l i = 0; i < nlanes; i++) {
    cin >> lanes[i].offset >> lanes[i].interval >> lanes[i].speed;
  }

  l x, y = nlanes - 1;
  string dir;
  cin >> x >> dir;

  for (int i = 1; i <= dir.length(); i++) {
    x += dir[i] == 'R';
    x -= dir[i] == 'L';
    y += dir[i] == 'D';
    y -= dir[i] == 'U';
    if (y == nlanes) continue;

    l offset = lanes[i].offset, interval = lanes[i].interval,
      speed = lanes[i].speed;

    // l t = i % (interval * speed);
    l xx = ((y & 1) == 0) ? x : nlanes - 1 - x;

    cout << "Lane: " << i << "\n";

    for (l car = offset + speed * i; car < width; car += interval) {
      if (collide(x, car, speed, width)) {
        cout << "squish\n";
        return 0;
      }
    }
    for (l car = offset + speed * i; car >= 0; car -= interval) {
      if (collide(x, car, speed, width)) {
        cout << "squish\n";
        return 0;
      }
    }
  }
  cout << "safe\n";
}
