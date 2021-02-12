Goal: Make a button that says "errione-say-wow" (everyone say wow)

Doing
- I can make the on-board LED light up

Todo

- I can play a single tone on load
- I can detect the button press
- I can output a single tone by pressing a button
- I can output a custom tone
- I can save a custom tone to the edison

Done

- Record erryonesaywow mp3
- Pick a mp3: winner: c1-wk4-wrapup.mp3
- I can turn on the intel edison
  - I connect USB-to-micro-usb cable from computer to edison (port J16)
  - I turn the switch SW1 towards the micro usb port (away from USB 2.0)
  - Press and hold power button SW1UI2 for 3 seconds
  - See DS1 and DS2 flash. DS2 stays on mostly
- I can connect to the edison with my computer
  - Connect USB-to-micro-usb cable from computer to edison (port J3)
  - In terminal
    $ lsusb | grep UART
    Bus 003 Device 005: ID 413c:1010 Dell Computer Corp. FT232R USB UART
    Bus 003 Device 012: ID 0403:6001 Future Technology Devices International, Ltd FT232 Serial (UART) IC
  - Somehow, the J3 port corresponds to both of these results
- (failed) Use Arduino IDE
  - Intel Edison is a retired board, don't expect much support
  - Ran into some errors when installing board-specific software
    - Intel i686 post-install script failed (warning about absolute paths, then SDK something failed
    - When I ignored the error and went on, uploading the example code resulted in avrdude errors about trying to sync up (something_getasync)
- I can log in to the edison
  - Forgot the password, so I needed to flash the edison, which was painful. See [how I flashed the edison](./flash-edison.md)
- I can transfer files to the edison
  - scp works, but it requires me to enter password each time, which is annoying
    - Make edison trust my computer (add public ssh key)
- I can get basic code running on the edison
  - print hello world
  - establish watch to do build on save, only continues with build if previous step succeeded, but still always watches
- I can compile mraa code on my machine (not the edison)
  - Learn basic cmake
- I can compile mraa code on the edison
  - cmake said that architecture (i686) was not supported. stupid solution that worked: change CMakeLists.txt to allow it (changed "i586" to "i686")
  - my hello world built and ran fine (for now)
- migrate from c to cpp

Resources

- [Flash Intel Edison, Troubleshooting was helpful](https://openaps.readthedocs.io/en/latest/docs/Resources/Edison-Flashing/all-computers-flash.html)
- [Edison system tutorials](https://lasr.cs.ucla.edu/classes/edison_tutorials/)
- [Spec](http://web.cs.ucla.edu/classes/winter17/cs111/labs/Project4.html)
- [Class schedule & labs](http://web.cs.ucla.edu/classes/winter17/cs111/syllabus.html)
- [flashall.sh and supporting materials](https://downloadcenter.intel.com/download/27074/Intel-Edison-Yocto-Poky-image)
- [How to use dfu for u-boot](https://github.com/u-boot/u-boot/blob/master/doc/README.dfu)
- [u-boot manual, didn't read](https://www.digi.com/resources/documentation/digidocs/PDFs/90000852.pdf)
- [Intel Phone Flash Tool, didn't work for me](https://androidmtk.com/download-intel-phone-flash-tool)
- [Building MRAA, learned cmake was necessary](https://github.com/eclipse/mraa/blob/master/docs/building.md)
- [CMake Tutorial, went up to step 2](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)


Problems

- Compute Module not connected correctly
  - needed to snap in
  - observed: no blinking lights at all. Tried plugging in through 5V and then putting in the module, then saw blinking lights
- Could not verify that I could connect
  - failed to use Arduino IDE - Intel Edison was too outdated
  - lsusb - at least I could detect it from PC
  - read edison tutorials and found out to do: screen /dev/ttyUSB0 115200
  - Cannot access /dev/ttyUSB0 for R/W Permission denied
  - Added myself to the dialout group, which was the group of the ttyUSB0, and logout
  - Solution: added self to dialout group
- Not enough power through USB interface
  - used 5V instead of usb power
  - observed: was able to connect to it and type a few letters at the boot> prompt, then it would reboot
- Could not log in because I forgot my password
  - observed: a prompt like AndrewLee_edison login
  - was not able to remember my credentials from years ago
  - solution: flash the device to reset to factory settings
- Don't know how to use dfu on intel edison
  - installed dfu-utils on home computer
  - ran ./flashall.sh, failed to detect that I was rebooting the device
- [Flashing the edison](./flash-edison.md)
- Writing code to tell the edison hardware to do things
  - How do I get information about the board?
    - Using the mraa library
  - How do I get the mraa library?
    - You need to download the source code from github and build it
  - How do I build it?
    - use cmake
  - Ok I learned about cmake basics
  - cmake on my machine worked, but make didn't work. How do I link mraa library?
    - export LIBRARY_PATH="/home/andrew/projects-practice/everyone-say-wow/lib/mraa/build/src"
    - gcc uses that to find libraries
  - cmake on edison results in error saying architecture (i686) not supported
    - stupid solution that worked: change CMakeLists.txt to allow it (changed "i586" to "i686")
  - cmake examples result in segfaults
    - don't care about those. At least my hello world code built and worked
  
  