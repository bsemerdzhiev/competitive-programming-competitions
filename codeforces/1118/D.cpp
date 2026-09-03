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
const int32_t MAXN = 12e3 + 5;
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

int32_t n, m;
pl a[2][MAXN];
vpl intervals;

struct sol {
  vl lens;

  void add(int64_t vv) {
    FOR(i, 0, sz(lens)) {
      if (lens[i] <= vv) {
        lens.insert(lens.begin() + i, vv);
        return;
      }
    }
    lens.push_back(vv);
  }

  bool operator<(const sol &rhs) const {
    FOR(i, 0, min(rhs.lens.size(), lens.size())) {
      if (rhs.lens[i] < lens[i]) {
        return false;
      } else if (rhs.lens[i] > lens[i]) {
        return true;
      }
    }
    return lens.size() < rhs.lens.size();
  }
};

sol T[MAXN][5][2];

sol rec(int32_t ind, int32_t side, bool rem_one) {
  if (ind >= sz(intervals) - 1) {
    return {};
  }

  sol &cur_sol = T[ind][side + 2][rem_one];

  if (cur_sol.lens.size() != 0) {
    return cur_sol;
  }

  bool has_seen_other = false;
  FOR(z, ind + 1, sz(intervals)) {
    if (intervals[z].f == intervals[ind].f && abs(intervals[z].s) != side) {
      continue;
    }
    if (abs(intervals[z].s) != side && intervals[z].s > 0) {
      continue;
    }

    if (abs(intervals[z].s) == side) {
      sol new_sol = {};
      if (has_seen_other) {
        // we are inside another interval
        new_sol = rec(z, side == 2 ? 1 : 2, has_seen_other);
        new_sol.add(intervals[z].f - intervals[ind].f + 1 - rem_one);
        cur_sol = max(cur_sol, new_sol);

      } else {
        if (z + 1 < sz(intervals)) {
          new_sol = rec(z + 1, abs(intervals[z + 1].s), has_seen_other);
        }
        new_sol.add(intervals[z].f - intervals[ind].f + 1 - rem_one);
        cur_sol = max(cur_sol, new_sol);
      }

      break;
    } else {
      has_seen_other = true;

      sol new_sol = rec(z, side == 2 ? 1 : 2, false);

      new_sol.add(intervals[z].f - intervals[ind].f - rem_one);
      cur_sol = max(cur_sol, new_sol);
    }
  }

  return cur_sol;
}

void solve() {
  sort(a[0], a[0] + n);
  sort(a[1], a[1] + m);

  int32_t l1 = 0, l2 = 0;

  intervals.clear();

  while (l1 < n || l2 < m) {
    while (l1 < n && l2 < m && a[0][l1].f <= a[1][l2].f &&
           a[1][l2].s <= a[0][l1].s) {
      l2++;
    }

    while (l1 < n && l2 < m && a[1][l2].f <= a[0][l1].f &&
           a[0][l1].s <= a[1][l2].s) {
      l1++;
    }

    if (l1 == n) {
      intervals.pb(mp(a[1][l2].f, -1));
      intervals.pb(mp(a[1][l2].s, 1));
      l2++;
    } else if (l2 == m) {
      intervals.pb(mp(a[0][l1].f, -2));
      intervals.pb(mp(a[0][l1].s, 2));
      l1++;
    } else {
      if (a[0][l1].f < a[1][l2].f) {
        intervals.pb(mp(a[0][l1].f, -2));
        intervals.pb(mp(a[0][l1].s, 2));
        l1++;
      } else {
        intervals.pb(mp(a[1][l2].f, -1));
        intervals.pb(mp(a[1][l2].s, 1));
        l2++;
      }
    }
  }
  sort(intervals.begin(), intervals.end());

  FOR(i, 0, sz(intervals)) {
    FOR(j, 0, 5) {
      FOR(g, 0, 2) { T[i][j][g] = {}; }
    }
  }

  sol answer = rec(0, abs(intervals[0].s), false);

  ps(sz(answer.lens));
  trav(x, answer.lens) { pr(x, " "); }
  ps();
}

int main() {
  setIO();

  size_t t;
  re(t);

  while (t--) {
    re(n, m);
    FOR(i, 0, n) { re(a[0][i].f, a[0][i].s); }

    FOR(i, 0, m) { re(a[1][i].f, a[1][i].s); }

    solve();
  }

  return 0;
}
