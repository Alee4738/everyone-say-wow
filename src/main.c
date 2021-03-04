#include <stdio.h>

#include "../lib/mraa/api/mraa.h"

int main()
{
  // const char *board_name = mraa_get_platform_name();
  // fprintf(stdout, "hello mraa\n Version: %s\n Running on %s\n", mraa_get_version(), board_name);

  // mraa_deinit();
  return 0;

  // return MRAA_SUCCESS;
  // Result initResult = init();
  // std::cout << "init() result: " << initResult << std::endl;

  // std::string platformName = getPlatformName();
  // std::cout << "hello mraa" << std::endl
  //           << " Version: " << getPlatformVersion() << std::endl
  //           << " Running on " << platformName << std::endl;

  // unsigned int pinCount = getPinCount();
  // std::cout << "Pin count: " << pinCount << std::endl;

  // const int START = 0;
  // const int END = 10;
  // for (int i = START; i < END; i++)
  // {
  //   try
  //   {
  //     Led led = new Led(i);
  //     int maxBrightness = led.readMaxBrightness();
  //     std::cout << "Led " << i << " max brightness: " << maxBrightness << std::endl;
  //   }
  //   catch (std::invalid_argument)
  //   {
  //   }
  // }

  // mraa_deinit();
  // return MRAA_SUCCESS;
  // return 0;
}
