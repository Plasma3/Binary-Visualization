# Make sure that curent working dir is Programmering/C/Lego Manager
if (($pwd | Split-Path -Leaf) -ne "Binary Visualization") {
	Write-Error "THIS SCRIPT NEEDS TO BE CALLED WITH <Binary Visualization> AS CURRENT PWD!";
	break;
}

# Set stop on error
$ErrorActionPreference = "Stop"

# Load build flags and build functions
. ./scripts/flags
. ./scripts/build


Write-Output " > Starting compilation";
Write-Output "=========================";
# New-Item -ItemType Directory -Force -Path $tmp_folder | Out-Null;

# GCC_Build ".\src\themes.c" "themes" ($compile_flags + $debug_flags);
# GCC_Build ".\src\compress.c" "compress" ($compile_flags + $debug_flags);
GCC_BuildExe (".\main.c", ".\lib\fcu_windows.c") "a.exe" ($compile_flags + $debug_flags);

# DXC_Build "cs_6_0" "main" "./shaders/comp.gradiant.hlsl" "gradiant"
# DXC_Build "ps_6_0" "FS_main" "./shaders/colored_triangle.hlsl" "colored_triangle.frag"
# DXC_Build "vs_6_0" "VS_main" "./shaders/colored_triangle.hlsl" "colored_triangle.vert"

# GCC_Build "main.c" "main" ($compile_flags + $debug_flags + $library_glfw + $library_vulkan + $library_cimgui)

# GCC_Link (,"compress") "a.exe" ($compile_flags + $debug_flags);
# GPP_Link ("main", "fcu_windows", "vk_images", "vk_init", "VMA", "cimgui") "main.exe" ($compile_flags + $debug_flags + $library_glfw + $library_vulkan + $library_cimgui)

# if ($tmp_folder -eq "./.temp") { # Safety
# 	Remove-Item $tmp_folder -Recurse;
# }
Write-Output "=========================";
Write-Output "> Compilation success!"