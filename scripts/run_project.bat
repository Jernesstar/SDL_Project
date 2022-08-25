@echo off
pushd %~dp0\..\

if exist .\bin\Sandbox.exe (
    echo Running project
    .\bin\Sandbox.exe
) else (
    echo Cannot find Sandbox.exe. Make sure to call compile.bat before calling run_project.bat
)

popd