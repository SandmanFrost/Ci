#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses,
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator>>(istream& is, Query& q) {
  string command;
  is >> command;
  if (command == "NEW_BUS"s) {
    q.stops.clear();
    q.type = QueryType::NewBus;
    is >> q.bus;
    size_t stop_count = 0;
    is >> stop_count;
    vector<string> respon;
    respon.resize(stop_count);
    for (string& stop : respon) {
      is >> stop;
      q.stops.push_back(stop);
    }
  } else if (command == "BUSES_FOR_STOP"s) {
    q.type = QueryType::BusesForStop;
    is >> q.stop;
  } else if (command == "STOPS_FOR_BUS"s) {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
  } else if (command == "ALL_BUSES") {
    q.type = QueryType::AllBuses;
  }
  return is;
}

struct BusesForStopResponse {
  map<string, vector<string>> stop_to_bus;
  string stop;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
  if (r.stop_to_bus.count(r.stop) == 0) {
    os << "No stop";
    return os;
  }
  bool first = true;
  for (const string& bus : r.stop_to_bus.at(r.stop)) {
    if (first) {
      os << bus;
      first = false;
    } else {
      os << " "s << bus;
    }
  }
  return os;
}

struct StopsForBusResponse {
  map<string, vector<string>> buses_to_stops, stops_to_buses;
  string bus;
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
  if (r.buses_to_stops.count(r.bus) == 0) {
    os << "No bus"s;
    return os;
  }
  size_t count = 0;
  for (const string& stop : r.buses_to_stops.at(r.bus)) {
    ++count;
    os << "Stop "s << stop << ": "s;
    if (r.stops_to_buses.at(stop).size() == 1) {
      os << "no interchange";
    } else {
      bool first = true;
      for (const string& transfer_bus : r.stops_to_buses.at(stop)) {
        if (r.bus != transfer_bus) {
          if (first) {
            os << transfer_bus;
            first = false;
          } else {
            os << " "s << transfer_bus;
          }
        }
      }
    }
    if (r.buses_to_stops.at(r.bus).size() != count) {
      os << endl;
    }
  }
  return os;
}

struct AllBusesResponse {
  map<string, vector<string>> buses_to_stops;
};

ostream& operator<<(ostream& os, const AllBusesResponse& r) {
  if (r.buses_to_stops.empty()) {
    os << "No buses"s;
    return os;
  }
  size_t count = 0;
  for (const auto& [bus, stops] : r.buses_to_stops) {
    ++count;
    os << "Bus "s << bus << ": "s;
    bool is_first = true;
    for (const string& stop : stops) {
      if (is_first) {
        os << stop;
        is_first = false;
      } else {
        os << " "s << stop;
      }
    }
    if (r.buses_to_stops.size() != count) os << endl;
  }

  return os;
}

