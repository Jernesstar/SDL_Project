cd $PSScriptRoot # project_folder\scripts
cd .. # project_folder

$stopwatch = New-Object System.Diagnostics.Stopwatch

cls
echo "`n`tCompiling..."
$stopwatch.Start()

MinGW32-make -f .\scripts\MakefileDebug

$stopwatch.Stop()
if($LastExitCode -eq 0) {
    echo "`tSuccessfully compiled in $($stopwatch.Elapsed.TotalSeconds) seconds `n"
}
else {
    echo "`tAn error occured. Could not compile"
}
# Read-Host -Prompt "`tPress any key to continue..."
# cls