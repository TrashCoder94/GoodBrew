#!/bin/sh

echo "Generating Project with Premake!"
chmod +x ThirdParty/premake/Binaries/premake5_mac
ThirdParty/premake/Binaries/premake5_mac --file=premake5.lua gmake2
if [ $? -ne 0 ] 
then
echo "Generating project files failed, exiting out..."
exit 1
fi

cd /ThirdParty/Shared
pwd
echo "Generating binaries for ThirdParty dependencies..."
make config=debug_x86_64
if [ $? -ne 0 ] 
then
echo "Building ThirdParty dependencies failed, exiting out..."
exit 1
fi

cd ../../
pwd
echo "Linking binaries for ThirdParty dependencies..."
ThirdParty/premake/Binaries/premake5_mac --file=premake5.lua gmake2
if [ $? -ne 0 ] 
then
echo "Linking binaries for ThirdParty dependencies failed, exiting out..."
exit 1
fi

echo "Building Debug Configuration"
make config=debug_x86_64
if [ $? -ne 0 ] 
then
echo "Building Debug Configuration failed, exiting out..."
exit 1
fi
