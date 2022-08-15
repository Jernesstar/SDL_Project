project "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("%{wks.location}/Saddle/vendor/SDL2/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "include/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "include",

        "%{wks.location}/Saddle/src/Core",
        "%{wks.location}/Saddle/src/Events",
        "%{wks.location}/Saddle/src/Renderer",
        "%{wks.location}/Saddle/src/Scene",
        "%{wks.location}/Saddle/src/Systems",

        "%{wks.location}/Saddle/vendor/SDL2/include/SDL2",
        "%{wks.location}/Saddle/vendor/SDL2/include/SDL_image",
        "%{wks.location}/Saddle/vendor/SDL2/include/SDL_mixer",
        "%{wks.location}/Saddle/vendor/SDL2/include/SDL_ttf"
    }

    libdirs
    {
        "%{wks.location}/Saddle/vendor/SDL2/lib"
    }

    links
    {
        "Saddle",
        "mingw32",
        "SDL2main",
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
        