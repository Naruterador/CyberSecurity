#include <stdio.h>
int add(int x, int y) {

  int sum = 0;
  sum = x + y;
  return sum;
}

int main() {
  int a = 1;
  int b = 2;
  add(a, b);

  return 0;
}
