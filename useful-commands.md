sshedison # bash alias for ssh into edison
scp -r ./ root@<IP>:~/src/ # copy this directory into edison

For my machine,
PC_MRAA_LIB_PATH="/home/andrew/projects-practice/everyone-say-wow/lib/mraa/build/src"
PC_MYMATH_LIB_PATH="/home/andrew/projects-practice/everyone-say-wow/lib/mymath"
export LIBRARY_PATH="$PC_MRAA_LIB_PATH:$PC_MYMATH_LIB_PATH"

For edison,
EDISON_MRAA_LIB_PATH="/home/root/everyone-say-wow/lib/mraa/build/src"
EDISON_MYMATH_LIB_PATH="/home/root/everyone-say-wow/lib/mymath"
export LIBRARY_PATH="$EDISON_MRAA_LIB_PATH:$EDISON_MYMATH_LIB_PATH"
export LD_LIBRARY_PATH="$EDISON_MRAA_LIB_PATH:$EDISON_MYMATH_LIB_PATH"
