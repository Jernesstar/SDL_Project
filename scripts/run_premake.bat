@echo off

pushd %~dp0\..\
vendor\premake\bin\premake5.exe gmake2
popd

Pause