#include <bits/stdc++.h>
#include <string>
#include <unordered_map>

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

string a;

void solve() {
  if (a.length() == 1) {
    cout << a << "\n";
    return;
  }
  vector<int32_t> cnt(10, 0);

  int32_t sum = 0;
  for (auto x : a) {
    cnt[x - '0']++;
    sum += x - '0';
  }

  vector<int32_t> taken(10, 0);

  struct Element {
    std::array<int32_t, 10> cnt;
    int32_t max_ch;
    int32_t br;
    int32_t cur_sum;
  };

  queue<Element> qq;

  qq.push({});

  vector<int32_t> needed_cnt(10, 0);
  while (!qq.empty()) {
    auto x = qq.front();
    qq.pop();

    int32_t cur_sum = sum - x.cur_sum;
    for (int32_t i{0}; i < 10; i++) {
      needed_cnt[i] = 0;
    }

    string fin_ans = "";
    while (true) {
      string sum_to_s = to_string(cur_sum);
      fin_ans += sum_to_s;
      int32_t new_sum = 0;

      for (auto x : sum_to_s) {
        new_sum += x - '0';
        needed_cnt[x - '0']++;
      }
      if (cur_sum < 10) {
        break;
      }
      cur_sum = new_sum;
    }

    bool possible = true;
    for (int32_t i{0}; i < 10; i++) {
      if (needed_cnt[i] != x.cnt[i]) {
        possible = false;
      }
    }

    if (possible) {
      for (int32_t i{9}; i >= 0; i--) {
        while (cnt[i] - x.cnt[i] > 0) {
          cout << i;

          cnt[i]--;
        }
      }
      cout << fin_ans << "\n";
      return;
    }

    if (x.br == 11) {
      continue;
    }
    std::array<int32_t, 10> new_cnt = x.cnt;

    for (int32_t i{x.max_ch}; i < 10; i++) {
      if (cnt[i] >= new_cnt[i] + 1) {
        new_cnt[i]++;
        qq.push({new_cnt, i, x.br + 1, x.cur_sum + i});
        new_cnt[i]--;
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> a;

    solve();
  }

  return 0;
}
