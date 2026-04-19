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
string s;
vector<int32_t> graph[MAXN];
bool removed[MAXN];

int32_t total_cnt[MAXN], available[MAXN];

struct node {
  int32_t v;
  double needed;

  bool operator<(node other) const { return needed > other.needed; }
};

void solve() {
  priority_queue<node> qq;

  for (int32_t i = 1; i <= n; i++) {
    total_cnt[i] = 0;
    available[i] = 0;

    for (auto x : graph[i]) {
      if (s[x] == '1') {
        available[i]++;
      }
      total_cnt[i]++;
    }

    removed[i] = s[i] == '1' ? 1 : 0;

    double needed = sqrt(total_cnt[i]) - available[i];

    if (available[i])
      qq.push(node{i, needed});
  }
  double answer = 0;
  while (qq.size() > 0) {
    node to_remove = qq.top();
    qq.pop();

    if (removed[to_remove.v])
      continue;
    removed[to_remove.v] = 1;

    answer += 1.0 * total_cnt[to_remove.v] / available[to_remove.v];
    // cout << to_remove.v << " " << total_cnt[to_remove.v] << " "
    // << available[to_remove.v] << "\n";

    for (auto x : graph[to_remove.v]) {
      available[x]++;
      if (!removed[x]) {
        qq.push(node{x, to_remove.needed - 1});
      }
    }
  }

  cout << fixed << setprecision(7);
  cout << answer << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n;

    for (int32_t i = 1; i <= n; i++) {
      graph[i].clear();
    }

    cin >> s;
    s = "#" + s;

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
