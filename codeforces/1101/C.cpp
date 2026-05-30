#include <bits/stdc++.h>
#include <type_traits>

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

int32_t n, x, s;
string a;
int32_t tables[MAXN];

void solve() {
  for (int32_t i = 0; i < x; i++) {
    tables[i] = 0;
  }

  int32_t k = 0;

  queue<int32_t> pos;
  queue<int32_t> to_fill;

  for (int32_t i = 0; i < n; i++) {
    // cout << i << " " << k << "\n";
    if (a[i] == 'I') {
      // cout << k << "\n";
      if (k == x) {
        continue;
      }
      tables[k++] = 1;

      if (tables[k - 1] != s) {
        to_fill.push(k - 1);
      }
    } else if (a[i] == 'A') {
      bool can_push = true;

      if (to_fill.empty()) {
        if (k == x) {
          continue;
        }
        to_fill.push(k++);
        can_push = false;
      }
      int32_t ind_of_table = to_fill.front();

      tables[ind_of_table]++;

      if (can_push) {
        pos.push(ind_of_table);
      }

      if (tables[ind_of_table] == s) {
        to_fill.pop();
      }
    } else {
      if (to_fill.empty()) {
        if (!pos.empty()) {
          if (k == x || s < 2) {
            continue;
          }
          int32_t pos_of_a = pos.front();
          pos.pop();

          tables[pos_of_a]--;
          if (tables[pos_of_a] == s - 1) {
            to_fill.push(pos_of_a);
          }
          tables[k++] = 2;

          if (tables[k - 1] != s) {
            to_fill.push(k - 1);
          }
        }
      } else {
        int32_t ind_of_table = to_fill.front();

        tables[ind_of_table]++;

        if (tables[ind_of_table] == s) {
          to_fill.pop();
        }
      }
    }
  }
  int64_t ans = 0;
  for (int32_t i = 0; i < x; i++) {
    ans += tables[i];
  }
  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> n >> x >> s;
    cin >> a;

    solve();
  }

  return 0;
}
