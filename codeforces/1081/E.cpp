#include <bits/stdc++.h>
#include <cstdint>
#include <unordered_map>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 1e6 + 5;

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

int32_t n, a[MAXN], b[MAXN];
int32_t edge_count[MAXN];
unordered_map<int32_t, int32_t> edge_cnt[MAXN];
vector<int32_t> graph[MAXN];
multiset<int32_t> ms[MAXN];
int32_t all_edges = 0;

bool dfs(int32_t v, int32_t first) {
  int32_t trg = 0;
  int32_t burn_bridge = 0;

  for (auto x : edge_cnt[v]) {
    if (edge_count[x.first] > 1) {
      trg = x.first;
    } else if (edge_count[x.first] == 1) {
      burn_bridge = x.first;
    }
  }
  if (trg == 0) {
    trg = burn_bridge;
  }
  if (trg == 0)
    return v == first;

  edge_cnt[v][trg]--;
  edge_cnt[trg][v]--;

  if (edge_cnt[v][trg] == 0) {
    edge_cnt[v].erase(trg);
    edge_cnt[trg].erase(v);
  }

  edge_count[v]--;
  edge_count[trg]--;

  ms[v].insert(trg);
  all_edges++;
  return dfs(trg, first);
}

void solve() {
  for (int32_t i = 1; i <= n; i++) {
    edge_count[i] = 0;
    edge_cnt[i].clear();
    ms[i].clear();
  }
  all_edges = 0;

  for (int32_t i = 0; i < n; i++) {
    edge_cnt[a[i]][b[i]]++;
    edge_cnt[b[i]][a[i]]++;
    edge_count[a[i]]++;
    edge_count[b[i]]++;
  }

  vector<pair<int32_t, int32_t>> to_vis;

  for (int32_t i = 1; i <= n; i++) {
    if (edge_count[i] % 2 == 1) {
      to_vis.push_back(make_pair(0, i));
    } else {
      to_vis.push_back(make_pair(1, i));
    }
  }
  sort(to_vis.begin(), to_vis.end());

  bool is_possible = true;
  for (auto x : to_vis) {
    is_possible &= dfs(x.second, x.second);
  }
  if (!is_possible || all_edges < n) {
    cout << "-1\n";
    return;
  }

  vector<int32_t> answer;
  for (int32_t i = 0; i < n; i++) {
    if (!ms[a[i]].count(b[i]) && !ms[b[i]].count(a[i])) {
      return;
    }

    if (!ms[a[i]].count(b[i])) {
      answer.push_back(i + 1);
      ms[b[i]].erase(ms[b[i]].find(a[i]));
    } else {
      ms[a[i]].erase(ms[a[i]].find(b[i]));
    }
  }
  cout << answer.size() << "\n";
  for (auto x : answer) {
    cout << x << " ";
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
    for (int32_t i = 0; i < n; i++) {
      cin >> a[i];
    }

    for (int32_t i = 0; i < n; i++) {
      cin >> b[i];
      graph[i + 1].clear();
    }

    for (int32_t i = 0; i < n; i++) {
      graph[a[i]].push_back(b[i]);
      graph[b[i]].push_back(a[i]);
    }

    solve();
  }

  return 0;
}
