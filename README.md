Goal: Make a button that says "errione-say-wow" (everyone say wow)

Doing
- I can make a grove LED light up
  - I did make install on the edison, said it installed libraries to /usr/local/include/ (mraa.hpp, mraa.h, etc.) and /usr/local/lib/ (libmraa.so, libmraa.so.2, libmraa.so.2.2.0)
    - But now I'm having problems with linking, something about C code mixing with C++, extern C, ifdef __cplusplus in the header file, and it's still not working
    - If I can't find a solution, then I have to fall back to C instead of C++
    - I could try recreating the problem on the edison with a smaller example (.h, .c, and .cpp incling the .h)
  - Problems with segfaults and linked libraries (I think)
    - Maybe I should just use sudo and install the mraa library in /usr/local/include or wherever the default location is
root@Wow_Edison:src$ gdb ../dist/wow 
GNU gdb (GDB) 7.7.1
...
Reading symbols from ../dist/wow...done.
(gdb) r
Starting program: /home/root/everyone-say-wow/dist/wow 
warning: Could not load shared library symbols for linux-gate.so.1.
Do you need "set solib-search-path" or "set sysroot"?
warning: File "/lib/libthread_db-1.0.so" auto-loading has been declined by your `auto-load safe-path' set to "$debugdir:$datadir/auto-load".
To enable execution of this file add
        add-auto-load-safe-path /lib/libthread_db-1.0.so
line to your configuration file "/home/root/.gdbinit".
To completely disable this security protection add
        set auto-load safe-path /
line to your configuration file "/home/root/.gdbinit".
For more information about this security protection see the
"Auto-loading safe path" section in the GDB manual.  E.g., run from the shell:
        info "(gdb)Auto-loading safe path"
warning: Unable to find libthread_db matching inferior's thread library, thread debugging will not be available.

Program received signal SIGSEGV, Segmentation fault.
0xb7fc1d03 in mraa_gpio_read_dir ()
   from /home/root/everyone-say-wow/lib/mraa/build/src/libmraa.so.2

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
- I made changes to lib/mraa. I need to figure out how to commit them
  - https://git-scm.com/book/en/v2/Git-Tools-Submodules
- (skipped) I can make the on-board LED light up
  - It says that there are no LEDs, so skip this
- Making my own library and making sure I can link to it correctly
  - https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/create-libraries/index
  - Make a static library, use on PC, use on edison
  - Make a shared library, use on PC, use on edison

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
  
  