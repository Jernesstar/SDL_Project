@echo off

cls
echo Compiling...

@REM Will cd into the parent directory of this compile.bat file, represented by %~dp0
@REM @REM Will run the Makefile, which will compile the project
for /F "usebackq delims=" %%r in (
    `powershell -Command "cd '%~dp0'; cd ..; $compiling_time = Measure-Command { MinGW32-make -f bin\Makefile }; $compiling_time.TotalSeconds"`
) do set "compiling_time=%%r"

if %ERRORLEVEL% == 0 (
    echo Compiling took %compiling_time% seconds
    echo.
)