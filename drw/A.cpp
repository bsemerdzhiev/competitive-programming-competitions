#include <bits/stdc++.h>

using namespace std;

int32_t a[3];

bool check_possible(int32_t n_a, int32_t n_b, int32_t n_c, int32_t prev_c,
                    int32_t prev_cnt) {
  int32_t b[3] = {n_a, n_b, n_c};

  if (b[0] > max(b[1], b[2])) {
    if (prev_c == 0) {
      b[0] -= 2 - prev_cnt;
    } else {
      b[0] -= 2;
    }
    return (b[0] + 1) / 2 <= b[1] + b[2];
  } else if (b[1] > max(b[0], b[2])) {
    if (prev_c == 1) {
      b[1] -= 2 - prev_cnt;
    } else {
      b[1] -= 2;
    }
    return (b[1] + 1) / 2 <= b[0] + b[2];
  } else if (b[2] > max(b[0], b[1])) {
    if (prev_c == 2) {
      b[2] -= 2 - prev_cnt;
    } else {
      b[2] -= 2;
    }
    return (b[2] + 1) / 2 <= b[0] + b[1];
  }
  return true;
}

void solve() {
  int32_t prev_choice = -1;
  int32_t prev_cnt = 0;

  int32_t n_a[3];
  vector<char> ans;

  int32_t n = a[0] + a[1] + a[2];
  for (int32_t i{0}; i < n; i++) {
    for (int32_t j{0}; j < 3; j++) {
      for (int32_t z{0}; z < 3; z++) {
        n_a[z] = a[z];
      }
      n_a[j]--;

      if (a[j]) {
        if (prev_choice == j) {
          if (prev_cnt != 2 && check_possible(n_a[0], n_a[1], n_a[2],
                                              prev_choice, prev_cnt + 1)) {
            prev_cnt++;
            ans.push_back('a' + j);
            a[j]--;
            break;
          }
        } else if (check_possible(n_a[0], n_a[1], n_a[2], j, 1)) {
          prev_choice = j;
          prev_cnt = 1;

          ans.push_back('a' + j);
          a[j]--;
          break;
        }
      }
    }
  }
  for (auto x : ans) {
    cout << x;
  }
  cout << "\n";
}

int32_t main() {
  std::cin >> a[0] >> a[1] >> a[2];

  solve();

  return 0;
}
