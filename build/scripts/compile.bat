@echo off

echo.
echo    Compiling...

MinGW32-make -f build\scripts\Makefile

if %ERRORLEVEL% == 0 (
    echo    Compiled project successfully
    echo.
) else (
    echo.
    echo    An error occurred. Could not compile
    echo.   
)

Pause