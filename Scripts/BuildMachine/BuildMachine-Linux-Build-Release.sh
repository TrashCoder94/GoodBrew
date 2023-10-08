#!/bin/sh

echo "Running GBHeaderTool"
chmod +x Tools/GBHeaderTool/GBHeaderTool-linux
Tools/GBHeaderTool/GBHeaderTool-linux GBEngine/Source/GBEngine/ GBEngine/Source/GeneratedCode/
if [ $? -ne 0 ] 
then
echo "Running GBHeaderTool failed, exiting out..."
exit 1
fi

echo "Generating Project with Premake!"
chmod +x ThirdParty/premake/Binaries/premake5
ThirdParty/premake/Binaries/premake5 --file=premake5.lua gmake2
if [ $? -ne 0 ] 
then
echo "Generating project files failed, exiting out..."
exit 1
fi

echo "Building Release Configuration"
make config=release_x86_64
if [ $? -ne 0 ] 
then
echo "Building Release Configuration failed, exiting out..."
exit 1
fi
