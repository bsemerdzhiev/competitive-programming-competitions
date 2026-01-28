#include <algorithm>
#include <cstdio>
#include <stdint.h>

#define MAXN 105

int32_t n;
int32_t a[MAXN];

int main() {
  int32_t t;

  scanf("%d\n", &t);

  while (t--) {

    scanf("%d", &n);

    for (size_t i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }

    int32_t ans = n;

    int32_t max_number = 0;
    for (size_t i = 0; i < n; i++) {
      if (max_number <= a[i]) {
        ans--;
      }
      max_number = std::max(max_number, a[i]);
    }

    printf("%d\n", ans);
  }
  return 0;
}
