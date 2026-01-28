#include <bits/stdc++.h>
#include <cstdint>
#include <cstring>
#include <ios>
#include <string>

const int32_t MAXN = int32_t(1e2) + 5;
const int32_t MOD = 998244353;

int32_t n;
std::string a;

int32_t dp[MAXN][MAXN][MAXN][4];

int32_t add(int64_t x, int64_t y) { return (x + y + MOD) % MOD; }

void solve() {
  int32_t answer = 0;

  for (int32_t i{0}; i <= n; i++) {
    for (int32_t j{0}; j <= n; j++) {
      for (int32_t z{0}; z <= n; z++) {
        for (int32_t k{0}; k < 4; k++) {
          dp[i][j][z][k] = 0;
        }
      }
    }
  }

  dp[0][0][0][0] = 1;

  for (int32_t i = 0; i < n; i++) {
    for (int32_t j = 0; j <= n; j++) {
      for (int32_t len = 0; len <= n; len++) {
        for (int32_t k = 0; k < 4; k++) {
          if (a[i] == '(') {
            int32_t nxt_k = ((k == 0 || k == 3) ? k : k + 1);

            dp[i + 1][j + 1][len + 1][nxt_k] =
                add(dp[i + 1][j + 1][len + 1][nxt_k], dp[i][j][len][k]);
          } else if (j - 1 >= 0) {
            int32_t nxt_k = ((k == 0) ? 1 : k);
            dp[i + 1][j - 1][len + 1][nxt_k] =
                add(dp[i + 1][j - 1][len + 1][nxt_k], dp[i][j][len][k]);
          }
          // dont take
          dp[i + 1][j][len][k] = add(dp[i + 1][j][len][k], dp[i][j][len][k]);
        }
      }
    }
  }

  /*for (int32_t i{0}; i <= n; i++) {
    for (int32_t j{0}; j <= n; j++) {
      for (int32_t z{0}; z <= n; z++) {
        for (int32_t k{0}; k < 4; k++) {
          std::cout << dp[i][j][z][k] << " " << i << " " << j << " " << z << " "
                    << k << "\n";
        }
      }
    }
  }*/

  for (int32_t len{2}; len <= n; len++) {
    answer = add(answer, (int64_t(dp[n][0][len][3]) * (len - 2)) % MOD);
  }

  std::cout << answer << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int32_t t;
  std::cin >> t;

  while (t--) {
    std::cin >> n;

    std::cin >> a;
    solve();
  }

  return 0;
}
