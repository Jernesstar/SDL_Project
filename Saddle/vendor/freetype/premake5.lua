project "freetype"
    kind "StaticLib"
    language "C"

    targetdir ("%{wks.location}/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "src/base/ftsystem.c",
        "src/base/ftinit.c",
        "src/base/ftdebug.c",

        "src/base/ftbase.c",

        "src/base/ftbbox.c",
        "src/base/ftglyph.c",

        "src/base/ftbitmap.c",
        
        "src/sfnt/sfnt.c",
        "src/truetype/truetype.c",

        "src/raster/raster.c",
        "src/sdf/sdf.c",
        "src/smooth/smooth.c",

        "src/psnames/psnames.c",
        "src/pshinter/pshinter.c",
        "src/psaux/psaux.c"
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"