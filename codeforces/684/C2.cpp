#include <bits/stdc++.h>
#include <unordered_map>

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
const int32_t MAXN = 1e2 + 5;
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
str a[MAXN];
unordered_map<str, int32_t> par;
vector<vi> pos_moves = {{0, 1, 2}, {0, 1, 3}, {0, 2, 3}, {1, 2, 3}};

void precalc() {
  unordered_map<char, char> to_swap;

  to_swap['0'] = '1';
  to_swap['1'] = '0';

  queue<str> moves;

  moves.push("0000");
  unordered_map<str, bool> visited;

  visited["0000"] = 1;

  while (!moves.empty()) {
    auto cur_move = moves.front();
    moves.pop();

    int32_t kk = 0;
    for (auto x : pos_moves) {
      str new_move = cur_move;
      for (auto z : x) {
        new_move[z] = to_swap[new_move[z]];
      }
      if (!visited[new_move]) {
        visited[new_move] = 1;
        par[new_move] = kk;

        moves.push(new_move);
      }
      kk++;
    }
  }
}

void solve() {
  unordered_map<char, char> to_swap;
  to_swap['0'] = '1';
  to_swap['1'] = '0';

  vector<std::array<pi, 3>> fin_moves;
  if (n % 2 != 0) {
    FOR(i, 0, m) {
      if (a[0][i] == '1') {
        int32_t nxt = (i + 1 == m ? i - 1 : i + 1);

        a[0][i] = to_swap[a[0][i]];
        a[1][i] = to_swap[a[1][i]];
        a[1][nxt] = to_swap[a[1][nxt]];
        fin_moves.push_back({mp(0, i), mp(1, i), mp(1, nxt)});
      }
    }
  }
  if (m % 2 != 0) {
    FOR(i, 0, n) {
      if (a[i][0] == '1') {
        int32_t nxt = (i + 1 == n ? i - 1 : i + 1);

        a[i][0] = to_swap[a[i][0]];
        a[i][1] = to_swap[a[i][1]];
        a[nxt][1] = to_swap[a[nxt][1]];
        fin_moves.push_back({mp(i, 0), mp(i, 1), mp(nxt, 1)});
      }
    }
  }

  for (int32_t i{n % 2}; i < n; i += 2) {
    for (int32_t j{m % 2}; j < m; j += 2) {
      str cur_str = std::format("{}{}{}{}", (a[i][j]), (a[i][j + 1]),
                                (a[i + 1][j]), (a[i + 1][j + 1]));

      while (cur_str != "0000") {
        vpi cur_moves;
        for (auto x : pos_moves[par[cur_str]]) {
          cur_str[x] = to_swap[cur_str[x]];

          if (x >= 2) {
            cur_moves.push_back(mp(i + 1, j + x - 2));
          } else {
            cur_moves.push_back(mp(i, j + x));
          }
        }
        fin_moves.push_back({cur_moves[0], cur_moves[1], cur_moves[2]});
      }
    }
  }
  ps(sz(fin_moves));
  trav(x, fin_moves) {
    ps(x[0].first + 1, x[0].second + 1, x[1].first + 1, x[1].second + 1,
       x[2].first + 1, x[2].second + 1);
  }
}

int main() {
  setIO();

  size_t t;
  cin >> t;

  precalc();

  while (t--) {
    re(n, m);
    FOR(i, 0, n) { re(a[i]); }
    solve();
  }

  return 0;
}
