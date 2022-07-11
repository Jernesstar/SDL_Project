cd $PSScriptRoot # project_folder\scripts
cd .. # project_folder

$cpp_file_count = 6
$stopwatch = New-Object System.Diagnostics.Stopwatch

cls
echo "`n`tCompiling..."
$stopwatch.Start()

MinGW32-make -f scripts\Makefile

$stopwatch.Stop()
if($LastExitCode -eq 0) {
    echo "`tSuccessfully compiled $($cpp_file_count) files in $($stopwatch.Elapsed.TotalSeconds) seconds `n"
}
else {
    echo "`tAn error occured. Could not compile"
}
Read-Host -Prompt "`tPress any key to continue..."