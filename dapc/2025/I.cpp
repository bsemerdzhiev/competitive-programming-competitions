#include <bits/stdc++.h>
#include <cstdlib>
#include <string>

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

int32_t n;
str names[MAXN];
double values[MAXN];
bool has_val[MAXN];

int32_t check(int32_t pos, double val) {
  for (int32_t i{pos}; i >= 0; i--) {
    if (has_val[i] && val > values[i]) {
      // should be smaller
      return 1;
    }
  }

  for (int32_t i{pos}; i < n; i++) {
    if (has_val[i] && val < values[i]) {
      // should be bigger
      return 0;
    }
  }

  // DBG("AA");
  values[pos] = val;

  double prev_val = 0.0;
  double slack = 0.0;
  double min_val = 0.0;
  int32_t empties_cnt = 0;

  has_val[pos] = 1;
  values[pos] = val;

  for (int32_t i{n - 1}; i >= 0; i--) {
    if (has_val[i]) {
      // DBG(i, values[i] - prev_val);
      min_val += values[i];

      min_val += empties_cnt * prev_val;
      slack += (values[i] - prev_val) * empties_cnt;

      empties_cnt = 0;
      prev_val = values[i];
    } else {
      empties_cnt++;
    }
  }

  // ps(min_val, slack);

  has_val[pos] = 0;

  min_val += empties_cnt * prev_val;
  slack += (100.0 - prev_val) * empties_cnt;

  if (min_val > 100.0) {
    return 1;
  } else if (min_val + slack < 100.0) {
    return 0;
  } else {
    return 2;
  }
}

void solve() {
  // ps(check(2, 50));
  // return;
  FOR(i, 0, n) {
    if (has_val[i])
      continue;

    double l = 0.00, r = 100.00;
    double ans_small = 100.0;
    // test smallest first
    FOR(z, 0, 1'000) {
      double middle = (l + r) / 2.0;

      int32_t res = check(i, middle);

      if (res == 0) {
        l = middle;
      } else if (res == 1) {
        r = middle;
      } else {
        ans_small = middle;
        r = middle;
      }
    }
    l = 0.00;
    r = 100.00;
    double ans_big = 0.00;

    FOR(z, 0, 1'000) {
      double middle = (l + r) / 2.0;

      int32_t res = check(i, middle);

      if (res == 0) {
        l = middle;
      } else if (res == 1) {
        r = middle;
      } else {
        ans_big = middle;
        l = middle;
      }
    }

    ps(names[i], ans_small, ans_big);
  }
}

int main() {
  setIO();

  str complete_str;
  std::getline(std::cin, complete_str);

  n = atoi(complete_str.c_str());

  FOR(i, 0, n) {
    std::getline(std::cin, complete_str);

    int32_t x = complete_str.find(' ');
    str name = (x == -1 ? complete_str : complete_str.substr(0, x));
    names[i] = name;

    if (x != -1) {
      values[i] = atof(complete_str.substr(x + 1).c_str());
      has_val[i] = 1;
    }
  }

  solve();

  return 0;
}
