@echo off

if exist Makefile (
    MinGW32-make
) else (
    echo Makefile not found. Be sure to run run_premake.bat before calling compile.bat
)