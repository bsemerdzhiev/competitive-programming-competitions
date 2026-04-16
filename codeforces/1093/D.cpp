#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <format>

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

bool ask_query(int32_t l, int32_t r, vector<int32_t> &ans_v) {
  int32_t bonus_added = 0;
  for (auto x : ans_v) {
    if (x >= l && x <= r) {
      bonus_added++;
    }
  }

  cout << format("? {} ", n - (r - l + 1) + bonus_added);

  for (int32_t i = 1; i <= n; i++) {
    bool to_add = false;
    for (auto x : ans_v) {
      if (x == i) {
        to_add = true;
        break;
      }
    }
    if (to_add || i < l || i > r) {
      cout << i << " ";
    }
  }
  cout << "\n";
  cout.flush();

  int32_t ans;
  cin >> ans;

  if (ans == -1) {
    exit(1);
  }

  return (n + ans - (r - l + 1 - bonus_added)) % 2 == 0;
}

bool rec(int32_t l, int32_t r, vector<int32_t> &ans, bool skip_ask) {
  bool has_in_interval = skip_ask ? true : ask_query(l, r, ans);
  if (!has_in_interval) {
    return false;
  }

  if (l == r) {
    ans.push_back(l);
    return true;
  }
  int32_t middle = (l + r) >> 1;

  int32_t size_before = ans.size();
  if (rec(l, middle, ans, false)) {
    return true;
  }
  if (rec(middle + 1, r, ans, size_before == ans.size())) {
    return true;
  }
  return false;
}

void solve() {
  vector<int32_t> ans;
  for (int32_t i = 0; i < 3; i++) {
    rec(1, n, ans, true);
  }

  cout << "! ";
  for (auto x : ans) {
    cout << x << " ";
  }
  cout << "\n";
  cout.flush();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> n;
    if (n == -1) {
      return 0;
    }

    n <<= 1;
    n += 1;

    solve();
  }

  return 0;
}
