#include <bits/stdc++.h>
using namespace std;
typedef long long l;

// Data Structure: Unordered Map

struct Car {
  string name;
  l price, pickCost, kmCost;
};
struct Event {
  l time, dist, damage;
  string spy, carType;
  char eventType;
};
struct Spy {
  string name;
  l cost, carIndex;
  char status;
  bool valid;
};

bool sortEvents(Event const& a, Event const& b) { return a.time < b.time; }
bool sortSpies(Spy const& a, Spy const& b) { return a.name < b.name; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  l z;
  cin >> z;
  for (l zz = 0; zz < z; zz++) {
    l nCar, nEvent;  // n, m
    cin >> nCar >> nEvent;

    vector<Car> cars;
    vector<Event> events;
    vector<Spy> spies;
    unordered_map<string, l> carMap;
    unordered_map<string, l> spyMap;

    for (l i = 0; i < nCar; i++) {
      Car car;
      cin >> car.name >> car.price >> car.pickCost >> car.kmCost;
      cars.push_back(car);
      carMap[car.name] = i;
    }

    for (l i = 0; i < nEvent; i++) {
      Event event;
      cin >> event.time >> event.spy >> event.eventType;

      switch (event.eventType) {
        case 'p':
          cin >> event.carType;
          break;
        case 'r':
          cin >> event.dist;
          break;
        case 'a':
          cin >> event.damage;
      }
      events.push_back(event);
    }
    sort(events.begin(), events.end(), &sortEvents);
    for (const Event& event : events) {
      auto spyPair = spyMap.find(event.spy);
      l spyIndex;

      if (spyPair == spyMap.end()) {
        Spy spy;
        spy.name = event.spy;
        spy.cost = 0;
        spy.carIndex = -1;
        spy.valid = true;
        spy.status = 'r';
        spyIndex = spies.size();
        spyMap[event.spy] = spyIndex;
        spies.push_back(spy);
      } else {
        spyIndex = spyPair->second;
      }
      Spy& spy = spies[spyIndex];

      switch (event.eventType) {
        case 'p':
          spy.valid = spy.valid && spy.status == 'r';
          spy.status = 'p';
          spy.carIndex = carMap.find(event.carType)->second;
          spy.cost += cars[spy.carIndex].pickCost;
          break;
        case 'r':
          spy.valid = spy.valid && spy.status != 'r';
          spy.status = 'r';
          if (spy.carIndex >= 0)
            spy.cost += cars[spy.carIndex].kmCost * event.dist;
          spy.carIndex = -1;
          break;
        case 'a':
          spy.valid = spy.valid &&
                      spy.status != 'r';  // can two accidents happen? // YES
          spy.status = 'a';
          spy.cost += (l)ceil(cars[spy.carIndex].price * event.damage / 100.0);
      }
    }

    sort(spies.begin(), spies.end(), &sortSpies);
    for (Spy& spy : spies) {
      spy.valid = spy.valid && spy.status == 'r';
      cout << spy.name << " "
           << (spy.valid ? to_string(spy.cost) : "INCONSISTENT") << "\n";
    }
  }
}
