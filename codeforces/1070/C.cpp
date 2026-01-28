#include <algorithm>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <inttypes.h>
#include <vector>

#define MAXN int(2e5 + 5)

int32_t n;
int32_t a[MAXN];

void solve() {
  std::vector<int32_t> by_parity[2];
  by_parity[0] = std::vector<int32_t>();
  by_parity[1] = std::vector<int32_t>();

  for (size_t i = 0; i < n; i++) {
    by_parity[a[i] % 2].push_back(a[i]);
  }
  for (size_t i = 0; i < 2; i++) {
    std::sort(by_parity[i].begin(), by_parity[i].end(),
              std::greater<int32_t>());
  }
  std::vector<int64_t> answers(n + 1, 0);

  // handle k = 1
  if (by_parity[0].empty()) {
    for (size_t i = 1; i <= n; i += 2) {
      answers[i] = by_parity[1][0];
    }
  } else if (by_parity[1].empty()) {
    // everything is only 0
  } else {
    int64_t running_sum = by_parity[1][0];
    answers[1] = running_sum;

    running_sum += by_parity[0][0];
    answers[2] = running_sum;

    size_t next_ind = 3;

    // keep adding even numbers
    for (size_t i = 1; i < by_parity[0].size(); i++) {
      running_sum += by_parity[0][i];
      answers[next_ind++] = running_sum;
    }

    int32_t smallest_even_number = by_parity[0].back();
    for (size_t i = 1; i < by_parity[1].size(); i++) {
      if (i % 2 == 1) {
        answers[next_ind++] = running_sum - smallest_even_number;
      } else {
        answers[next_ind++] = running_sum;
      }
    }
    if (by_parity[1].size() % 2 == 0) {
      answers[n] = 0;
    }
  }

  for (size_t i = 1; i <= n; i++) {
    printf("%" PRId64 " ", answers[i]);
  }
  printf("\n");
}

int main() {
  int32_t t;
  scanf("%d", &t);

  while (t--) {
    scanf("%d", &n);
    for (size_t i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }

    solve();
  }

  return 0;
}
