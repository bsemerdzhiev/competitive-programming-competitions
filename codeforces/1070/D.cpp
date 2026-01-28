#include <cstdint>
#include <cstdio>
#include <inttypes.h>
#include <map>
#include <vector>

#define MOD 998244353
#define MAXN size_t(2e5 + 5)

class ModOperation {
public:
  int32_t add(int32_t f, int32_t s) {
    return ((int64_t)f + (int64_t)s + MOD) % MOD;
  }

  int32_t mult(int32_t f, int32_t s) {
    return int32_t(((int64_t)f * (int64_t)s) % MOD);
  }
};

ModOperation mod_operator;

uint32_t n, m;
uint64_t a[MAXN];
std::vector<uint32_t> graph[MAXN];

std::map<std::pair<uint32_t, uint64_t>, int32_t> memo;

int32_t dfs(uint32_t v, uint64_t prev_value) {
  if (memo.count({v, prev_value})) {
    return memo[{v, prev_value}];
  }

  int32_t answer = 1;
  for (auto child : graph[v]) {
    if (a[v] + prev_value == a[child]) {
      // printf("%" PRIu32 " %" PRIu32 "\n", v, child);
      answer = mod_operator.add(answer, dfs(child, a[v]));
    }
  }

  return memo[{v, prev_value}] = answer;
}

void solve() {
  memo.clear();

  int32_t answer = 0;
  for (uint32_t i = 1; i <= n; i++) {
    for (auto child : graph[i]) {
      answer = mod_operator.add(answer, dfs(child, a[i]));
    }
  }

  printf("%" PRId32 "\n", answer);
}

int main() {
  uint32_t t;

  scanf("%" PRIu32, &t);

  while (t--) {
    scanf("%" PRIu32 " %" PRIu32, &n, &m);
    for (size_t i = 1; i <= n; i++) {
      scanf("%" PRIu64, &a[i]);
      graph[i].clear();
    }
    uint32_t from, to;
    for (size_t i = 0; i < m; i++) {
      scanf("%" PRIu32 "%" PRIu32, &from, &to);
      graph[from].push_back(to);
    }

    solve();
  }

  return 0;
}
