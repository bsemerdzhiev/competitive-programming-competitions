#include <bits/stdc++.h>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 2e5 + 5;

namespace MO {
int32_t add(int64_t x, int64_t y) { return (x + y + MOD) % MOD; }
int32_t mul(int64_t x, int64_t y) { return (x * y) % MOD; }

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
int64_t a[MAXN], ans[MAXN];
int64_t subtree_sum[MAXN];
int64_t total_sum[MAXN];
int64_t best_improv[MAXN];

int64_t max_depth[MAXN];

vector<int32_t> graph[MAXN];

void dfs(int32_t v, int32_t p, int32_t cur_depth) {
  subtree_sum[v] = a[v];
  total_sum[v] = 0;
  max_depth[v] = cur_depth;

  best_improv[v] = 0;

  multiset<int64_t> depths;

  for (const auto &x : graph[v]) {
    if (x != p) {
      dfs(x, v, cur_depth + 1);

      depths.insert(max_depth[x]);

      max_depth[v] = max(max_depth[v], max_depth[x]);

      best_improv[v] = max(best_improv[v], best_improv[x]);

      subtree_sum[v] += subtree_sum[x];

      total_sum[v] += total_sum[x];
      total_sum[v] += subtree_sum[x];
    }
  }

  // try to improve the total_sum

  for (const auto &x : graph[v]) {
    if (x == p)
      continue;
    depths.erase(depths.find(max_depth[x]));

    if (!depths.empty()) {
      best_improv[v] =
          max(best_improv[v], subtree_sum[x] * (*depths.rbegin() - cur_depth));
    }

    depths.insert(max_depth[x]);
  }

  ans[v] = total_sum[v] + best_improv[v];
}

void solve() {
  dfs(1, 1, 0);

  for (int32_t i = 1; i <= n; i++) {
    cout << ans[i] << " ";
  }
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n;

    for (int32_t i = 1; i <= n; i++) {
      cin >> a[i];
      graph[i].clear();
    }
    int32_t v, w;
    for (int32_t i = 0; i < n - 1; i++) {
      cin >> v >> w;

      graph[v].push_back(w);
      graph[w].push_back(v);
    }
    solve();
  }

  return 0;
}
