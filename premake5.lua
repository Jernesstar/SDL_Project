workspace "Saddle"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

project "Saddle"
    location "Saddle"
    kind "StaticLib"
    language "C++"

    targetdir ("bin")
    objdir ("obj")

    files
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/include/**.h"
    }

    includedirs
    {
        "%{prj.name}/include",
        "%{prj.name}/vendor/SDL2/include/SDL2",
        "%{prj.name}/vendor/SDL2/include/SDL_image",
        "%{prj.name}/vendor/SDL2/include/SDL_mixer",
        "%{prj.name}/vendor/SDL2/include/SDL_ttf"
    }

    libdirs
    {
        "%{prj.name}/vendor/SDL2/bin"
    }

    links
    {
        "SDL2",
        "SDL2_image",
        "SDL2_mixer",
        "SDL2_ttf"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "_WINDOWS",
            "WIN32"
        }

    filter "configurations:Debug"
        defines "SADDLE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "SADDLE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "SADDLE_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin")
    objdir ("obj")

    files
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/include/**.h"
    }

    includedirs
    {
        "%{prj.name}/include",
        "Saddle/include",
        "Saddle/vendor/SDL2/include/SDL2",
        "Saddle/vendor/SDL2/include/SDL_image",
        "Saddle/vendor/SDL2/include/SDL_mixer",
        "Saddle/vendor/SDL2/include/SDL_ttf"
    }

    links
    {
        "Saddle"
    }

    filter "configurations:Debug"
    defines "SADDLE_DEBUG"
    symbols "On"

    filter "configurations:Release"
        defines "SADDLE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "SADDLE_DIST"
        optimize "On"