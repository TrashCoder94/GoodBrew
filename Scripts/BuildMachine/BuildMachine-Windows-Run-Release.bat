@echo off
pushd %~dp0\..\..\

echo "Running Release BootupAndShutdownTest executable!"
cd Binaries\Release-windows-x86_64\BootupAndShutdownTest
call BootupAndShutdownTest.exe
if %errorlevel% neq 0 exit /b %errorlevel%

popd