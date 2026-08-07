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

int32_t n;
vi graph[MAXN];
int32_t lvl[MAXN];
bool mark[MAXN];

int32_t dfs(int32_t v, int32_t p, int32_t dist) {
  int32_t cur = dist;
  lvl[v] = dist;
  trav(x, graph[v]) {
    if (x == p || mark[x])
      continue;
    cur = max(cur, dfs(x, v, dist + 1));
  }
  return cur;
}

bool dfs_mark(int32_t v, int32_t p, int32_t cur_dist, set<int32_t> &to_add) {
  int32_t should_add = 0;

  trav(x, graph[v]) {
    if (x == p || mark[x]) {
      continue;
    }
    if (dfs_mark(x, v, cur_dist - 1, to_add)) {
      should_add++;
    }
  }
  if (should_add > 1) {
    to_add.ins(cur_dist);
  }
  return cur_dist == 0 || should_add;
}

void solve() {
  FOR(i, 1, n + 1) {
    lvl[i] = 0;
    mark[i] = 0;
  }
  dfs(1, 1, 0);

  int32_t farthest = 1;
  FOR(i, 1, n + 1) {
    if (lvl[i] > lvl[farthest]) {
      farthest = i;
    }
  }
  FOR(i, 1, n + 1) { lvl[i] = 0; }
  int32_t diag = dfs(farthest, farthest, 0);

  int32_t node_a = farthest;
  int32_t node_b = farthest;

  FOR(i, 1, n + 1) {
    if (lvl[i] > lvl[node_b]) {
      node_b = i;
    }
  }

  int32_t v = node_b;

  vi my_nodes;
  while (v != node_a) {
    my_nodes.pb(v);
    trav(x, graph[v]) {
      if (lvl[x] + 1 == lvl[v]) {
        v = x;
        break;
      }
    }
  }
  my_nodes.pb(node_a);
  set<int32_t> vv[2];

  for (int32_t i{0}; i < sz(my_nodes); i++) {
    if (i + 1 == (diag + 1) / 2) {
      mark[my_nodes[i]] = mark[my_nodes[i + 1]] = 1;
      FOR(i, 1, n + 1) { lvl[i] = 0; }

      dfs_mark(my_nodes[i], my_nodes[i], diag / 2, vv[0]);

      FOR(i, 1, n + 1) { lvl[i] = 0; }

      dfs_mark(my_nodes[i + 1], my_nodes[i + 1], diag / 2, vv[1]);

      break;
    }
  }

  vv[0].ins(0);
  vv[1].ins(0);

  set<int32_t> ss;
  trav(x, vv[0]) {
    trav(z, vv[1]) { ss.insert(diag - x - z); }
  }
  pr(sz(ss), " ");
  trav(x, ss) { pr(x, " "); }
  ps();
}

int main() {
  setIO();

  size_t t;
  re(t);

  while (t--) {
    re(n);
    FOR(i, 1, n + 1) { graph[i].clear(); }

    int32_t v, w;
    FOR(i, 0, n - 1) {
      re(v, w);
      graph[v].pb(w);
      graph[w].pb(v);
    }

    solve();
  }

  return 0;
}
