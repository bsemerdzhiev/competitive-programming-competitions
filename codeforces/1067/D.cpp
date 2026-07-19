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

int32_t n;
str a, b;

void solve() {
  map<int32_t, int32_t> map_to;

  map_to['1'] = '0';
  map_to['0'] = '1';

  vpi ans;
  FOR(i, 0, n - 4) {
    if (a[i] == b[i]) {
      continue;
    } else {
      if (a[i] == a[i + 1]) {
        ans.push_back(mp(i, i + 1));
        a[i + 0] = map_to[a[i + 0]];
        a[i + 1] = map_to[a[i + 1]];

      } else if (a[i] == a[i + 2]) {
        ans.push_back(mp(i, i + 2));

        a[i + 0] = map_to[a[i + 0]];
        a[i + 1] = map_to[a[i + 1]];
        a[i + 2] = map_to[a[i + 2]];
      } else {
        ans.push_back(mp(i + 1, i + 2));
        a[i + 1] = map_to[a[i + 1]];
        a[i + 2] = map_to[a[i + 2]];

        ans.push_back(mp(i, i + 1));
        a[i + 0] = map_to[a[i + 0]];
        a[i + 1] = map_to[a[i + 1]];
      }
    }
  }

  str rem = std::format("{}{}{}{}", a[n - 4], a[n - 3], a[n - 2], a[n - 1]);
  str desired = std::format("{}{}{}{}", b[n - 4], b[n - 3], b[n - 2], b[n - 1]);

  struct state {
    str cur_ss;
    vpi moves;
  };

  queue<state> qq;
  map<str, bool> vis;
  vis[rem] = 1;

  // DBG(sz(ans));

  qq.push({rem, {}});

  while (!qq.empty()) {
    auto x = qq.front();
    qq.pop();

    // DBG(x.cur_ss);

    if (x.cur_ss == desired) {
      for (auto xx : x.moves) {
        ans.push_back(xx);
      }
      ps(sz(ans));
      for (auto xx : ans) {
        ps(xx.first + 1, xx.second + 1);
      }
      return;
    }

    FOR(i, 0, 4) {
      FOR(j, i + 1, 4) {

        bool not_possible = 0;
        FOR(z, 0, j - i) {
          if (x.cur_ss[i + z] != x.cur_ss[j - z]) {
            not_possible = 1;
          }
        }
        if (!not_possible) {
          str new_s = x.cur_ss;
          vpi new_moves = x.moves;
          new_moves.push_back(mp(n - 4 + i, n - 4 + j));

          FOR(z, i, j + 1) { new_s[z] = map_to[new_s[z]]; }

          if (!vis[new_s]) {
            qq.push({new_s, new_moves});
            vis[new_s] = 1;
          }
        }
      }
    }
  }
}

int main() {
  setIO();

  size_t t;
  re(t);

  while (t--) {
    re(n);
    re(a);
    re(b);

    solve();
  }

  return 0;
}
