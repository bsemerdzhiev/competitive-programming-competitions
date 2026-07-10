#include <bits/stdc++.h>
#include <cstdint>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 5e2 + 5;

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
string a[MAXN];
vector<int32_t> graph[MAXN];
vector<int32_t> bidir_graph[MAXN];

bool rec(int32_t v, int32_t orig, int32_t &visited) {
  if (a[orig][v] != '1') {
    return false;
  }
  visited++;
  if (visited > n) {
    return false;
  }

  for (auto x : graph[v]) {
    if (!rec(x, orig, visited)) {
      return false;
    }
  }
  return true;
}

bool vis[MAXN];

int32_t dfs(int32_t v, int32_t par) {
  if (vis[v]) {
    return -MAXN;
  }
  vis[v] = 1;
  int32_t ans = 1;
  for (auto x : bidir_graph[v]) {
    if (x == par)
      continue;
    ans += dfs(x, v);
  }
  return ans;
}

void solve() {
  for (int32_t i{1}; i <= n; i++) {
    graph[i].clear();
    bidir_graph[i].clear();
    vis[i] = 0;
  }
  int32_t br = 0;
  set<int32_t> ss;

  for (int32_t i{1}; i <= n; i++) {
    vector<int32_t> reaches;

    for (int32_t j{1}; j <= n; j++) {
      if (a[i][j] == '1' && j != i) {
        reaches.push_back(j);
      }
    }
    std::size_t k = reaches.size();

    for (int32_t z{0}; z < k; z++) {
      bool direct_reach = true;
      for (int32_t p{0}; p < k; p++) {
        if (z != p && a[reaches[p]][reaches[z]] == '1') {
          direct_reach = false;
        }
      }
      if (direct_reach) {
        ss.insert(i);
        ss.insert(reaches[z]);
        graph[i].push_back(reaches[z]);

        bidir_graph[i].push_back(reaches[z]);
        bidir_graph[reaches[z]].push_back(i);
        br++;
      }
    }
  }
  if (br != n - 1 || ss.size() != n) {
    cout << "No\n";
    return;
  }

  for (int32_t i{1}; i <= n; i++) {
    int32_t visited = 0;

    if (!rec(i, i, visited)) {
      cout << "No\n";
      return;
    }
    for (int32_t z{1}; z <= n; z++) {
      if (a[i][z] == '1') {
        visited--;
      }
    }
    if (visited != 0) {
      cout << "No\n";
      return;
    }
  }
  if (dfs(1, 1) != n) {
    cout << "No\n";
    return;
  }

  cout << "Yes\n";
  for (int32_t i{1}; i <= n; i++) {
    for (auto x : graph[i]) {
      cout << std::format("{} {}\n", i, x);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n;
    for (int32_t i{1}; i <= n; i++) {
      cin >> a[i];
      a[i] = "#" + a[i];
    }
    solve();
  }

  return 0;
}
