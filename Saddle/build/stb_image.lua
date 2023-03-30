project "stb_image"
    kind "StaticLib"
    language "C"

    targetdir ("%{wks.location}/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "include/stb_image/stb_image.h",
        "src/stb_image.cpp",
    }

    includedirs
    {
        "include"
    }
