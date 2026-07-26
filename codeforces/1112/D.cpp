#include <bits/stdc++.h>

using namespace std;

using pi = std::pair<int32_t, int32_t>;
using vi = std::vector<int32_t>;
using vpi = std::vector<pi>;
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
const int32_t MAXN = 1e6 + 5;
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

int32_t n, a[MAXN];

void solve() {
  bool type = 0;
  int32_t prev_max = 0;
  vi ans(n, 0);

  FOR(i, 0, n - 1) {
    if (a[i] == n) {
      ps(0);
      return;
    }

    if (a[i] == n - 1) {
      if (prev_max != n && type == 1) {
        ps(0);
        return;
      }
      if (prev_max != n) {
        ans[i] = n;
      }

      prev_max = n;
      type = 1;
    } else {
      if (type == 0) {
        if (a[i] < prev_max) {
          ps(0);
          return;
        }
        if (prev_max != a[i]) {
          ans[i] = a[i];
          prev_max = a[i];
        }
      } else {
        if (a[i] > prev_max) {
          ps(0);
          return;
        }
        if (prev_max != a[i]) {
          ans[i] = prev_max;
          prev_max = a[i];
        }
      }
    }
  }
  if (type == 0) {
    ps(0);
    return;
  }

  ans[n - 1] = prev_max;

  set<int32_t> ss;
  FOR(i, 0, n) {
    if (ans[i] > 0 && ans[i] != n) {
      if (ss.count(ans[i])) {
        ps(0);
        return;
      }
      ss.insert(ans[i]);
    }
  }
  ss.insert(n - 1);
  ss.insert(n);

  int32_t fin_ans = 2;

  int32_t ll = 1;

  set<int32_t> cur_ss;

  int32_t l = 0, r = n - 1;

  while (l < r) {
    if (ans[l] < ans[r]) {
      while (ll < ans[l]) {
        if (!ss.count(ll)) {
          cur_ss.insert(ll);
        }
        ll++;
      }

      l++;
      while (ans[l] == 0) {
        fin_ans = MO::mul(fin_ans, sz(cur_ss));
        // DBG("A");

        if (cur_ss.empty()) {
          ps(0);
          return;
        }
        ss.insert(*cur_ss.rbegin());
        cur_ss.erase(*cur_ss.rbegin());
        l++;
      }
    } else {
      if (ans[r] == n)
        break;
      while (ll < ans[r]) {
        if (!ss.count(ll)) {
          cur_ss.insert(ll);
        }
        ll++;
      }

      r--;
      while (ans[r] == 0) {
        fin_ans = MO::mul(fin_ans, sz(cur_ss));
        if (cur_ss.empty()) {
          ps(0);
          return;
        }

        ss.insert(*cur_ss.rbegin());
        cur_ss.erase(*cur_ss.rbegin());
        r--;
      }
    }
  }

  int32_t k = 1;
  FOR(i, 1, n - 1) {
    if (!ss.count(i)) {
      fin_ans = MO::mul(fin_ans, k);
      k++;
    }
  }

  ps(fin_ans);
}

int main() {
  setIO();

  size_t t;
  re(t);

  while (t--) {
    re(n);
    FOR(i, 0, n - 1) { re(a[i]); }

    solve();
  }

  return 0;
}
