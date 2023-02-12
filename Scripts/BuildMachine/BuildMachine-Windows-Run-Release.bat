@echo off
pushd %~dp0\..\..\

echo "Running Release BuildMachine executable!"
call Binaries\Release-windows-x86_64\BuildMachine\BuildMachine.exe
if %errorlevel% neq 0 exit /b %errorlevel%

popd