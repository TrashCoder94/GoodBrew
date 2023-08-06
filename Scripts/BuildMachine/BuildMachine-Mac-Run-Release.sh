#!/bin/sh

echo "Copying SFML frameworks to /Library/Frameworks"
sudo cp -R ./GBEngine/ThirdParty/SFML/Mac/Frameworks/ /Library/Frameworks/
sudo cp -R ./GBEngine/ThirdParty/SFML/Mac/extlibs/ /Library/Frameworks/

echo "Running Release BootupAndShutdownTest executable!"
chmod o+rx Binaries/Release-macosx-x86_64/BootupAndShutdownTest/Assets
chmod +x Binaries/Release-macosx-x86_64/BootupAndShutdownTest/BootupAndShutdownTest
Binaries/Release-macosx-x86_64/BootupAndShutdownTest/BootupAndShutdownTest
if [ $? -ne 0 ] 
then
echo "Running release BootupAndShutdownTest executable failed, exiting out..."
exit 1
fi
