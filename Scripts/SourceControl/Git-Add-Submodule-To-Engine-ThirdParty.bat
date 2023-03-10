@echo off
pushd %~dp0\..\..\

set /P repo=What git repo do you want to add to GBEngine/ThirdParty (please reply with .git link not just the normal url)?
set /P folderName=What do you want to call the parent folder?

echo Adding %repo% to GBEngine/ThirdParty/%folderName%/
git submodule add %repo% GBEngine/ThirdParty/%folderName%/

popd
PAUSE