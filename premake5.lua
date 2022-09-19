Includes = {}
Includes["glm"] = "%{wks.location}/Saddle/vendor/glm"
Includes["glfw"] = "%{wks.location}/Saddle/vendor/glfw"
Includes["glad"] = "%{wks.location}/Saddle/vendor/glad"

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
include "Saddle"
include "Sandbox"