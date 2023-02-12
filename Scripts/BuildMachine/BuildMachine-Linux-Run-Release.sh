#!/bin/sh

echo "Running Release BuildMachine executable!"
chmod +x Binaries/Release-linux-x86_64/BuildMachine/BuildMachine
Binaries/Release-linux-x86_64/BuildMachine/BuildMachine
if [ $? -ne 0 ] 
then
echo "Running release executable failed, exiting out..."
exit 1
fi
