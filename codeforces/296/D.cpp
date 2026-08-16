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

int32_t n, m, k;
str a, b;

void fft(int32_t N, vector<complex<double>> &A, bool inv) {
  if (N == 1) {
    return;
  }

  vector<complex<double>> even(N / 2, 0), odd(N / 2, 0);
  FOR(i, 0, N / 2) {
    even[i] = A[i << 1];
    odd[i] = A[i << 1 | 1];
  }

  fft(N / 2, even, inv);
  fft(N / 2, odd, inv);

  double angle = 2 * PI * (inv ? -1 : 1) / N;

  complex<double> wk = 1;
  complex<double> wn = complex(cos(angle), sin(angle));

  FOR(i, 0, N / 2) {
    A[i] = even[i] + wk * odd[i];
    A[i + N / 2] = even[i] - wk * odd[i];

    if (inv) {
      A[i] /= 2;
      A[i + N / 2] /= 2;
    }
    wk *= wn;
  }
}

void solve() {
  int32_t N = 1;
  while (N <= n) {
    N *= 2;
  }
  N *= 2;

  vi cnt(N, 0);
  for (char c : {'A', 'C', 'G', 'T'}) {
    queue<int32_t> qq;

    for (int32_t i{0}; i < n; i++) {
      if (a[i] == c) {
        qq.push(i);
      }
    }
    vector<complex<double>> mark(N, 0);
    vector<complex<double>> mark2(N, 0);

    for (int32_t i{0}; i < n; i++) {
      while (!qq.empty() && abs(qq.front() - i) > k && qq.front() < i)
        qq.pop();

      if (qq.empty()) {
        break;
      }

      if (abs(qq.front() - i) <= k) {
        mark[i] = 1;
      }
    }
    FOR(i, 0, m) {
      if (b[m - i - 1] == c) {
        mark2[i] = 1;
      }
    }

    fft(N, mark, false);
    fft(N, mark2, false);

    FOR(i, 0, N) { mark[i] *= mark2[i]; }

    fft(N, mark, true);

    FOR(i, 0, N) { cnt[i] += roundl(mark[i].real()); }
  }
  int32_t ans = 0;
  FOR(i, 0, N) {
    if (cnt[i] == m) {
      ans++;
    }
  }
  ps(ans);
}

int main() {
  setIO();

  re(n, m, k);
  re(a);
  re(b);

  solve();

  return 0;
}