class BusManager {
 public:
  void AddBus(const string& bus, const vector<string>& stops) {
    bus_to_stop_[bus] = stops;
    for (const auto& stop : stops) {
      stop_to_bus_[stop].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    BusesForStopResponse res;
    res.stop_to_bus = stop_to_bus_;
    res.stop = stop;
    return res;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    StopsForBusResponse res;
    res.bus = bus;
    res.buses_to_stops = bus_to_stop_;
    res.stops_to_buses = stop_to_bus_;
    return res;
  }

  AllBusesResponse GetAllBuses() const {
    AllBusesResponse res;
    res.buses_to_stops = bus_to_stop_;
    return res;
  }

 private:
  map<string, vector<string>> bus_to_stop_, stop_to_bus_;
};

void TestIsInput() {
  istringstream input;
  input.str("NEW_BUS No_1 5 1ya 2ya 3ya 4ya 5ya"s);
  Query q;
  input >> q;
  assert(q.bus == "No_1"s);
  assert(q.stops[0] == "1ya"s);
  assert(q.stops[1] == "2ya"s);
  assert(q.stops[2] == "3ya"s);
  assert(q.stops[3] == "4ya"s);
  assert(q.stops[4] == "5ya"s);
}

void TestInOutput() {
  BusesForStopResponse BtS = {{{"1ya"s, {"1"s, "2"s}},
                               {"2ya"s, {"1"s, "2"s}},
                               {"3ya"s, {"2"s, "3"s}},
                               {"4ya"s, {"3"}},
                               {"5ya"s, {"2"s, "3"s}},
                               {"6ya"s, {"1"s}},
                               {"7ya"s, {"3"s}},
                               {"9ya"s, {"1"s, "3"s}},
                               {"10ya"s, {"2"s}},
                               {"11ya"s, {"1"s}}},
                              "1ya"s};
  StopsForBusResponse StB = {{{"1"s, {"1ya"s, "2ya"s, "6ya", "9ya"s, "11ya"s}},
                              {"2"s, {"1ya"s, "2ya"s, "3ya", "5ya"s, "10ya"s}},
                              {"3"s, {"3ya"s, "4ya"s, "5ya", "7ya"s, "9ya"s}}},
                             {{"1ya"s, {"1"s, "2"s}},
                              {"2ya"s, {"1"s, "2"s}},
                              {"3ya"s, {"2"s, "3"s}},
                              {"4ya"s, {"3"}},
                              {"5ya"s, {"2"s, "3"s}},
                              {"6ya"s, {"1"s}},
                              {"7ya"s, {"3"s}},
                              {"9ya"s, {"1"s, "3"s}},
                              {"10ya"s, {"2"s}},
                              {"11ya"s, {"1"s}}},
                             "1"s};
  vector<string> ylitsa = {"1ya"s, "2ya"s, "6ya", "9ya"s, "11ya"s};
  AllBusesResponse all;
  all.buses_to_stops.insert({"1st", ylitsa});
  ostringstream out1, out2, out3;
  out1 << BtS;
  assert(out1.str() == "1 2"s);
  out2 << StB;
  assert(
      out2.str() ==
      "Stop 1ya: 2\nStop 2ya: 2\nStop 6ya: no interchange\nStop 9ya: 3\nStop 11ya: no interchange"s);
  out3 << all;
  assert(out3.str() == "Bus 1st: 1ya 2ya 6ya 9ya 11ya"s);
}

void TestForClass() {
  Query q;
  BusManager bm;
  ostringstream out1, out2, out3;
  bm.AddBus("1"s, {"1ya"s, "2ya"s, "6ya"s, "9ya"s, "11ya"s});
  bm.AddBus("2"s, {"1ya"s, "2ya"s, "3ya"s, "5ya"s, "10ya"s});
  bm.AddBus("3"s, {"3ya"s, "4ya"s, "5ya"s, "7ya"s, "9ya"s});
  out1 << bm.GetBusesForStop("1ya"s);
  assert(out1.str() == "1 2");

  out2 << bm.GetStopsForBus("1"s);
  assert(
      out2.str() ==
      "Stop 1ya: 2\nStop 2ya: 2\nStop 6ya: no interchange\nStop 9ya: 3\nStop 11ya: no interchange"s);
  out3 << bm.GetAllBuses();
  assert(
      out3.str() ==
      "Bus 1: 1ya 2ya 6ya 9ya 11ya\nBus 2: 1ya 2ya 3ya 5ya 10ya\nBus 3: 3ya 4ya 5ya 7ya 9ya"s);
}

void TestAll() {
  TestIsInput();
  TestInOutput();
  TestForClass();
}

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
      case QueryType::NewBus:
        bm.AddBus(q.bus, q.stops);
        break;
      case QueryType::BusesForStop:
        cout << bm.GetBusesForStop(q.stop) << endl;
        break;
      case QueryType::StopsForBus:
        cout << bm.GetStopsForBus(q.bus) << endl;
        break;
      case QueryType::AllBuses:
        cout << bm.GetAllBuses() << endl;
        break;
    }
  }
}