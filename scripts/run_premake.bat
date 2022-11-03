@echo off

pushd %~dp0\..\

echo --------------------------------
vendor\premake\bin\premake5.exe gmake2
echo --------------------------------
vendor\premake\bin\premake5.exe vs2022
echo --------------------------------

popd
Pause