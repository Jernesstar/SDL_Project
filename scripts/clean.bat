@echo off
pushd %~dp0\..\

if exist Makefile  (
    MinGW32-make clean
    del /q Makefile
)
if exist Saddle\Makefile (
    del /q Saddle\Makefile
)
if exist Sandbox\Makefile (
    del /q Sandbox\Makefile
)
if exist Saddle\vendor\glad\Makefile (
    del /q Saddle\vendor\glad\Makefile
)
if exist Saddle\vendor\glfw\Makefile (
    del /q Saddle\vendor\glfw\Makefile
)
if exist bin/ (
    rmdir /s /q bin
)
if exist obj/ (
    rmdir /s /q obj
)

echo Project clean
popd
Pause