@echo off
pushd %~dp0\..\..\

echo "Running Debug BuildMachine executable!"
call Binaries\Debug-windows-x86_64\BuildMachine\BuildMachine.exe
if %errorlevel% neq 0 exit /b %errorlevel%

popd