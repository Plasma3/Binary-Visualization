# Make sure that curent working dir is Programmering/C/Lego Manager
if (($pwd | Split-Path -Leaf) -ne "Lego Manager") {
	Write-Error "THIS SCRIPT NEEDS TO BE CALLED WITH <vulkan-test> AS CURRENT PWD!";
	break;
}

# Set stop on error
$ErrorActionPreference = "Stop"

# Load build flags and build functions
. ./scripts/flags
. ./scripts/build

Write-Output " > Starting compilation of tests";
Write-Output "=========================";

GCC_BuildExe (,"tests/linked_list.c") "tests.exe" ($compile_flags + $debug_flags);

# if ($tmp_folder -eq "./.temp") { # Safety
# 	Remove-Item $tmp_folder -Recurse;
# }
Write-Output "=========================";
Write-Output "> Compilation success!"




