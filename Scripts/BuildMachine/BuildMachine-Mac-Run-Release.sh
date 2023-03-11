#!/bin/sh

echo "Running Release BuildMachine executable!"
chmod o+rx Binaries/Release-macosx-x86_64/BuildMachine/Assets
chmod +x Binaries/Release-macosx-x86_64/BuildMachine/BuildMachine
Binaries/Release-macosx-x86_64/BuildMachine/BuildMachine
if [ $? -ne 0 ] 
then
echo "Running release executable failed, exiting out..."
exit 1
fi
