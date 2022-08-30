project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("%{wks.location}/Saddle/vendor/SDL2/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "include/**.h",
        "src/**.cpp",
    }

    includedirs
    {
        "include",

        "%{wks.location}/Saddle/src",

        "%{Includes.SDL2}",
        "%{Includes.SDL_image}",
        "%{Includes.SDL_mixer}",
        "%{Includes.SDL_ttf}"
    }

    libdirs
    {
        "%{wks.location}/Saddle/vendor/SDL2/lib"
    }

    links
    {
        "Saddle",

        "mingw32:static",
        "SDL2main",
        "SDL2",
        "SDL2_image",
        "SDL2_mixer",
        "SDL2_ttf"
    }

    buildoptions
    {
        "-fexceptions"
    }