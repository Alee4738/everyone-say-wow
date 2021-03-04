## Connect

screen /dev/ttyUSB0 115200 # use screen to connect
sshedison # bash alias for ssh into edison

## Build

scp -r ./ root@<IP>:~/src/ # copy this directory into edison

For my machine,
everyoneSayWowPath="$(pwd)" # path of the everyone-say-wow project
PC_MRAA_LIB_PATH="$everyoneSayWowPath/lib/mraa/build/src"
PC_MYMATH_LIB_PATH="$everyoneSayWowPath/lib/mymath/bin/shared"
export LD_LIBRARY_PATH="$PC_MRAA_LIB_PATH:$PC_MYMATH_LIB_PATH"

For edison,
everyoneSayWowPath="$(pwd)" # path of the everyone-say-wow project
EDISON_MRAA_LIB_PATH="$everyoneSayWowPath/lib/mraa/build/src"
EDISON_MYMATH_LIB_PATH="$everyoneSayWowPath/lib/mymath/bin/shared"
export LD_LIBRARY_PATH="$EDISON_MRAA_LIB_PATH:$EDISON_MYMATH_LIB_PATH"

## Debug

ldd <executable> - see what shared libraries are linked to <executable>


## Other
configure_edison # show help, has lots of options
configure_edisson --showWiFiIP
