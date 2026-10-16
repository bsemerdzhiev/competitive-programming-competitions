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

int32_t n;
str a;

void solve() {
  vector<vector<int32_t>> pos;
  pos.assign(10, {});

  int32_t k = 0;
  trav(x, a) { pos[x - '0'].push_back(k++); }

  vector<vi> adds, removals;

  adds.assign(n, {});
  removals.assign(n, {});

  FOR(i, 0, n) {
    int32_t cur_pos = i;

    // find first 2
    auto it1 = std::lower_bound(pos[2].begin(), pos[2].end(), cur_pos);

    if (it1 == pos[2].end()) {
      adds[cur_pos].push_back(n - cur_pos);
      continue;
    }

    // find first 0
    auto it2 = std::lower_bound(pos[0].begin(), pos[0].end(), *it1);

    if (it2 == pos[0].end()) {
      adds[cur_pos].push_back(n - cur_pos);
      continue;
    }

    it2 = std::lower_bound(pos[2].begin(), pos[2].end(), *it2);

    // now find 2
    if (it2 == pos[2].end()) {
      adds[cur_pos].push_back(n - cur_pos);
      continue;
    }

    // find next 5 after the 2
    auto it3 = std::lower_bound(pos[5].begin(), pos[5].end(), *it2);

    if (it3 == pos[5].end()) {
      adds[cur_pos].push_back(n - cur_pos);
      continue;
    }

    // find next 6 after the 2
    auto it4 = std::lower_bound(pos[6].begin(), pos[6].end(), *it2);

    if (it4 == pos[6].end()) {
      // now 6
      adds[cur_pos].push_back(*it3 - cur_pos);
      removals[*it3].push_back(1);
    } else {
      // check two cases
      if (*it4 < *it3) {
        // 6 happens before 5
        adds[cur_pos].push_back(n - cur_pos);
      } else {
        // 5 happens before 6
        adds[cur_pos].push_back((n - cur_pos) - (*it4 - *it3));

        removals[*it3].push_back(1);

        adds[*it4].push_back(0);
      }
    }
  }

  int64_t cur_sum = 0;
  int64_t plus_cnt = 0;

  FOR(i, 0, n) {
    trav(x, removals[i]) {
      cur_sum--;
      plus_cnt--;
    }

    cur_sum -= plus_cnt;

    trav(x, adds[i]) {
      plus_cnt++;
      cur_sum += x;
    }

    pr(cur_sum, " ");
  }
  ps();
}

int main() {
  setIO();

  size_t t;
  re(t);

  while (t--) {
    re(n);
    re(a);

    solve();
  }

  return 0;
}
