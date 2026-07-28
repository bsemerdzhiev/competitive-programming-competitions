#include <bits/stdc++.h>
#include <functional>

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

int32_t n, m, v[MAXN], w[MAXN], c[MAXN];
int32_t par[MAXN], cnt[MAXN];

int32_t get(int32_t l) {
  if (par[l] == l) {
    return l;
  }
  return par[l] = get(par[l]);
}

void connect(int32_t l, int32_t r) {
  l = par[l];
  r = par[r];

  if (cnt[l] > cnt[r]) {
    par[r] = l;
    cnt[l] += cnt[r];
  } else {
    par[l] = r;
    cnt[r] += cnt[l];
  }
}

void solve() {
  FOR(i, 1, n + 1) {
    par[i] = i;
    cnt[i] = 1;
  }

  vi deg(n + 1, 0);
  vi br(n + 1, 0);
  int64_t ans = 0;
  FOR(i, 0, m) {
    if (v[i] != w[i]) {
      deg[v[i]]++;
      deg[w[i]]++;
    }
    ans += c[i];
  }
  FOR(i, 1, n + 1) {
    if (deg[i] % 2 == 1) {
      br[i]++;

      // ps(i);
    }
  }

  using QueueType = pair<int64_t, int64_t>;
  vector<priority_queue<QueueType, vector<QueueType>, std::less<QueueType>>> pq(
      n + 1);

  FOR(i, 0, m) {
    int32_t left = get(v[i]);
    int32_t right = get(w[i]);
    int64_t min_so_far = int64_t(c[i]);

    if (left != right) {
      int32_t br_left = br[left];
      int32_t br_right = br[right];
      int32_t old_right = right;
      int32_t old_left = left;

      connect(left, right);
      left = get(left);
      if (old_right == left) {
        old_right = old_left;
      }

      if (br_left == br_right && br_left == 1) {
        pq[left].push(mp(min_so_far, 1));
        ans += min_so_far;

        br[left] = 0;
      } else {
        br[left] = br_left + br_right;
      }

      while (!pq[old_right].empty()) {
        pq[left].push(pq[old_right].top());
        pq[old_right].pop();
      }
    }
    int64_t to_add_back = 0;

    while (!pq[left].empty() && pq[left].top().first > min_so_far) {
      to_add_back += pq[left].top().second;
      ans -= pq[left].top().first * pq[left].top().second;

      pq[left].pop();
    }
    ans += to_add_back * min_so_far;
    if (to_add_back)
      pq[left].push(mp(min_so_far, to_add_back));
  }
  ps(ans);
}

int main() {
  setIO();

  size_t t;
  re(t);

  while (t--) {
    re(n, m);

    FOR(i, 0, m) { re(v[i], w[i], c[i]); }

    solve();
  }

  return 0;
}
