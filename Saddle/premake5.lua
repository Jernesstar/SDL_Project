project "Saddle"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir ("%{wks.location}/Saddle/vendor/SDL2/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src",

        "%{Includes.SDL2}",
        "%{Includes.SDL_image}",
        "%{Includes.SDL_mixer}",
        "%{Includes.SDL_ttf}"
    }

    libdirs
    {
        "vendor/SDL2/lib",
    }
    
    links
    {
        "mingw32:static",
        
        "SDL2",
        "SDL2_image",
        "SDL2_mixer",
        "SDL2_ttf"
    }

    buildoptions
    {
        "-fexceptions"
    }

    -- links
    -- {
    --     "SDL2"
    -- }
