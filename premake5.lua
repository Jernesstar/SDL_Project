Includes = {}
Includes["glm"] = "%{wks.location}/Saddle/vendor/glm"
Includes["glfw"] = "%{wks.location}/Saddle/vendor/glfw/include"
Includes["glad"] = "%{wks.location}/Saddle/vendor/glad/include"
Includes["stb_image"] = "%{wks.location}/Saddle/vendor/stb_image/include"

workspace "Saddle"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

include "Saddle/vendor/glfw"
include "Saddle/vendor/glad"
include "Saddle/vendor/stb_image"
include "Saddle"
include "Sandbox"