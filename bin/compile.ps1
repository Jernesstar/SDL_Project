cd $PSScriptRoot
cd ..

$cpp_file_count = 6
$stopwatch = New-Object System.Diagnostics.Stopwatch
echo "`n`tCompiling..."

$stopwatch.Start()

MinGW32-make -f bin\Makefile

$stopwatch.Stop()

if($LastExitCode -eq 0)
{
    echo "`tSuccessfully compiled $($cpp_file_count) files in $($stopwatch.Elapsed.TotalSeconds) seconds `n"
}
else
{
    echo "An error occured. Could not compile"
}