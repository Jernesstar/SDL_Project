@echo off
pushd %~dp0\..\

if exist Saddle\Makefile  (
    MinGW32-make --no-print-directory -C Saddle -f Makefile clean
    del /q Saddle\Makefile
)
if exist Sandbox\Makefile  (
    MinGW32-make --no-print-directory -C Sandbox -f Makefile clean
    del /q Sandbox\Makefile
)
if exist Makefile  (
    del /q Makefile
)
if exist Saddle\vendor\glad\Makefile (
    del /q Saddle\vendor\glad\Makefile
)
if exist Saddle\vendor\glfw\Makefile (
    del /q Saddle\vendor\glfw\Makefile
)
if exist Saddle\vendor\stb_image\Makefile (
    del /q Saddle\vendor\stb_image\Makefile
)

echo Project clean
popd
Pause