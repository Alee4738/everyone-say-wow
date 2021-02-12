# Flashing the Edison

This shows how I flashed the edison.

## Why

I forgot the root password that I set for the edison, so I needed to flash it with the factory image.

## How To Do It

The edison uses the U-Boot bootloader, which provides a basic shell to interact with.

1. Plug in everything: both micro USBs into PC, barrel connector for power
1. Download image from https://downloadcenter.intel.com/download/27074/Intel-Edison-Yocto-Poky-image
   1. I got iot-devkit-prof-dev-image-edison-20160606.zip
   1. Unzip
   1. I am on Linux, so ./flashall.sh was the relevant script for me

On edison,
boot> run do_flashall

On PC,
$ ./flashall.sh

flashall.sh should detect the edison and begin to flash U-boot (the bootloader) and IFWI (whatever that is). After that, the flashall.sh script will end, and the edison will hang with something like "Ctrl+C to exit ...". Once flashall.sh ends, it's ok to press Ctrl+C for the edison and reset it.


On edison,
// reset it using the physical reset button, or the "reset" command
boot > run do_force_flash_os

On PC,
$ ./flashall.sh

That will run and restart the edison multiple times, output is at the bottom, and you should be able to log in with root.

On edison,
```
Poky (Yocto Project Reference Distro) 1.7.3 edison ttyMFD2

edison login: root
root@edison:~# echo "hello world I am logged in"
hello world I am logged in
```

## How I Figured It Out

