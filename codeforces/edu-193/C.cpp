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

int64_t n, m, x, y, a[2][MAXN];

void solve() {
  reverse(a[0], a[0] + x);
  reverse(a[1], a[1] + y);
  int64_t best_ans = 0;
  FOR(z, 0, 2) {
    unordered_set<int64_t> ss, ss2;

    int64_t cur_ans = 0;
    FOR(i, 0, min(x, n - 1)) {
      ss.insert(a[z][i]);
      cur_ans += a[z][i];
    }

    int32_t add = 0;
    FOR(i, 0, min(y, m)) {
      if (ss.count(a[z ^ 1][i])) {
        add++;
      } else {
        cur_ans += a[z ^ 1][i];
      }
      ss2.insert(a[z ^ 1][i]);
    }

    int32_t ll = sz(ss), rr = sz(ss2);

    while (add) {
      if (ll == x && rr == y) {
        break;
      }

      if (ll == x) {
        if (ss.count(a[z ^ 1][rr])) {
          add++;
        } else {
          cur_ans += a[z ^ 1][rr];
        }
        ss2.insert(a[z ^ 1][rr]);

        rr++;
        add--;
        continue;
      } else if (rr == y) {
        if (ss2.count(a[z][ll])) {
          add++;
        } else {
          cur_ans += a[z][ll];
        }

        ss.insert(a[z][ll]);
        ll++;
        add--;
        continue;
      } else {
        if (a[z][ll] > a[z ^ 1][rr]) {
          if (ss2.count(a[z][ll])) {
            add++;
          } else {
            cur_ans += a[z][ll];
          }

          ss.insert(a[z][ll]);
          ll++;
          add--;
        } else {
          if (ss.count(a[z ^ 1][rr])) {
            add++;
          } else {
            cur_ans += a[z ^ 1][rr];
          }
          ss2.insert(a[z ^ 1][rr]);

          rr++;
          add--;
        }
      }
    }
    best_ans = max(best_ans, cur_ans);

    swap(n, m);
    swap(x, y);
  }
  ps(best_ans);
}

int main() {
  setIO();

  size_t t;
  re(t);

  while (t--) {
    re(n, m, x, y);

    FOR(i, 0, x) { re(a[0][i]); }
    FOR(i, 0, y) { re(a[1][i]); }

    solve();
  }

  return 0;
}
