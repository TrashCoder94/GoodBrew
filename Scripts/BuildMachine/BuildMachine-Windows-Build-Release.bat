@echo off
pushd %~dp0\..\..\

echo "Generating Project with Premake"
call ThirdParty\premake\Binaries\premake5.exe vs2022
devenv GB.sln /rebuild Release /project Premake
if %errorlevel% neq 0 exit /b %errorlevel%

echo "Generating binaries for ThirdParty dependencies..."
devenv GB.sln /rebuild Release /project Shared
if %errorlevel% neq 0 exit /b %errorlevel%

echo "Linking binaries for ThirdParty dependencies..."
devenv GB.sln /rebuild Release /project Premake
if %errorlevel% neq 0 exit /b %errorlevel%

echo "Building Release Configuration"
devenv GB.sln /rebuild Release
if %errorlevel% neq 0 exit /b %errorlevel%

popd