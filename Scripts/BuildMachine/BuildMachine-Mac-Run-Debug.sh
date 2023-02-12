#!/bin/sh

echo "Running Debug BuildMachine executable!"
chmod +x Binaries/Debug-macosx-x86_64/BuildMachine/BuildMachine
Binaries/Debug-macosx-x86_64/BuildMachine/BuildMachine
if [ $? -ne 0 ] 
then
echo "Running debug executable failed, exiting out..."
exit 1
fi
