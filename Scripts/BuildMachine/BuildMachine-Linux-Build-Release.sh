#!/bin/sh

echo "Generating Project with Premake!"
chmod +x ThirdParty/premake/Binaries/premake5
ThirdParty/premake/Binaries/premake5 --file=premake5.lua gmake2
if [ $? -ne 0 ] 
then
echo "Generating project files failed, exiting out..."
exit 1
fi

sudo chmod o+x ./ThirdParty/Shared
cd ./ThirdParty/Shared
pwd
echo "Generating binaries for ThirdParty dependencies..."
make config=release_x86_64
if [ $? -ne 0 ] 
then
echo "Building ThirdParty dependencies failed, exiting out..."
find . -type f
exit 1
fi

cd ../../
pwd
echo "Linking binaries for ThirdParty dependencies..."
ThirdParty/premake/Binaries/premake5 --file=premake5.lua gmake2
if [ $? -ne 0 ] 
then
echo "Linking binaries for ThirdParty dependencies failed, exiting out..."
find . -type f
exit 1
fi

echo "Building Release Configuration"
make config=release_x86_64
if [ $? -ne 0 ] 
then
echo "Building Release Configuration failed, exiting out..."
find . -type f
exit 1
fi
