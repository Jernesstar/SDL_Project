@echo off
pushd %~dp0\..\

if exist Makefile (
    MinGW32-make

    if $? == 0 (
        echo Compiled project successfully
    )
    
) else (
    echo Makefile not found. Be sure to run run_premake.bat before calling compile.bat
)

popd
Pause