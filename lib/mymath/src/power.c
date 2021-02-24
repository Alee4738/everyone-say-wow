#include "./power.h"
#include "./multiply.h"

int square(int num)
{
  return multiply(num, num);
}

int cube(int num)
{
  return multiply(square(num), num);
}
