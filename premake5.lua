Includes = { }
Includes["SDL2"] = "%{wks.location}/Saddle/vendor/SDL2/include/SDL2"
Includes["SDL_image"] = "%{wks.location}/Saddle/vendor/SDL2/include/SDL_image"
Includes["SDL_mixer"] = "%{wks.location}/Saddle/vendor/SDL2/include/SDL_mixer"
Includes["SDL_ttf"] = "%{wks.location}/Saddle/vendor/SDL2/include/SDL_ttf"

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

include "Saddle"
include "Sandbox"