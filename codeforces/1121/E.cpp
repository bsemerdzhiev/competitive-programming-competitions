#include <bits/stdc++.h>
#include <cstdint>
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
const int32_t MAXN = 3e3 + 5;
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
int32_t prime_factors[MAXN];
int32_t max_numb[MAXN][MAXN];
int32_t two_powers[MAXN];

void solve() {
  sort(a, a + n);

  int32_t ans = 0;
  for (int32_t i{0}; i < n; i++) {
    vector<int32_t> vv;
    for (int32_t j{i + 1}; j < n; j++) {
      vv.push_back(max_numb[a[i]][a[j]]);
    }
    sort(vv.begin(), vv.end());

    for (int32_t j{0}; j < sz(vv); j++) {
      ans = MO::add(ans, MO::mul(vv[j], two_powers[sz(vv) - j - 1]));
    }
    ans = MO::add(ans, a[i]);
  }
  ps(ans);
}

void get_primes() {
  vi is_prime(MAXN, 1);

  FOR(i, 1, MAXN) { prime_factors[i] = 1; }

  for (int64_t i{2}; i < MAXN; i++) {
    if (is_prime[i]) {
      for (int64_t j{i * i}; j < MAXN; j += i) {
        is_prime[j] = 0;
      }
      for (int64_t j{i}; j < MAXN; j += i) {
        prime_factors[j] *= i;
      }
    }
  }
  two_powers[0] = 1;
  for (int32_t i{1}; i < MAXN; i++) {
    two_powers[i] = MO::mul(two_powers[i - 1], 2);
  }

  for (int32_t i{1}; i < MAXN; i++) {
    max_numb[i][i] = i;

    for (int32_t j{1}; j < i; j++) {
      if (j % prime_factors[i] == 0) {
        assert(j != 1);

        max_numb[j][i] = max_numb[j - 1][i - 1];
      } else {
        max_numb[j][i] = max_numb[j][i - 1];
      }
    }
  }
}

int main() {
  setIO();

  get_primes();

  size_t t;
  re(t);

  while (t--) {
    re(n);
    FOR(i, 0, n) { re(a[i]); }

    solve();
  }

  return 0;
}
