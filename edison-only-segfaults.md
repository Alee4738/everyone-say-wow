# Segfaults Happening Only On the Edison

On the edison, I built the mraa code (using cmake) and used it in a very basic program that just links to the library; it doesn't even use the library. Still, it crashes in some libmraa.so.2 function.

## gdb output

gdb is a debugger.

```bash
root@Wow_Edison:src$ gdb ../dist/wow 
GNU gdb (GDB) 7.7.1
...
Reading symbols from ../dist/wow...done.
(gdb) r
Starting program: /home/root/everyone-say-wow/dist/wow 
warning: Could not load shared library symbols for linux-gate.so.1.
Do you need "set solib-search-path" or "set sysroot"?
warning: File "/lib/libthread_db-1.0.so" auto-loading has been declined by your `auto-load safe-path` set to "$debugdir:$datadir/auto-load".
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
```

## ldd output

ldd shows the dynamic libraries linked to an executable and where they're located.

root@Wow_Edison:src$ ldd ../dist/wow 
        linux-gate.so.1 (0xb7763000)
        libmraa.so.2 => /home/root/everyone-say-wow/lib/mraa/build/src/libmraa.so.2 (0xb771a000)
        libc.so.6 => /lib/libc.so.6 (0x4b740000)
        libpthread.so.0 => /lib/libpthread.so.0 (0x4b8a9000)
        librt.so.1 => /lib/librt.so.1 (0x4b92f000)
        /lib/ld-linux.so.2 (0x4b713000)

Turns out the top and bottom libraries are special. I think they are actually kernel-exported libraries that expose system calls, so I probably don't have to worry about them.
Source: https://stackoverflow.com/questions/19981862/what-are-ld-linux-so-2-and-linux-gate-so-1

## Thoughts

- The same code works on my PC (it doesn't run into a segfault). This means the build on the edison architecture specifically is probably incorrect.
- This code was indeed running before. I must've somehow corrupted my system. Maybe I should reset the entire thing to get back to a fresh state.

Options
- Curr: Reset/reflash the edison, hope the problem goes away
  - just reflashed the edison and set it up
  - next step: cmake
- Figure out which part of the mraa library code is causing a segfault. Fix it and rebuild
- Give up
