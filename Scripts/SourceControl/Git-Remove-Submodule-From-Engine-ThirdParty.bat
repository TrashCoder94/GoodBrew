@echo off
pushd %~dp0\..\..\

set /P folderName=What is the folder name of the submodule you want to remove from GBEngine/ThirdParty folder?

echo Removing %repo% from GBEngine/ThirdParty/%folderName%/
git rm GBEngine/ThirdParty/%folderName%/

popd
PAUSE