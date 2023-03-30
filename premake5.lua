VendorPath = "%{wks.location}/Saddle/vendor"

VendorPaths = {}
VendorPaths["glm"] = "%{VendorPath}/glm"
VendorPaths["glfw"] = "%{VendorPath}/glfw"
VendorPaths["glad"] = "%{VendorPath}/glad"
VendorPaths["freetype"] = "%{VendorPath}/freetype"
VendorPaths["stb_image"] = "%{VendorPath}/stb_image"
VendorPaths["imgui"] = "%{VendorPath}/imgui"

Includes = {}
Includes["glm"] = "%{VendorPaths.glm}"
Includes["glfw"] = "%{VendorPaths.glfw}/include"
Includes["glad"] = "%{VendorPaths.glad}/include"
Includes["freetype"] = "%{VendorPaths.freetype}/include"
Includes["stb_image"] = "%{VendorPaths.stb_image}/include"
Includes["imgui"] = "%{VendorPaths.imgui}"

workspace "Saddle"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

include "Saddle/build/freetype"
include "Saddle/build/glad"
include "Saddle/build/glfw"
include "Saddle/build/stb_image"
include "Saddle/build/imgui"
include "Saddle"
include "Sandbox"