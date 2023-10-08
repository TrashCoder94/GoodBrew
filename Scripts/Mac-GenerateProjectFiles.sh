#!/bin/sh

echo "Running GBHeaderTool"
chmod +x Tools/GBHeaderTool/GBHeaderTool-mac
Tools/GBHeaderTool/GBHeaderTool-mac GBEngine/Source/GBEngine/ GBEngine/Source/GeneratedCode/
if [ $? -ne 0 ] 
then
echo "Running GBHeaderTool failed, exiting out..."
exit 1
fi

echo "Generating Project with Premake!"
chmod +x ThirdParty/premake/Binaries/premake5_mac
ThirdParty/premake/Binaries/premake5_mac --file=premake5.lua gmake2
if [ $? -ne 0 ] 
then
echo "Generating project files failed, exiting out..."
exit 1
fi
