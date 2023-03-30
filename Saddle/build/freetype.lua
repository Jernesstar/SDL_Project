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
        "src/base/ftstroke.c",
        "src/base/ftsynth.c",
        "src/sfnt/sfnt.c",
        "src/truetype/truetype.c",
        "src/type1/type1.c",
        "src/cff/cff.c",
        "src/cid/type1cid.c",
        "src/bdf/bdf.c",
        "src/pcf/pcf.c",
        "src/pfr/pfr.c",
        "src/type42/type42.c",
        "src/winfonts/winfnt.c",
        "src/gzip/ftgzip.c",
        "src/psaux/psaux.c",
        "src/raster/raster.c",
        "src/sdf/sdf.c",
        "src/smooth/smooth.c",
        "src/autofit/autofit.c",
        "src/pshinter/pshinter.c",
        "src/psnames/psnames.c",
        "src/svg/svg.c"
    }

    includedirs
    {
        "include"
    }

    buildoptions 
    { 
        "-DFT2_BUILD_LIBRARY"
    }
