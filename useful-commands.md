sshedison # bash alias for ssh into edison
scp -r ./ root@<IP>:~/src/ # copy this directory into edison

For my machine,
export LIBRARY_PATH="/home/andrew/projects-practice/everyone-say-wow/lib/mraa/build/src"
For edison,
MRAA_LIB_PATH="/home/root/everyone-say-wow/lib/mraa/build/src"
export LIBRARY_PATH="$LIBRARY_PATH:$MRAA_LIB_PATH"
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$MRAA_LIB_PATH"
