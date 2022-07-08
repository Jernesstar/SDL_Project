cd $PSScriptRoot # project_folder\build\scripts
cd ..\.. # project_folder

$cpp_file_count = 6
$stopwatch = New-Object System.Diagnostics.Stopwatch
cls
echo "`n`tCompiling..."

$stopwatch.Start()

MinGW32-make -f build\scripts\Makefile

$stopwatch.Stop()

if($LastExitCode -eq 0)
{
    echo "`tSuccessfully compiled $($cpp_file_count) files in $($stopwatch.Elapsed.TotalSeconds) seconds `n"
}
else
{
    echo "An error occured. Could not compile"
}