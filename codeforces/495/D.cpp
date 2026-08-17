#include <bits/stdc++.h>
#include <unordered_map>

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

int32_t k, a[MAXN];

void solve() {
  unordered_map<int32_t, int32_t> mm;
  int32_t val_b = 0;
  FOR(i, 0, k) {
    mm[a[i]]++;
    val_b = max(val_b, a[i]);
  }

  int32_t val_x = 1;
  FOR(i, 1, val_b + 2) {
    if (mm[i] != 4 * i) {
      val_x = i;
      break;
    }
  }

  FOR(n, 1, k + 1) {
    if (k % n == 0) {
      int32_t m = k / n;

      int32_t a = n + m - val_b - 2;
      int32_t y = a - val_x + 2;

      queue<pi> qq;

      if (y >= 1 && y <= m && val_x >= 1 && val_x <= n) {
        qq.push({val_x, y});

        unordered_map<int32_t, int32_t> exp = mm;
        vector<vi> mark;
        mark.resize(n + 1);
        FOR(i, 0, n + 1) { mark[i].resize(m + 1, 0); }

        mark[val_x][y] = 1;

        bool imp = false;
        while (!qq.empty()) {
          auto z = qq.front();
          qq.pop();

          exp[mark[z.first][z.second] - 1]--;
          if (exp[mark[z.first][z.second] - 1] < 0) {
            imp = true;
            break;
          }

          FOR(i, 0, 4) {
            pi new_z = {z.first + dx[i], z.second + dy[i]};
            if (new_z.first >= 1 && new_z.first <= n && new_z.second >= 1 &&
                new_z.second <= m && mark[new_z.first][new_z.second] == 0) {
              mark[new_z.first][new_z.second] = mark[z.first][z.second] + 1;
              qq.push({new_z.first, new_z.second});
            }
          }
        }

        if (!imp) {
          ps(n, m);
          ps(val_x, y);
          return;
        }
      }
    }
  }
  ps(-1);
}

int main() {
  setIO();

  re(k);
  FOR(i, 0, k) { re(a[i]); }

  solve();

  return 0;
}
