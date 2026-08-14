#include <bits/stdc++.h>
#include <utility>

using namespace std;

using pi = std::pair<int32_t, int32_t>;
using pl = std::pair<int64_t, int64_t>;
using vi = std::vector<int32_t>;
using vl = std::vector<int64_t>;
using vpi = std::vector<pi>;
using vpl = std::vector<pl>;
using str = std::string;
using db = double;
using ld = long double;

// templates
#define tcT template <class T
#define tcTU tcT, class U
#define tcTUU tcT, class... U

// pairs
#define mp make_pair
#define f first
#define s second

// loops
#define FOR(i, a, b) for (int32_t i = (a); i < (b); i++)
#define ROF(i, a, b) for (int32_t i = (b) - 1; i >= (a); i--)
#define trav(a, x) for (auto &(a) : (x))

// vectors
#define sz(a) (int32_t)(a).size()
#define all(x) (x).begin(), (x).end()
#define sor(x) sort(all(x))
#define rsz resize
#define ins insert
#define ft front()
#define bk back()
#define pf push_front
#define pb push_back
#define eb emplace_back
#define lb lower_bound
#define ub upper_bound

const int32_t MOD = 998244353;
const int32_t MAXN = 2e5 + 5;
const int64_t INF = 1e18;
const double PI = acos(-1);
const int32_t tSZ = (1 << 21);
const int32_t dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1}; // for grid problems
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

constexpr int pcnt(int x) { return __builtin_popcount(x); } // number of bits

namespace MO {
int32_t add(int64_t x, int64_t y) {
  return ((x % MOD) + (y % MOD) + MOD) % MOD;
}
int32_t mul(int64_t x, int64_t y) { return ((x % MOD) * (y % MOD)) % MOD; }

int32_t pow(int32_t x, int32_t y) {
  int32_t res = 1;

  while (y) {
    if (y & 1) {
      res = mul(res, x);
    }
    x = mul(x, x);
    y >>= 1;
  }
  return res;
}

int32_t inverse(int32_t x) { return pow(x, MOD - 2); }
}; // namespace MO

// input
tcT > void re(complex<T> &c);
tcTU > void re(pair<T, U> &p);
tcT > void re(vector<T> &v);

tcT > void re(T &x) { cin >> x; }
void re(db &d) {
  str t;
  cin >> t;
  d = stod(t);
}
void re(ld &d) {
  str t;
  cin >> t;
  d = stold(t);
}
tcTUU > void re(T &x, U &...u) {
  re(x);
  re(u...);
}

tcT > void re(complex<T> &x) {
  T a, b;
  re(a, b);
  x = {a, b};
}
tcTU > void re(pair<T, U> &p) { re(p.f, p.s); }
tcT > void re(vector<T> &v) { trav(x, v) re(x); }

// to string
#define ts to_string
str ts(char c) { return str(1, c); }
str ts(const char *s) { return (str)s; }
str ts(str s) { return s; }
str ts(bool x) { return x ? "YES" : "NO"; }

// output
tcT > void pr(const T &x) { cout << ts(x); }
tcTUU > void pr(const T &t, const U &...u) {
  pr(t);
  pr(u...);
}
void ps() { pr("\n"); }
tcTUU > void ps(const T &t, const U &...u) {
  pr(t);
  if (sizeof...(u)) {
    pr(" ");
  }
  ps(u...);
}

void setIn(const str &f_name) { freopen(f_name.c_str(), "r", stdin); }
void setOut(const str &f_name) { freopen(f_name.c_str(), "w", stdout); }
void unsyncIO() { cin.tie(0)->sync_with_stdio(false); }
void setIO(str st = "") {
  unsyncIO();
  if (sz(st)) {
    setIn(st + ".in"), setOut(st + ".out");
  }
}

// DEBUG
void DBG() { cerr << "]\n"; }
tcTUU > void DBG(const T &t, const U &...u) {
  cerr << ts(t);
  if (sizeof...(u)) {
    cerr << ", ";
  }
  DBG(u...);
}

// strategy is to use 3 numbers in the list per person

