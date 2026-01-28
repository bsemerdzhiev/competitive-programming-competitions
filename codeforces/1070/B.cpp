#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stdint.h>

#define MAXN int(2e5 + 5)

int32_t n;
char str[MAXN * 2];

int main() {
  int32_t t;
  scanf("%d", &t);

  while (t--) {
    scanf("%d", &n);
    scanf("%s", str);

    for (int i = n; i < 2 * n; i++) {
      str[i] = str[i - n];
    }

    int32_t largest_hole = 0;
    int32_t current_hole = 0;
    for (size_t i = 0; i < 2 * n; i++) {
      if (str[i] == '0') {
        current_hole += 1;
      } else {
        current_hole = 0;
      }
      largest_hole = std::max(current_hole, largest_hole);
    }
    printf("%d\n", largest_hole);
  }

  return 0;
}
