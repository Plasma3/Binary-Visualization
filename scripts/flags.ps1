# Helper
$parent_path = ($pwd | Split-Path).ToString()

# General compile flags (should always be used)
$compile_flags =, "-std=c23", "-fdiagnostics-color=always"
$compile_flags += "-Wall", "-Wextra", "-Wshadow", "-Wpedantic", "-Wuninitialized", "-Wconversion"
$compile_flags += "-Wno-unknown-pragmas", "-Wno-nonnull-compare", "-Wno-unused-function", "-Werror=nonnull"

# Flags for generating debug builds
$debug_flags =, "-g", "-Og"
$debug_flags = $debug_flags

# Release flags for generating release builds
$release_flags =, "-O2"
$release_flags = $release_flags

# Libraries to be included in builds
$library_glfw =, ("-I{0}/sdk/GLFW/include" -f $parent_path)
$library_glfw += ("-L{0}/sdk/GLFW/lib-mingw-w64" -f $parent_path)
$library_glfw += "-lglfw3"

$library_vulkan =, "-IC:/VulkanSDK/1.3.296.0/Include"
$library_vulkan += "-LC:/VulkanSDK/1.3.296.0/Lib"
$library_vulkan += "-lvulkan-1"
$library_vulkan += "-lgdi32"

$library_cimgui =, ("-I{0}/sdk/cimgui" -f $parent_path)
$library_cimgui += ("-L{0}/sdk/cimgui" -f $parent_path)
$library_cimgui += "-lcimgui"


