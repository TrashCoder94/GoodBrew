#!/bin/sh

echo "Running Release BootupAndShutdownTest executable!"
chmod o+rx Binaries/Release-linux-x86_64/BootupAndShutdownTest/Assets
chmod +x Binaries/Release-linux-x86_64/BootupAndShutdownTest/BootupAndShutdownTest
Binaries/Release-linux-x86_64/BootupAndShutdownTest/BootupAndShutdownTest
if [ $? -ne 0 ] 
then
echo "Running release BootupAndShutdownTest executable failed, exiting out..."
exit 1
fi
