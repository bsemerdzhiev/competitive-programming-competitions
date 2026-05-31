#include <bits/stdc++.h>
#include <deque>
#include <semaphore>
#include <stack>

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

int32_t a[3];

void solve() {
  char l[3] = {'R', 'G', 'B'};

  for (int32_t i = 0; i < 3; i++) {
    for (int32_t j = i + 1; j < 3; j++) {
      if (a[j] > a[i]) {
        swap(a[i], a[j]);
        swap(l[i], l[j]);
      }
    }
  }

  deque<char> ans;

  while (a[0]) {
    ans.push_back(l[0]);
    a[0]--;

    if (a[2]) {
      ans.push_back(l[2]);
      a[2]--;
    } else if (a[1]) {
      ans.push_back(l[1]);
      a[1]--;
    } else {
      break;
    }
  }

  if (ans.back() == l[0] && a[1]) {
    ans.push_back(l[1]);
    a[1]--;
  }

  deque<char> to_add;
  if (a[1]) {
    to_add.push_front(l[1]);
    // ans.push_front(l[1]);
    a[1]--;
  }

  int32_t st_ind = 1;

  while (a[1]) {
    if (to_add.front() != l[1]) {
      to_add.push_front(l[1]);
      a[1]--;
      continue;
    }

    if (st_ind >= ans.size() || ans[st_ind] != l[2]) {
      break;
    }

    ans[st_ind] = l[1];
    a[1]--;

    to_add.push_front(l[2]);

    st_ind += 2;
  }

  for (auto x : to_add) {

    cout << x;
  }
  for (auto x : ans) {
    cout << x;
  }
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  size_t t;
  cin >> t;

  while (t--) {
    cin >> a[0] >> a[1] >> a[2];
    solve();
  }

  return 0;
}
