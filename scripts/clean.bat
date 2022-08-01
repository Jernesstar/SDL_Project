@echo off

if exist obj\ (
    rmdir /s /q obj
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
if exist Saddle\vendor\SDL2\bin\Saddle.lib (
    del /q Saddle\vendor\SDL2\bin\Saddle.lib
)
if exist Saddle\vendor\SDL2\bin\Saddle.dll (
    del /q Saddle\vendor\SDL2\bin\Saddle.dll
)
if exist Saddle\vendor\SDL2\bin\Sandbox.exe (
    del /q Saddle\vendor\SDL2\bin\Sandbox.exe
)