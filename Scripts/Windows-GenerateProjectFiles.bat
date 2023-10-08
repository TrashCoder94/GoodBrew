@echo off
pushd %~dp0\..\

echo "Running GBHeaderTool"
call Tools\GBHeaderTool\GBHeaderTool-windows.exe GBEngine/Source/GBEngine/ GBEngine/Source/GeneratedCode/
if %errorlevel% neq 0 exit /b %errorlevel%

echo "Generating Projects with Premake"
call ThirdParty\premake\Binaries\premake5.exe vs2022
devenv GB.sln /rebuild Debug /project Premake
if %errorlevel% neq 0 exit /b %errorlevel%

popd