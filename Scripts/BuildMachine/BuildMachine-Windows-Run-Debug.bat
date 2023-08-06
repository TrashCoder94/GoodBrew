@echo off
pushd %~dp0\..\..\

echo "Running Debug BootupAndShutdownTest executable!"
call Binaries\Debug-windows-x86_64\BootupAndShutdownTest\BootupAndShutdownTest.exe
if %errorlevel% neq 0 exit /b %errorlevel%

popd