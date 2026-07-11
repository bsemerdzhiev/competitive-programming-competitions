#include <array>
#include <bits/stdc++.h>
#include <string>

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
  vector<int32_t> vv(10, 0);
  for (auto x : a) {
    vv[x - '0']++;
  }

  for (int32_t i{1}; i < (int32_t(9e5)); i++) {
    int32_t cur_sum = i;
    vector<int32_t> needed(10, 0);
    string ans_s = "";

    while (true) {
      string sum_to_s = to_string(cur_sum);
      ans_s += sum_to_s;
      int32_t new_sum = 0;

      for (auto x : sum_to_s) {
        new_sum += x - '0';
        needed[x - '0']++;
      }
      if (cur_sum <= 9) {
        break;
      }
      cur_sum = new_sum;
    }

    int32_t rem_sum = 0;
    bool possible = true;
    for (int32_t z{0}; z < 10; z++) {
      if (needed[z] > vv[z]) {
        possible = false;
        break;
      }
      rem_sum += z * (vv[z] - needed[z]);
    }
    // cout << rem_sum << "\n";

    if (possible && rem_sum == i) {
      for (int32_t z{9}; z >= 0; z--) {
        for (int32_t j{0}; j < vv[z] - needed[z]; j++) {
          cout << z;
        }
      }
      cout << ans_s << "\n";
      return;
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