std::vector<std::vector<int>> process_step(int N, int M, int R,
                                           std::vector<int> T,
                                           std::vector<std::vector<int>> A) {
  set<int32_t> already_marked;
  set<int32_t> locked;
  set<int32_t> free_last_round;
  set<int32_t> added;

  vpi to_add;

  // add currently locked ones
  for (int32_t i{0}; i < sz(T); i++) {
    locked.ins(T[i]);
  }

  for (int32_t i{0}; i < N; i++) {
    if (sz(A[i]) >= 2) {
      already_marked.ins(A[i][0]);
    }
  }
  for (int32_t i{0}; i < N; i++) {
    if (sz(A[i]) == 1 || sz(A[i]) == 3) {
      if (free_last_round.count(A[i].back())) {
        free_last_round.erase(A[i].back());
      } else {
        free_last_round.ins(A[i].back());
      }
    }
  }

  // need to determine if the free_last_round are fake or not
  // they could be left overs from a locked one
  bool last_was_empty = free_last_round.empty();

  for (int32_t i{0}; i < N; i++) {
    if (!last_was_empty && R > 0 && !already_marked.count(i) &&
        !free_last_round.count(i)) {
      // was locked last round
      to_add.pb({i, R - 1});
    }

    int32_t holds_free = -1;

    if (sz(A[i]) == 1 || sz(A[i]) == 3) {
      holds_free = A[i].back();
    }

    // locked one is holding a currently locked one as a free from last round
    // we need to immediately set the this as a locked
    if (locked.count(i) && locked.count(holds_free) &&
        !added.count(holds_free)) {
      // is locked this round, but its index was marked as not locked last round
      to_add.pb({holds_free, R});
      added.ins(holds_free);
    }
  }

  for (int32_t i{0}; i < N; i++) {
    if (locked.count(i) && !added.count(i)) {
      // is locked this round, and was not already added in the loop on top
      // thats best effort, since we might not push all of them
      to_add.pb({i, R});
    }
  }

  // from all that we can alter, remove the last round free item
  for (int32_t i{0}; i < N; i++) {
    if (!locked.count(i) && (sz(A[i]) == 1 || sz(A[i]) == 3)) {
      A[i].pop_back();
    }
  }

  int32_t z = 0;
  for (int32_t i{0}; i < N; i++) {
    // if we can alter the current one, add an item from the FIFO
    if (!locked.count(i) && A[i].empty() && z < sz(to_add)) {
      already_marked.insert(to_add[z].first);

      if (added.count(to_add[z].first)) {
        added.erase(to_add[z].first);
      }
      A[i].push_back(to_add[z].first);
      A[i].push_back(to_add[z].second);
      z++;
    }
  }

  vi free_this_round;

  // get a list of the free ones
  for (int32_t i{0}; i < N; i++) {
    if (!locked.count(i)) {
      free_this_round.pb(i);
    }
  }

  if (z == sz(to_add)) {
    map<int32_t, int32_t> mm;
    // check which are the frozen frees, and make sure their count is even
    for (int32_t i{0}; i < N; i++) {
      if (locked.count(i) && (sz(A[i]) == 1 || sz(A[i]) == 3)) {
        mm[A[i].back()]++;
      }
    }
    free_this_round.clear();
    trav(x, mm) {
      if (x.second % 2 == 1) {
        free_this_round.push_back(x.first);
      }
    }
  }

  // now push back the ones that are not locked already, and were not locked in
  // this round
  z = 0;
  for (int32_t i{0}; i < N; i++) {
    if (z == sz(free_this_round))
      break;

    if (!locked.count(i)) {
      A[i].push_back(free_this_round[z++]);
    }
  }
  return A;
}

std::vector<int> determine_steps(int N, int M,
                                 std::vector<std::vector<int>> A) {
  vi answer(N, -1);

  trav(x, A) {
    if (sz(x) >= 2) {
      answer[x[0]] = x[1];
    }
  }

  set<int32_t> free_last_round;
  // now check last round
  for (int32_t i{0}; i < N; i++) {
    if ((sz(A[i]) == 1 || sz(A[i]) == 3)) {
      if (free_last_round.count(A[i].back())) {
        free_last_round.erase(A[i].back());
      } else {
        free_last_round.ins(A[i].back());
      }
    }
  }

  if (!free_last_round.empty()) {
    for (int32_t i{0}; i < N; i++) {
      if (answer[i] == -1 && !free_last_round.count(i)) {
        answer[i] = M - 1;
      }
    }
  }

  return answer;
}
