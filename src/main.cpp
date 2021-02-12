#include <stdio.h>
#include <iostream>

#include "../lib/mraa/api/mraa.hpp"

using namespace mraa;

int main()
{
  Result initResult = init();
  std::cout << "init() result: " << initResult << std::endl;

  std::string platformName = getPlatformName();
  std::cout << "hello mraa" << std::endl
            << " Version: " << getVersion() << std::endl
            << " Running on " << platformName << std::endl;

  unsigned int pinCount = getPinCount();
  std::cout << "Pin count: " << pinCount << std::endl;

  // for (int i = 0; i < 10; i++)
  // {
  //   try
  //   {
  //     Led led = new Led(i);
  //     int maxBrightness = led.readMaxBrightness();
  //     std::cout << "Led " << i << " max brightness: " << maxBrightness << std::endl;
  //   }
  //   catch (std::invalid_argument)
  //   {
  //     std::cerr << "Led index " << i << " invalid" << std::endl;
  //   }
  // }

  mraa_deinit();
  return MRAA_SUCCESS;
}
