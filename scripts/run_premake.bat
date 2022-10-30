@echo off

pushd %~dp0\..\
vendor\premake\bin\premake5.exe vs2022
popd

Pause