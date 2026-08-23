#include <bits/stdc++.h>

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

struct point {
  int32_t x, y;
  double d;
  int32_t ind;

  bool touch(const point &other) const {
    double dist = (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);

    double ff = (d + other.d + 25.4 * 2.0);

    return ff * ff >= dist;
  }

  bool operator<(const point &other) const {
    return x < other.x || (x == other.x && y < other.y);
  }
};

int32_t n;

vector<int32_t> graph[MAXN];
int32_t mark[MAXN];

bool rec(int32_t v) {
  mark[v] = 1;
  bool ans = (n >= 7 ? graph[v].size() < 2 : 0);
  trav(x, graph[v]) {
    if (!mark[x]) {
      ans |= rec(x);
    }
  }
  return ans;
}

void solve() {
  re(n);

  vector<point> vv;

  int32_t x, y, d;
  FOR(i, 0, n) {
    re(x, y, d);

    vv.push_back({.x = x, .y = y, .d = d / 2.0, .ind = i});
  }

  sort(vv.begin(), vv.end());

  int32_t threshold = 220;

  set<point, decltype([](const point &f1, const point &f2) {
        return f1.y < f2.y || (f1.y == f2.y && f1.x < f2.x);
      })>
      ss;

  FOR(i, 0, n) {
    ss.insert(vv[i]);

    // find current point in ss
    auto x = ss.find(vv[i]);

    // keep going left
    while (true) {
      if (abs(x->x - vv[i].x) > threshold) {
        // remove cur
        auto to_rem = x;
        if (x == ss.begin()) {
          ss.erase(to_rem);
          break;
        }
        x = std::prev(x);
        ss.erase(to_rem);
        continue;
      }
      if (abs(x->y - vv[i].y) > threshold)
        break;

      if (vv[i].ind != x->ind && vv[i].touch(*x)) {
        graph[vv[i].ind].pb(x->ind);
        graph[x->ind].pb(vv[i].ind);
      }
      if (x == ss.begin())
        break;
      x = std::prev(x);
    }

    // now go right
    x = ss.find(vv[i]);

    while (x != ss.end()) {
      if (abs(x->x - vv[i].x) > threshold) {
        // remove cur
        auto to_rem = x;
        if (std::next(x) == ss.end()) {
          ss.erase(to_rem);
          break;
        }
        x = std::next(x);
        ss.erase(to_rem);
        continue;
      }
      if (abs(x->y - vv[i].y) > threshold)
        break;

      if (vv[i].ind != x->ind && vv[i].touch(*x)) {
        graph[vv[i].ind].pb(x->ind);
        graph[x->ind].pb(vv[i].ind);
      }
      x = std::next(x);
    }
  }

  // now traverse
  bool ans = rec(0);
  FOR(i, 0, n) {
    if (!mark[i]) {
      ans |= 1;
    }
  }
  ps(ans ? "no" : "yes");
}

int main() {
  setIO();

  solve();

  return 0;
}
