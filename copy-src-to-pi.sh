#!/bin/bash

if [ $# -gt 1 ]; then
  echo "Usage: copy-src-to-pi.sh [--watch]"
  exit 1
fi

if [ $# -eq 1 ]; then
  watch=true
fi
piProjectRoot="~/projects/everyone-say-wow"
username="pi"
ipAddress="192.168.0.136"

dest="$username@$ipAddress:$piProjectRoot/src"

copySrcToPi() {
  echo "Copy src/ to $dest"
  scp -r ./src/ "$dest"
}

copySrcToPi

while [ $watch ]; do
  echo ""
  inotifywait -qr -e modify -e move -e create -e delete ./src
  copySrcToPi
done