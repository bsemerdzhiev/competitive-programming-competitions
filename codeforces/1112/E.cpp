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

int32_t n, a[MAXN * 2];

struct segment_tree {
  int32_t tree[tSZ];
  int32_t lazy[tSZ];

  void push_down(int32_t k, int32_t l, int32_t r) {
    if (lazy[k]) {
      tree[k] += lazy[k];

      if (l != r) {
        lazy[k << 1] += lazy[k];
        lazy[k << 1 | 1] += lazy[k];
      }
      lazy[k] = 0;
    }
  }

  void update(int32_t k, int32_t l, int32_t r, int32_t i, int32_t j,
              int32_t val) {
    push_down(k, l, r);
    // if (i > j)
    //   return;
    if (r < i || l > j)
      return;

    if (r <= j && l >= i) {
      lazy[k] += val;
      push_down(k, l, r);

      return;
    }
    int32_t middle = (l + r) >> 1;

    update(k << 1, l, middle, i, j, val);
    update(k << 1 | 1, middle + 1, r, i, j, val);

    tree[k] = max(tree[k << 1], tree[k << 1 | 1]);
  }

  int32_t query(int32_t k, int32_t l, int32_t r) {
    push_down(k, l, r);

    if (l == r) {
      return l;
    }

    int32_t middle = (l + r) >> 1;

    if (tree[k] > 2) {
      int32_t ans = 0;
      if (tree[k << 1] + lazy[k << 1] > 2) {
        ans = query(k << 1, l, middle);
      } else {
        ans = query(k << 1 | 1, middle + 1, r);
      }
      return ans;
    } else {
      return 0;
    }
  }
};

segment_tree st;

void solve() {
  FOR(i, 0, 4 * n) { st.tree[i] = st.lazy[i] = 0; }
  map<int32_t, int32_t> prev_val;
  int32_t ans = n;

  FOR(i, 0, 2 * n) {
    prev_val[a[i]] = i;
    int32_t L = max(0, i - n + 1);
    int32_t R = min(i, n - 1);

    st.update(1, 0, n - 1, L, R, 1);

    auto pv = prev_val.find(a[i] - 1);
    if (pv != prev_val.end() && pv->second >= L) {
      st.update(1, 0, n - 1, L, min(R, pv->second), -1);
    }

    pv = prev_val.find(a[i] + 1);
    if (pv != prev_val.end() && pv->second >= L) {
      st.update(1, 0, n - 1, L, min(R, pv->second), -1);
    }

    while (st.tree[1] > 2) {
      int32_t ind = st.query(1, 0, n - 1);
      st.update(1, 0, n - 1, ind, ind, -1e9);

      ans--;
    }
  }

  ps(ans);
}

int main() {
  setIO();

  size_t t;
  re(t);

  while (t--) {
    re(n);
    FOR(i, 0, n) {
      re(a[i]);
      a[i + n] = a[i];
    }

    solve();
  }

  return 0;
}
