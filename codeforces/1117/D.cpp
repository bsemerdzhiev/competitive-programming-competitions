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
const int32_t MAXN = 3e5 + 5;
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

int64_t S;
int64_t x[MAXN], y[MAXN], q;

int64_t calc(vpl &sums, vpl &vv, int64_t n, int64_t m) {
  int64_t ans = 0;

  int32_t st = 0, ed = vv.size() - 1;
  int32_t up_to = -1;

  while (st <= ed) {
    int32_t middle = (st + ed) >> 1;

    if (vv[middle].first >= n) {
      st = middle + 1;
      up_to = middle;
    } else {
      ed = middle - 1;
    }
  }

  // int32_t cur_ind = 0;
  // add the ones that we are smaller than
  if (up_to != -1) {
    ans += min(m, vv[up_to].second) * n;
    // cur_ind = min(m, vv[up_to].second);
  }
  // ps(ans);

  st = 0, ed = vv.size() - 1;
  int32_t up_to2 = -1;

  while (st <= ed) {
    int32_t middle = (st + ed) >> 1;

    if (vv[middle].second <= m) {
      up_to2 = middle;
      st = middle + 1;
    } else {
      ed = middle - 1;
    }
  }
  // ps(up_to2);

  // if (up_to2 == -1) {
  //   return ans;
  // }
  if (up_to > up_to2) {
    // we have already added everything
  } else if (up_to != -1) {
    // DBG(sums[up_to2].second, sums[up_to].second);
    // ps(ans);
    // ps(up_to2, up_to);
    ans += sums[up_to2].second;
    ans -= sums[up_to].second;
    // DBG(up_to2, ans);

    if (up_to2 + 1 < sz(sums)) {
      // DBG("AA");
      ans += (m - vv[up_to2].second) * vv[up_to2 + 1].first;
    }
  }

  return ans;
}

void solve() {
  // factorize
  vector<pl> vv;
  for (int64_t i{1}; i <= sqrt(S); i++) {
    if (S % i == 0) {
      vv.pb({i, S / i});
      vv.pb({S / i, i});
    }
  }

  sort(vv.begin(), vv.end(), greater<pl>());

  vpl sums;
  int64_t cur_sum = 0;
  int64_t prev_ind = 0;
  trav(x, vv) {
    // ps(x.first, x.second);
    // use current height
    cur_sum += (x.second - prev_ind) * x.first;
    prev_ind = x.second;

    sums.pb({x.second, cur_sum});
  }

  // ps(sz(vv));

  FOR(i, 0, q) { ps(calc(sums, vv, y[i], x[i])); }
}

int main() {
  setIO();

  size_t t;
  re(t);

  while (t--) {
    re(S, q);

    FOR(i, 0, q) { re(x[i], y[i]); }

    solve();
  }

  return 0;
}
