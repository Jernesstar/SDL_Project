@echo off
pushd %~dp0\..\

echo Cleaning project

if exist obj\ (
    rmdir /s /q obj
)
if exist bin\ (
    rmdir /s /q bin
)
if exist Makefile  (
    del /q Makefile
)
if exist Saddle\Makefile (
    del /q Saddle\Makefile
)
if exist Sandbox\Makefile (
    del /q Sandbox\Makefile
)

if exist .\Saddle\vendor\SDL2\bin\Saddle.lib (
    del .\Saddle\vendor\SDL2\bin\Saddle.lib
)

if exist .\Saddle\vendor\SDL2\bin\Sandbox.exe (
    del .\Saddle\vendor\SDL2\bin\Sandbox.exe
)

echo Project clean
popd
Pause