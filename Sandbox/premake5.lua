project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("%{wks.location}/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "include/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "include",

        "%{wks.location}/Saddle/src",

        "%{wks.location}/Saddle/vendor/SDL2/include/SDL2",
        "%{wks.location}/Saddle/vendor/SDL2/include/SDL_image",
        "%{wks.location}/Saddle/vendor/SDL2/include/SDL_mixer",
        "%{wks.location}/Saddle/vendor/SDL2/include/SDL_ttf"
    }

    links
    {
        "Saddle"
    }

    linkoptions
    {
        "-mwindows",
        "-municode"
    }
