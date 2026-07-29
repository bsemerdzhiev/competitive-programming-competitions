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

int32_t n, m;
vector<str> a;

void solve() {
  vector<vector<vi>> row_left_add, row_right_remove, row_up_remove,
      row_up_remove_right;

  row_left_add.resize(n + 1);
  row_right_remove.resize(n + 1);
  row_up_remove.resize(n + 1);
  row_up_remove_right.resize(n + 1);

  FOR(i, 0, n) {
    row_left_add[i].resize(m + 1);
    row_right_remove[i].resize(m + 1);
    row_up_remove[i].resize(m + 1);
    row_up_remove_right[i].resize(m + 1);
  }

  vector<vi> is_paired;
  is_paired.resize(m);
  FOR(j, 0, m) {
    is_paired[j].resize(m);
    FOR(z, 0, m) { is_paired[j][z] = -1; }
  }

  FOR(i, 0, n) {
    FOR(j, 1, m) {
      if (a[i][j] != '1')
        continue;

      FOR(z, 0, j) {
        if (a[i][z] == '1') {
          if (is_paired[z][j] != -1) {
            int32_t rect_size = (j - z + 1) * (i - is_paired[z][j] + 1);

            row_left_add[i][z].pb(rect_size);
            if (j + 1 < m) {
              row_right_remove[i][j + 1].pb(rect_size);
            }

            if (is_paired[z][j] - 1 >= 0) {
              row_up_remove[is_paired[z][j] - 1][z].pb(rect_size);
              if (j + 1 < m) {
                row_up_remove_right[is_paired[z][j] - 1][j + 1].pb(rect_size);
              }
            }
          }
          is_paired[z][j] = i;
        }
      }
    }
  }
  // return;
  vector<vi> ans(n + 1);
  FOR(i, 0, n) { ans[i].resize(m + 1, 1e9); }

  vector<multiset<int32_t>> cur_ss;
  cur_ss.resize(m + 1);

  for (int32_t i = n - 1; i >= 0; i--) {
    multiset<int32_t> cur_adds;
    multiset<int32_t> cur_erases;
    for (int32_t j = 0; j < m; j++) {
      trav(x, row_left_add[i][j]) { cur_adds.insert(x); }
      trav(x, row_right_remove[i][j]) { cur_adds.erase(cur_adds.find(x)); }
      trav(x, row_up_remove[i][j]) { cur_erases.ins(x); }
      trav(x, row_up_remove_right[i][j]) {
        cur_erases.erase(cur_erases.find(x));
      }

      trav(x, cur_adds) { cur_ss[j].insert(x); }
      trav(x, cur_erases) { cur_ss[j].erase(cur_ss[j].find(x)); }

      if (!cur_ss[j].empty()) {
        ans[i][j] = *cur_ss[j].begin();
      }
    }
  }

  FOR(i, 0, n) {
    FOR(j, 0, m) { pr(ans[i][j] == 1e9 ? 0 : ans[i][j], " "); }
    ps();
  }
}

int main() {
  setIO();

  size_t t;
  re(t);

  while (t--) {
    re(n, m);
    a.resize(n);
    FOR(i, 0, n) { re(a[i]); }

    solve();
  }

  return 0;
}
