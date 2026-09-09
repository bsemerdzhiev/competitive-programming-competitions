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

int32_t n, q;
str a;
int32_t cnt[MAXN][4];

int32_t get_type(char c1, char c2) {
  if (c1 == '0' && c2 == '0') {
    return 0;
  } else if (c1 == '0' && c2 == '1') {
    return 1;
  } else if (c1 == '1' && c2 == '0') {
    return 2;
  } else {
    return 3;
  }
}

int32_t check(int32_t k, int32_t x1, int32_t x2, int32_t x3) {
  int32_t init_k = k;
  int32_t desired_number = x3 + k;

  if (x2 > x1)
    swap(x1, x2);

  int32_t to_rem1 = max(0, x1 - desired_number);

  k -= to_rem1;

  x2 -= k;

  if (k < 0 || x2 > desired_number)
    return -1;

  return desired_number - x2 + init_k;
}

void solve() {
  a = '#' + a;

  FOR(i, 1, n + 1) {
    FOR(j, 0, 4) { cnt[i][j] = cnt[i - 1][j]; }
    cnt[i][get_type(a[i], a[(i % n) + 1])]++;
  }

  int32_t l, r;
  int32_t br[4];

  FOR(i, 0, q) {
    re(l, r);

    FOR(j, 0, 4) { br[j] = cnt[r - 1][j] - cnt[l - 1][j]; }

    br[get_type(a[r], a[l])]++;

    int32_t ans = 0;
    if (br[0] == 0 && br[1] == 0) {
      br[3]--;
      br[1] = br[2] = 1;
      ans++;
    } else if (br[3] == 0 && br[1] == 0) {
      br[0]--;
      br[1] = br[2] = 1;
      ans++;
    }

    if (br[1] >= max(br[0], br[3])) {
      ans += br[1] - br[0] + br[1] - br[3];
      ps(ans);
    } else {
      int32_t low = 0, up = n;
      int32_t to_add = 0;

      while (low <= up) {
        int32_t middle = (low + up) >> 1;

        if (check(middle, br[0], br[3], br[1]) >= 0) {
          to_add = middle;
          up = middle - 1;
        } else {
          low = middle + 1;
        }
      }
      ps(ans + check(to_add, br[0], br[3], br[1]));
    }
  }
}

int main() {
  setIO();

  re(n, q);
  re(a);

  solve();

  return 0;
}
