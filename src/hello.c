#include <stdio.h>
#include "../lib/mymath/src/power.h"

int main()
{
  printf("hello.c\n");
  int num = 5;
  int result = cube(num);
  printf("cube of %i is %i\n", num, result);
  return 0;
}
