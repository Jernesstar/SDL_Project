project "Saddle"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"

    targetdir ("%{wks.location}/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "src/**.h",
        "src/**.cpp",

        "vendor/SDL2/include/**.h"
    }

    includedirs
    {
        "src",

        "%{wks.location}/Saddle/vendor/SDL2/include/SDL2",
        "%{wks.location}/Saddle/vendor/SDL2/include/SDL_image",
        "%{wks.location}/Saddle/vendor/SDL2/include/SDL_mixer",
        "%{wks.location}/Saddle/vendor/SDL2/include/SDL_ttf"
    }

    libdirs
    {
        "vendor/SDL2/lib"
    }

    links
    {
        "mingw32",
        "winmm",
        "ws2_32",
        "wsock32",
        "glu32",
        "dinput8",
        "dxguid", 
        "dxerr8", 
        "user32", 
        "gdi32", 
        "imm32",
        "ole32", 
        "oleaut32", 
        "shell32", 
        "version", 
        "uuid",
        "setupapi",
        "usp10",
        "rpcrt4",

        "SDL2main:static",
        "SDL2:static",
        "SDL2_image:static",
        "SDL2_mixer:static",
        "SDL2_ttf:static",
    }
