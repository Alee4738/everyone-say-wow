#include <iostream>
#include "../lib/mymath/src/power.h"

using namespace std;

int main()
{
  cout << "world.cpp" << endl;
  int num = 5;
  int result = cube(num);
  cout << "cube of " << num << " is " << result << endl;
  return 0;
}