#include <iostream>

using namespace std;

const int32_t MOD = 998244353;
const int32_t MAXN = 2e5 + 5;

namespace MO {
int32_t add(int64_t x, int64_t y) { return (x + y + MOD) % MOD; }
int32_t mul(int64_t x, int64_t y) { return (x * y) % MOD; }
}; // namespace MO

int32_t x, y;

void update_answer(int &ans_p, int &ans_q, int new_p, int new_q) {
  int32_t t_ans = abs(x - ans_p) + abs(y - ans_q);

  int32_t new_ans = abs(x - new_p) + abs(y - new_q);

  if (new_ans < t_ans) {
    ans_p = new_p;
    ans_q = new_q;
  }
}

void solve() {
  // first bigger

  int32_t new_p = 0, new_q = 0;

  bool two_ones = false;
  // both are <=
  for (int32_t i = 30; i >= 0; i--) {
    int32_t bit1 = (x & (1 << i)) > 0;
    int32_t bit2 = (y & (1 << i)) > 0;

    // both are 0
    if (bit1 == 0 && bit2 == 0) {
      if (two_ones) {
        new_q ^= (1 << i);
      }
    } else if (bit1 == 1 && bit2 == 0) {
      new_p ^= (1 << i);
    } else if (bit1 == 0 && bit2 == 1) {
      new_q ^= (1 << i);
    } else if (bit1 == 1 && bit2 == 1) {
      new_p ^= (1 << i);
      two_ones = 1;
    }
  }

  // cout << new_p << " " << new_q;
  //  first is bigger

  for (int32_t i = 0; i < 31; i++) {
    if ((x & (1 << i)) == 0) {
      int32_t new_x = ((x >> i) << i) | (1 << i);

      int32_t new_y = y & (~new_x);

      update_answer(new_p, new_q, new_x, new_y);
    }
    if ((y & (1 << i)) == 0) {
      int32_t new_y = ((y >> i) << i) | (1 << i);

      int32_t new_x = x & (~new_y);

      update_answer(new_p, new_q, new_x, new_y);
    }
  }

  cout << new_p << " " << new_q << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int32_t t;
  cin >> t;

  while (t--) {
    cin >> x >> y;
    solve();
  }

  return 0;
}
