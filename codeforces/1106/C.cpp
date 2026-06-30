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
vector<int32_t> graph[MAXN];

pair<int32_t, int64_t> rec(int32_t v, int32_t p, int32_t depth) {
  int64_t ans = 0;

  int32_t max_h = depth;
  int32_t cnt = 0;

  multiset<int32_t> ms;
  for (auto x : graph[v]) {
    if (x == p) {
      continue;
    }
    auto ans_p = rec(x, v, depth + 1);

    cnt++;

    ms.insert(ans_p.first);

    max_h = max(max_h, ans_p.first);

    ans += ans_p.second;
  }

  if (cnt >= 2) {
    ms.erase(ms.find(*ms.rbegin()));

    ans += *ms.rbegin() - depth + 1;
    // cout << min_h - depth + 1 << " " << v << "\n";
  } else {
    ans++;
  }
  return make_pair(max_h, ans);
}

void solve() { cout << rec(1, 1, 0).second << "\n"; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n;
    for (int32_t i{1}; i <= n; i++) {
      graph[i].clear();
    }
    int32_t w;
    for (int32_t i{2}; i <= n; i++) {
      cin >> w;

      graph[w].push_back(i);
      graph[i].push_back(w);
    }
    solve();
  }

  return 0;
}
