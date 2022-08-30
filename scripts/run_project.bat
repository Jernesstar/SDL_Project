@echo off
pushd %~dp0\..\

if exist .\Saddle\vendor\SDL2\bin\Sandbox.exe (
    echo Running project
    .\Saddle\vendor\SDL2\bin\Sandbox.exe
) else (
    echo Cannot find Sandbox.exe. Make sure to call build.bat before calling run_project.bat
)

popd