#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 2e5 + 5;

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

int32_t n;

int32_t b[MAXN], k = 0;

vector<int32_t> graph[MAXN];
int32_t mx[MAXN];

int32_t special[MAXN];

int32_t biggest_leaf;

void rec(int32_t v, int32_t par = -1) {

  mx[v] = 0;

  for (auto x : graph[v]) {
    if (x == par) {
      continue;
    }
    rec(x, v);

    if (v != n || mx[x] != n - 1) {
      mx[v] = max(mx[v], mx[x]);
    }
  }

  special[v] = mx[v];

  if (mx[v] < v) {
    b[k++] = v;
  }

  mx[v] = max(mx[v], v);

  if (graph[v].size() == 1) {
    biggest_leaf = max(biggest_leaf, v);
  }
}

int32_t T[MAXN];
int32_t pref_sum[MAXN];
int32_t ind[MAXN];

int32_t query(int32_t l, int32_t r) {
  if (l == 0) {
    return pref_sum[r];
  }
  if (l > r) {
    return 0;
  }

  return MO::add(pref_sum[r], -pref_sum[l - 1]);
}

void solve() {
  k = 0;
  biggest_leaf = 1;

  rec(n);

  sort(b, b + k);

  int32_t ans = 0;
  pref_sum[0] = 0;

  for (int32_t i = 0; i < k; i++) {
    ind[b[i]] = i;

    if (b[i] == biggest_leaf) {
      T[i] = 1;
      pref_sum[i] = 1;

      continue;
    }

    int32_t up_to = ind[special[b[i]]];

    T[i] = query(up_to + 1, i - 1);

    pref_sum[i] = MO::add(i == 0 ? 0 : pref_sum[i - 1], T[i]);
  }

  cout << max(1, T[k - 1]) << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n;

    for (int32_t i = 1; i <= n; i++) {
      graph[i].clear();
    }

    int32_t u, v;
    for (int32_t i = 0; i < n - 1; i++) {
      cin >> u >> v;

      graph[u].push_back(v);
      graph[v].push_back(u);
    }
    solve();
  }

  return 0;
}
