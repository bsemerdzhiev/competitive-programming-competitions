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

int32_t n, a[2][MAXN];
int32_t mx[2][MAXN], mn[2][MAXN];
int32_t mx_r[2][MAXN], mn_r[2][MAXN];

void solve() {
  mx[0][0] = a[0][0];
  mn[0][0] = a[0][0];

  mx[1][0] = a[1][0];
  mn[1][0] = a[1][0];

  mx_r[0][n - 1] = a[0][n - 1];
  mn_r[0][n - 1] = a[0][n - 1];

  mx_r[1][n - 1] = a[1][n - 1];
  mn_r[1][n - 1] = a[1][n - 1];

  FOR(j, 0, 2) {
    FOR(i, 1, n) {
      mx[j][i] = max(mx[j][i - 1], a[j][i]);
      mn[j][i] = min(mn[j][i - 1], a[j][i]);
    }
  }

  FOR(j, 0, 2) {
    for (int32_t i{n - 2}; i >= 0; i--) {
      mx_r[j][i] = max(mx_r[j][i + 1], a[j][i]);
      mn_r[j][i] = min(mn_r[j][i + 1], a[j][i]);
    }
  }

  int64_t ans = 0;
  vector<int64_t> fin_ans(2 * n + 1, 2 * n + 1);

  FOR(i, 0, n) {
    int64_t lb = min(mn[0][i], mn_r[1][i]);
    int64_t ub = max(mx[0][i], mx_r[1][i]);

    fin_ans[lb] = min(fin_ans[lb], ub);
  }
  int64_t rem_ub = 2 * n + 1;

  for (int32_t i{2 * n}; i >= 1; i--) {
    rem_ub = min(rem_ub, fin_ans[i]);

    ans += (int64_t(2) * n - rem_ub + 1);
  }
  ps(ans);
}

int main() {
  setIO();

  size_t t;
  re(t);

  while (t--) {
    re(n);

    FOR(i, 0, n) { re(a[0][i]); }

    FOR(i, 0, n) { re(a[1][i]); }

    solve();
  }

  return 0;
}
