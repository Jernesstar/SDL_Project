@echo off

if exist .\Saddle\vendor\SDL2\bin\Sandbox.exe (
    .\Saddle\vendor\SDL2\bin\Sandbox.exe
) else (
    echo Cannot find Sandbox.exe. Make sure to call compile.bat before calling run_project.bat

)