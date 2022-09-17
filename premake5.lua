Includes = { }
Includes["glm"] = "%{wks.location}/Saddle/vendor/glm"
Includes["glfw"] = "%{wks.location}/Saddle/vendor/glfw"

workspace "Saddle"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }


include "Saddle/vendor/glfw"
include "Saddle"
include "Sandbox"