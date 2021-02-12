sshedison # bash alias for ssh root@10.0.0.5
scp -r ./ root@10.0.0.5:~/src/

For my machine,
export LIBRARY_PATH="/home/andrew/projects-practice/everyone-say-wow/lib/mraa/build/src"
For edison,
MRAA_LIB_PATH="/home/root/everyone-say-wow/lib/mraa/build/src"
export LIBRARY_PATH="$LIBRARY_PATH:$MRAA_LIB_PATH"
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$MRAA_LIB_PATH"
