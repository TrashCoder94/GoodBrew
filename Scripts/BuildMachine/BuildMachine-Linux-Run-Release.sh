#!/bin/sh

echo "Running Release BootupAndShutdownTest executable!"
chmod o+rx Binaries/Release-linux-x86_64/BootupAndShutdownTest/Assets
chmod +x Binaries/Release-linux-x86_64/BootupAndShutdownTest/BootupAndShutdownTest
pwd
sudo cd Binaries/Release-linux-x86_64/BootupAndShutdownTest
find . -type f
pwd
BootupAndShutdownTest
if [ $? -ne 0 ] 
then
echo "Running release BootupAndShutdownTest executable failed, exiting out..."
exit 1
fi