- I was recommended to flash the device by the UCLA EE edison setup guide
- Found online that intel provided support for this (the images, not really the instructions anymore), so I downloaded the image from the url mentioned above
- ./flashall.sh failed if dfu-utils is not installed, so I assumed dfu-util did most of the legwork.
- [man dfu-util](http://manpages.org/dfu-util) says it has something to do with "Device Firmware Upgrade" and that DFU is a USB protocol
- dfu-util also mentioned that it was "host" mentioned in the DFU protocol, so I had a hunch that the edison needed to be in "device mode" according to the DFU protocol
- Found online that I can stop "autoboot" by pressing Enter quickly multiple times when the edison is booting, which brings me to the U-boot shell
  - Found that people ran commands in the bootloader like `run do_force_flash_os`, `run do_flash_os`, but those didn't work for me
- Found by playing in the u-boot shell that there is the dfu command, but couldn't figure out the syntax (how to specify the USB_controller, interface, device)
- Gave up and tried to use Windows because there was an Intel Phone Flash Tool that I couldn't use on Linux
  - Found that the computer could connect serially to the edison via the UART micro usb port, but file explorer didn't detect the edison until the second micro usb was plugged in. I thought that second one was only for power, but whatever
  - The tool tried to flash and it got up to 21% all the time, but the bootloader wouldn't wait for it. It just booted up the Linux system as usual
  - Gave up on GUI tools and decided that I needed to learn about the nuts and bolts
- Found the [U-boot reference manual](https://www.digi.com/resources/documentation/digidocs/PDFs/90000852.pdf), but didn't read it
- I read the [u-boot docs for dfu](https://github.com/u-boot/u-boot/blob/master/doc/README.dfu) to figure out the dfu syntax, but couldn't
- In the u-boot docs for dfu, they mention "dfu_alt_info", and I guessed that it was an environment variable; `printenv` confirmed this
- In there, I saw the commands that people online recommended. Ones that stuck out: `run do_force_flash_os`, `run do_flashall`, so I decided to try them again, this time with both micro USBs plugged in, and it worked


## Output From PC

$ ./flashall.sh 
Using U-Boot target: edison-blankcdc
Now waiting for dfu device 8087:0a99
Please plug and reboot the board
Flashing IFWI
Download    [=========================] 100%      4194304 bytes
Download    [=========================] 100%      4194304 bytes
Flashing U-Boot
Download    [=========================] 100%       237568 bytes
Flashing U-Boot Environment
Download    [=========================] 100%        65536 bytes
Flashing U-Boot Environment Backup
Download    [=========================] 100%        65536 bytes
Rebooting to apply partition changes
Now waiting for dfu device 8087:0a99
Flashing boot partition (kernel)
Download    [=========================] 100%      6144000 bytes
Flashing rootfs, (it can take up to 5 minutes... Please be patient)
Download    [=========================] 100%   1373159424 bytes
Rebooting
U-boot & Kernel System Flash Success...
Your board needs to reboot to complete the flashing procedure, please do not unplug it for 2 minutes.


## Output From Edison

boot > run do_force_flash_os
Saving Environment to MMC...
Writing to MMC(0)... done
GADGET DRIVER: usb_dnl_dfu
#
DFU complete CRC32: 0x3756edb6
DOWNLOAD ... OK
Ctrl+C to exit ...
#
DFU complete CRC32: 0x3756edb6
DOWNLOAD ... OK
Ctrl+C to exit ...
#
DFU complete CRC32: 0xfe334eda
DOWNLOAD ... OK
Ctrl+C to exit ...
#
DFU complete CRC32: 0xe511e42b
DOWNLOAD ... OK
Ctrl+C to exit ...
#
DFU complete CRC32: 0xe511e42b
DOWNLOAD ... OK
Ctrl+C to exit ...
resetting ...


******************************
PSH KERNEL VERSION: b0182b2b
                WR: 20104000
******************************

SCU IPC: 0x800000d0  0xfffce92c

PSH miaHOB version: TNG.B0.VVBD.0000000c

microkernel built 11:24:08 Feb  5 2015

******* PSH loader *******
PCM page cache size = 192 KB
Cache Constraint = 0 Pages
Arming IPC driver ..
Adding page store pool ..
PagestoreAddr(IMR Start Address) = 0x04899000
pageStoreSize(IMR Size)          = 0x00080000

*** Ready to receive application ***


U-Boot 2014.04 (Jun 06 2016 - 14:40:07)

       Watchdog enabled
DRAM:  980.6 MiB
MMC:   tangier_sdhci: 0
In:    serial
Out:   serial
Err:   serial
Writing to redundant MMC(0)... done
Writing to MMC(0)... done
Hit any key to stop autoboot:  0
Target:blank
Partitioning using GPT
Writing GPT: success!
Saving Environment to MMC...
Writing to redundant MMC(0)... done
Flashing already done...
GADGET DRIVER: usb_dnl_dfu
#
DFU complete CRC32: 0xb0625c80
DOWNLOAD ... OK
Ctrl+C to exit ...
####################################################################################################
################################################################
DFU complete CRC32: 0x5043640d
DOWNLOAD ... OK
Ctrl+C to exit ...
resetting ...


******************************
PSH KERNEL VERSION: b0182b2b
                WR: 20104000
******************************

SCU IPC: 0x800000d0  0xfffce92c

PSH miaHOB version: TNG.B0.VVBD.0000000c

microkernel built 11:24:08 Feb  5 2015

******* PSH loader *******
PCM page cache size = 192 KB
Cache Constraint = 0 Pages
Arming IPC driver ..
Adding page store pool ..
PagestoreAddr(IMR Start Address) = 0x04899000
pageStoreSize(IMR Size)          = 0x00080000

*** Ready to receive application ***


U-Boot 2014.04 (Jun 06 2016 - 14:40:07)

       Watchdog enabled
DRAM:  980.6 MiB
MMC:   tangier_sdhci: 0
In:    serial
Out:   serial
Err:   serial
Hit any key to stop autoboot:  0
Target:blank
Partitioning already done...
Flashing already done...
GADGET DRIVER: usb_dnl_dfu
reading vmlinuz
5461344 bytes read in 135 ms (38.6 MiB/s)
Valid Boot Flag
Setup Size = 0x00003c00
Magic signature found
Using boot protocol version 2.0c
Linux kernel version 3.10.98-poky-edison+ (neck@flax) #1 SMP PREEMPT Mon Jun 6 14:32:08 PDT 2016
Building boot_params at 0x00090000
Loading bzImage at address 00100000 (5445984 bytes)
Magic signature found
Kernel command line: "rootwait root=PARTUUID=012b3303-34ac-284d-99b4-34e03a2335f4 rootfstype=ext4 co
nsole=ttyMFD2 earlyprintk=ttyMFD2,keep loglevel=4 g_multi.ethernet_config=cdc systemd.unit=multi-use
r.target hardware_id=00 g_multi.iSerialNumber=a0e2675428b7f50ad0980ebc460450b4 g_multi.dev_addr=02:0
0:86:04:50:b4 platform_mrfld_audio.audio_codec=dummy"

Starting kernel ...

[    1.606680] snd_soc_sst_platform: Enter:sst_soc_probe
[    2.090782] pmic_ccsm pmic_ccsm: Error reading battery profile from battid frmwrk
[    2.099609] pmic_ccsm pmic_ccsm: Battery Over heat exception
[    2.101283] pmic_ccsm pmic_ccsm: Battery0 temperature outside boundary

Welcome to Linux!

[    2.709634] systemd[1]: [/lib/systemd/system/wyliodrin-hypervisor.service:3] Failed to add depend
ency on redis, ignoring: Invalid argument
[    2.723567] systemd[1]: [/lib/systemd/system/wyliodrin-server.service:3] Failed to add dependency
 on redis, ignoring: Invalid argument
         Expecting device dev-ttyMFD2.device...
[  OK  ] Reached target Remote File Systems.
         Expecting device dev-disk-by\x2dpartlabel-factory.device...
         Expecting device dev-disk-by\x2dpartlabel-rootfs.device...
         Expecting device dev-disk-by\x2dpartlabel-update.device...
         Expecting device dev-disk-by\x2dpartlabel-home.device...
         Expecting device sys-subsystem-net-devices-usb0.device...
[  OK  ] Reached target Paths.
[  OK  ] Reached target Swap.
[  OK  ] Created slice Root Slice.
[  OK  ] Listening on Delayed Shutdown Socket.
[  OK  ] Listening on /dev/initctl Compatibility Named Pipe.
[  OK  ] Listening on udev Control Socket.
[  OK  ] Listening on udev Kernel Socket.
[  OK  ] Created slice User and Session Slice.
[  OK  ] Listening on Journal Socket.
[  OK  ] Created slice System Slice.
         Starting Remount Root and Kernel File Systems...
         Starting Apply Kernel Variables...
         Starting Create list of required static device nodes...rrent kernel...
         Mounting Debug File System...
         Starting Load Kernel Modules...
         Mounting POSIX Message Queue File System...
         Starting udev Coldplug all Devices...
[  OK  ] Created slice system-serial\x2dgetty.slice.
[  OK  ] Created slice system-getty.slice.
         Starting Journal Service...
[  OK  ] Started Journal Service.
[  OK  ] Reached target Slices.
         Mounting Temporary Directory...
[  OK  ] Set up automount boot.automount.
[  OK  ] Mounted POSIX Message Queue File System.
[  OK  ] Mounted Debug File System.
[  OK  ] Mounted Temporary Directory.
[  OK  ] Started Remount Root and Kernel File Systems.
[  OK  ] Started Apply Kernel Variables.
[  OK  ] Started Create list of required static device nodes ...current kernel.
[  OK  ] Started Load Kernel Modules.
[  OK  ] Started udev Coldplug all Devices.
         Mounting FUSE Control File System...
         Mounting Configuration File System...
         Starting Create Static Device Nodes in /dev...
         Starting Load/Save Random Seed...
[  OK  ] Mounted Configuration File System.
[  OK  ] Mounted FUSE Control File System.
[  OK  ] Started Load/Save Random Seed.
[  OK  ] Started Create Static Device Nodes in /dev.
         Starting udev Kernel Device Manager...
[  OK  ] Reached target Local File Systems (Pre).
         Mounting /var/volatile...
[  OK  ] Started udev Kernel Device Manager.
[  OK  ] Mounted /var/volatile.
[  OK  ] Reached target Local File Systems.
         Starting Create Volatile Files and Directories...
         Starting Trigger Flushing of Journal to Persistent Storage...
[  OK  ] Started Create Volatile Files and Directories.
[  OK  ] Started Trigger Flushing of Journal to Persistent Storage.
[  OK  ] Created slice system-systemd\x2drfkill.slice.
         Starting Load/Save RF Kill Switch Status of rfkill2...
         Starting Load/Save RF Kill Switch Status of rfkill1...
         Starting Load/Save RF Kill Switch Status of rfkill0...
         Starting Network Time Synchronization...
         Starting Opkg first boot configure...
         Starting Update UTMP about System Boot/Shutdown...
[  OK  ] Started Load/Save RF Kill Switch Status of rfkill2.
[  OK  ] Started Load/Save RF Kill Switch Status of rfkill1.
[  OK  ] Started Load/Save RF Kill Switch Status of rfkill0.
[  OK  ] Started Network Time Synchronization.
[  OK  ] Found device /sys/subsystem/net/devices/usb0.
[  OK  ] Found device /dev/ttyMFD2.
[  OK  ] Found device /dev/disk/by-partlabel/factory.
[  OK  ] Started Update UTMP about System Boot/Shutdown.
[  OK  ] Found device /dev/disk/by-partlabel/rootfs.
[  OK  ] Found device /dev/disk/by-partlabel/home.
[  OK  ] Found device /dev/disk/by-partlabel/update.
[  OK  ] Started Opkg first boot configure.
         Mounting Mount for factory...
[  OK  ] Reached target System Initialization.
[  OK  ] Listening on RPCbind Server Activation Socket.
[  OK  ] Reached target Timers.
         Starting Restore Sound Card State...
         Starting Console System Startup Logging...
[  OK  ] Listening on D-Bus System Message Bus Socket.
[  OK  ] Mounted Mount for factory.
[  OK  ] Listening on sshd.socket.
[  OK  ] Started Console System Startup Logging.
[  OK  ] Reached target Sockets.
[  OK  ] Reached target Basic System.
         Starting Edison PWR button handler...
[  OK  ] Started Edison PWR button handler.
         Starting Edison sketch check service...
[  OK  ] Started Edison sketch check service.
         Starting Wyliodrin server...
         Starting Telephony service...
         Starting OpenSSH Key Generation...
         Starting Daemon to handle arduino sketches...
[  OK  ] Started Daemon to handle arduino sketches.
         Starting Daemon to reset sketches...
[  OK  ] Started Daemon to reset sketches.
         Starting Start or stop WiFI AP Mode in Edison...
[  OK  ] Started Start or stop WiFI AP Mode in Edison.
         Starting Wyliodrin hypervisor...
         Starting Daemon to load edison mcu app binary...
[  OK  ] Started Daemon to load edison mcu app binary.
Application available at (physical) address 0x04819000
        VRL mapped to 0xff217000
        App size = 11508 bytes

        App Authentication feature is disabled!
        Resetting IPC

*** Ready to receive application ***
         Starting Bluetooth rf kill event daemon...
[  OK  ] Started Bluetooth rf kill event daemon.
         Starting Login Service...
         Starting Cleanjournal service...
[  OK  ] Started Cleanjournal service.
         Starting Generate unique machine-id...
         Starting Crashlog service...
[  OK  ] Started Crashlog service.
         Starting Permit User Sessions...
         Starting Post install service...
         Starting Watchdog sample daemon...
[  OK  ] Started Watchdog sample daemon.
         Starting D-Bus System Message Bus...
[  OK  ] Started D-Bus System Message Bus.
[   10.895407] sh[243]: Starting Post Install (try: 0)
[  OK  ] Started Telephony service.
         Starting Network Service...
[  OK  ] Started Restore Sound Card State.
[  OK  ] Started Permit User Sessions.
[   11.257617] systemd-machine-id-setup[258]: Initializing machine ID from random generator.
[  OK  ] Started Network Service.
[   11.708983] systemctl[262]: rm '/etc/systemd/system/basic.target.wants/edison-machine-id.service'
[  OK  ] Started Generate unique machine-id.
[  OK  ] Started Login Service.
         Starting Bluetooth service...
         Starting Edison Arduino board LED Blinker...
[  OK  ] Started Edison Arduino board LED Blinker.
         Starting PulseAudio Sound System...
         Starting Network Name Resolution...
[  OK  ] Reached target Network.
         Starting Mosquitto - lightweight server implementati...SN protocols...
[   13.127336] sh[243]: Backup home/root contents of rootfs : Success
         Starting Zero-configuration networking...
[   13.267549] sh[243]: mke2fs 1.42.9 (28-Dec-2013)
         Starting Getty on tty1...
[  OK  ] Started Getty on tty1.
[  OK  ] Started Network Name Resolution.
[  OK  ] Started Mosquitto - lightweight server implementatio...T-SN protocols.
[  OK  ] Started Bluetooth service.
[  OK  ] Started Zero-configuration networking.
         Starting The Edison status and configuration service...
[  OK  ] Started The Edison status and configuration service.
         Starting Hostname Service...
[  OK  ] Created slice user-0.slice.
[  OK  ] Started Wyliodrin server.
[  OK  ] Started Hostname Service.
         Starting User Manager for UID 0...
[   14.760444] sh[243]: Discarding device blocks: done
[   14.922514] sh[243]: Filesystem label=
[   15.017007] sh[243]: OS type: Linux
[   15.132132] sh[243]: Block size=4096 (log=2)
[   15.192425] sh[243]: Fragment size=4096 (log=2)
[   15.194480] sh[243]: Stride=0 blocks, Stripe width=0 blocks
[   15.196503] sh[243]: 87120 inodes, 348155 blocks
[   15.198538] sh[243]: 0 blocks (0.00%) reserved for the super user
[  OK  ] Started Wyliodrin hypervisor.
[   15.202160] sh[243]: First data block=0
[   15.339380] sh[243]: Maximum filesystem blocks=356515840
[   15.462349] sh[243]: 11 block groups
[   15.552368] sh[243]: 32768 blocks per group, 32768 fragments per group
[   15.654824] sh[243]: 7920 inodes per group
[   15.705512] sh[243]: Superblock backups stored on blocks:
[   15.782265] sh[243]: 32768, 98304, 163840, 229376, 294912
[  OK  ] Started User Manager for UID 0.
[   15.955107] sh[243]: Allocating group tables: done
[   16.019543] sh[243]: Writing inode tables: done
[   16.100868] sh[243]: Creating journal (8192 blocks): done
[   18.878284] sh[243]: Writing superblocks and filesystem accounting information: done
[   18.903675] sh[243]: Formatting home partition : Success
[   18.958343] sh[243]: Mount /home partition : Success
[   19.036067] sh[243]: Restore home/root contents on new /home partition : Success
[   19.109127] sh[243]: Welcome to fdisk (util-linux 2.24.2).
[   19.174101] sh[243]: Changes will remain in memory only, until you decide to write them.
[   19.242291] sh[243]: Be careful before using the write command.
[   19.332272] sh[243]: Command (m for help):
[   19.397217] sh[243]: Partition type:
[   19.472285] sh[243]: p   primary (1 primary, 0 extended, 3 free)
[   19.522314] sh[243]: e   extended
[   19.574104] sh[243]: Select (default p): Partition number (2-4, default 2): Value out of range.
[   19.576199] sh[243]: Partition number (2-4, default 2):
[   19.578176] sh[243]: No free sectors available.
[   19.590287] sh[243]: Command (m for help):
[   19.772334] sh[243]: Command (m for help):
[   19.822423] sh[243]: Selected partition 1
[   19.929914] sh[243]: Hex code (type L to list all codes): Changed type of partition 'W95 FAT32' t
o 'W95 FAT32'.
[   19.977172] sh[243]: Command (m for help): Disk /dev/disk/by-partlabel/update: 768 MiB, 805306368
 bytes, 1572864 sectors
[   20.032808] sh[243]: Units: sectors of 1 * 512 = 512 bytes
[   20.102448] sh[243]: Sector size (logical/physical): 512 bytes / 512 bytes
[   20.192298] sh[243]: I/O size (minimum/optimal): 512 bytes / 512 bytes
[   20.242463] sh[243]: Disklabel type: dos
[   20.292173] sh[243]: Disk identifier: 0x669c3310
[   20.351762] sh[243]: Device                         Boot Start       End Blocks  Id System
[   20.453902] sh[243]: /dev/disk/by-partlabel/update1         16   1572863 786424   b W95 FAT32
[   20.538168] sh[243]: Command (m for help): Re-reading the partition table failed.: Invalid argume
nt
[   20.613993] sh[243]: The partition table has been altered.
[   20.643682] sh[243]: Calling ioctl() to re-read partition table.
[   20.746011] sh[243]: The kernel still uses the old table. The new table will be used at the next
reboot or after you run partprobe(8) or kpartx(8).
[   20.842048] sh[243]: Formatting update partition Step 1 : Success
[   20.943815] sh[243]: Formatting update partition Step 2 : Failed ret(1)
[   21.013080] sh[243]: No journal files were found.
[   21.102517] sh[243]: mkfs.vfat: /dev/loop0 contains a mounted file system.
[   21.162328] sh[243]: mkfs.vfat 2.11 (12 Mar 2005)
[   21.212506] sh[243]: Formatting update partition Step 3 : Failed ret(1)
[   21.272428] sh[243]: No journal files were found.
[   21.686524] sh[243]: Formatting update partition Step 4 final : Success
[   22.985996] sh[243]: Update file system table /etc/fstab : Success
[   24.627529] sh[243]: Generating Wifi Access Point SSID and passphrase : Success
[   24.679455] sh[243]: Post install success
[   24.960777] sh[243]: No journal files were found.
[   26.846251] systemctl[423]: rm '/etc/systemd/system/basic.target.wants/post-install.service'
[  OK  ] Started Post install service.
         Stopping User Manager for UID 0...
         Starting Serial Getty on ttyMFD2...
[  OK  ] Started Serial Getty on ttyMFD2.
[  OK  ] Reached target Login Prompts.
         Starting Intel_XDK_Daemon...
[  OK  ] Started Intel_XDK_Daemon.
         Starting Increases rootfs image size to fit partition...
[   28.690834] resize2fs[449]: resize2fs 1.42.9 (28-Dec-2013)
[   28.775061] resize2fs[449]: Filesystem at /dev/disk/by-partlabel/rootfs is mounted on /; on-line
resizing required
[   28.902180] resize2fs[449]: old_desc_blocks = 1, new_desc_blocks = 1
[   28.999246] resize2fs[449]: The filesystem on /dev/disk/by-partlabel/rootfs is now 393216 blocks
long.
[  OK  ] Stopped User Manager for UID 0.
[   29.396507] systemctl[452]: rm '/etc/systemd/system/default.target.wants/resize-rootfs.service'
[  OK  ] Started Increases rootfs image size to fit partition.
[  OK  ] Removed slice user-0.slice.

Poky (Yocto Project Reference Distro) 1.7.3 edison ttyMFD2

edison login: root
root@edison:~# exit
logout

Poky (Yocto Project Reference Distro) 1.7.3 edison ttyMFD2

edison login:
