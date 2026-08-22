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

int32_t n, m;
int32_t possible[MAXN][MAXN];
vi graph[MAXN];

int32_t side[MAXN];

bool rec(int32_t v, int32_t p, int32_t st, vector<vector<int32_t>> &vv) {
  side[v] = st;
  vv[st - 1].pb(v);

  bool ans = false;
  trav(x, graph[v]) {
    if (x == p)
      continue;

    if (side[x] != 0 && side[x] == side[v]) {
      return true;
    }

    if (side[x] != 0)
      continue;

    ans |= rec(x, v, st == 1 ? 2 : 1, vv);
  }
  return ans;
}

bool T[MAXN][MAXN];
char answer[MAXN];

bool match_pairs(int32_t ind, int32_t cur_size,
                 const vector<vector<vector<int32_t>>> &pairs) {
  if (cur_size > n / 2) {
    return false;
  }
  if (ind == pairs.size()) {
    return cur_size == n / 2;
  }
  if (T[ind][cur_size]) {
    return false;
  }
  T[ind][cur_size] = 1;
  if (match_pairs(ind + 1, cur_size + pairs[ind][0].size(), pairs)) {
    trav(x, pairs[ind][0]) { answer[x] = 'r'; }
    trav(x, pairs[ind][1]) { answer[x] = 'b'; }
    return true;
  }

  if (match_pairs(ind + 1, cur_size + pairs[ind][1].size(), pairs)) {
    trav(x, pairs[ind][0]) { answer[x] = 'b'; }
    trav(x, pairs[ind][1]) { answer[x] = 'r'; }
    return true;
  }
  return false;
}

void solve() {
  FOR(i, 1, n + 1) {
    FOR(j, 1, n + 1) {
      if (!possible[i][j] && i != j) {
        graph[i].pb(j);
      }
    }
  }
  bool ans = 0;
  vector<vector<vector<int32_t>>> pairs;
  FOR(i, 1, n + 1) {
    if (side[i] == 0) {
      vector<vector<int32_t>> vv;
      vv.resize(2);

      ans |= rec(i, i, 1, vv);

      pairs.pb(vv);
    }
  }

  if (ans) {
    ps("impossible");
    return;
  }

  // return;
  if (match_pairs(0, 0, pairs)) {
    FOR(i, 1, n + 1) { ps(answer[i]); }
  } else {
    ps("impossible");
  }
}

int main() {
  setIO();

  re(n, m);

  if (n >= 3e3 || n % 2 == 1) {
    ps("impossible");
    return 0;
  }

  int32_t v, w;
  FOR(i, 0, m) {
    re(v, w);

    possible[v][w] = possible[w][v] = 1;
  }

  solve();

  return 0;
}
