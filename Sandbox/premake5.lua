project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("%{wks.location}/bin")
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

    links
    {
        "Saddle"
    }
