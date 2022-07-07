@echo off
cls
echo Compiling...
MinGW32-make -f bin\Makefile
if %ERRORLEVEL% == 0 (
    echo Compiled successfully
    echo.
) else (
    echo An error occurred. Could not build
    echo.
)