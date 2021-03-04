configure_edison --setup # then follow the setup
mkdir everyone-say-wow

# Add ssh key
https://linuxhandbook.com/add-ssh-public-key-to-server/
ssh-copy-id -i ~/.ssh/id_rsa.pub root@192.168.0.150

