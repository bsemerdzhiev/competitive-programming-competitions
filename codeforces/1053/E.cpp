#include <bits/stdc++.h>
#include <cstdint>

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

int32_t n, v[MAXN], a[MAXN], b[MAXN];
int64_t tree[tSZ], lazy[tSZ];

void push_down(int32_t k, int32_t l, int32_t r) {
  if (lazy[k] != 0) {
    tree[k] += lazy[k];

    if (l != r) {
      lazy[k << 1] += lazy[k];
      lazy[k << 1 | 1] += lazy[k];
    }
    lazy[k] = 0;
  }
}

void update(int32_t k, int32_t l, int32_t r, int32_t i, int32_t j,
            int64_t val) {
  push_down(k, l, r);
  if (r < i || l > j) {
    return;
  }

  if (l >= i && r <= j) {
    lazy[k] += val;
    push_down(k, l, r);

    return;
  }
  int32_t middle = (l + r) >> 1;

  update(k << 1, l, middle, i, j, val);
  update(k << 1 | 1, middle + 1, r, i, j, val);

  tree[k] = max(tree[k << 1], tree[k << 1 | 1]);
}

int64_t query(int32_t k, int32_t l, int32_t r, int32_t i, int32_t j) {
  push_down(k, l, r);
  if (r < i || l > j) {
    return -1e16;
  }

  if (r <= j && l >= i) {
    return tree[k];
  }

  int32_t middle = (l + r) >> 1;

  return max(query(k << 1, l, middle, i, j),
             query(k << 1 | 1, middle + 1, r, i, j));
}

void solve() {
  FOR(i, 0, 3 * n) { tree[i] = lazy[i] = 0; }
  FOR(i, 1, n + 1) { update(1, 0, n, i, i, -1e14); }
  map<int32_t, int32_t> pos;

  FOR(i, 1, n + 1) { pos[b[i]] = i; }

  for (int32_t i{1}; i <= n; i++) {
    int64_t cur_ans_without = query(1, 0, n, 0, pos[a[i]]);

    update(1, 0, n, 0, pos[a[i]] - 1, v[a[i]]);

    int64_t cur_val = query(1, 0, n, pos[a[i]], pos[a[i]]);
    update(1, 0, n, pos[a[i]], pos[a[i]], -cur_val);

    update(1, 0, n, pos[a[i]], pos[a[i]], cur_ans_without);
  }
  int64_t ans = 0;
  FOR(i, 0, n + 1) { ans = max(ans, query(1, 0, n, i, i)); }
  ps(ans);
}

int main() {
  setIO();

  size_t t;
  re(t);

  while (t--) {
    re(n);

    FOR(i, 1, n + 1) { re(v[i]); }
    FOR(i, 1, n + 1) { re(a[i]); }
    FOR(i, 1, n + 1) { re(b[i]); }

    solve();
  }

  return 0;
}
