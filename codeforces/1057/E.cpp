#include <bits/stdc++.h>
#include <queue>

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
vi all_primes;

int64_t calc_times(int64_t x, int64_t numb, int64_t e_i) {
  int64_t ans = 0;
  for (int64_t j{numb}; j <= x; j *= numb) {
    ans += x / j;
  }
  return ans / e_i;
}

void solve() {
  int64_t ans = 0;

  int64_t up_to = 0;
  for (int32_t j{sz(all_primes) - 1}; j >= 0; j--) {
    if (all_primes[j] <= n) {
      up_to = all_primes[j];
      break;
    }
  }

  vi primes_to_use;
  trav(x, all_primes) {
    if (x <= n && (n / x) * x >= up_to) {
      primes_to_use.pb(x);
    }
  }

  for (int64_t i{up_to}; i < n; i++) {
    int64_t best_ans = 1e9;

    for (int32_t j{0}; j < sz(primes_to_use); j++) {
      int64_t x = primes_to_use[j];
      if (x > i)
        break;

      int64_t val_for_n = calc_times(n, x, 1);
      int64_t val_for_i = calc_times(i, x, 1);

      for (int64_t cur_number{x}, cnt = 1; cur_number <= m;
           cur_number *= x, cnt++) {
        if (val_for_n / cnt != val_for_i / cnt) {
          best_ans = min(best_ans, val_for_i / cnt);
        }
      }
    }
    ans += best_ans;
  }

  ps(ans);
}

void sieve() {
  vi non_primes(1e7 + 10, 0);
  all_primes.reserve(5e6);
  FOR(i, 2, 1e7 + 5) {
    if (!non_primes[i]) {
      all_primes.pb(i);
      for (int64_t j{int64_t(i) * i}; j <= 1e7; j += i) {
        non_primes[j] = 1;
      }
    }
  }
}

int main() {
  setIO();

  size_t t;
  re(t);

  sieve();

  while (t--) {
    re(n, m);

    solve();
  }

  return 0;
}
