project "freetype"
    kind "StaticLib"
    language "C"

    targetdir ("%{wks.location}/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "%{VendorPaths.freetype}/src/base/ftsystem.c",
        "%{VendorPaths.freetype}/src/base/ftinit.c",
        "%{VendorPaths.freetype}/src/base/ftdebug.c",
        "%{VendorPaths.freetype}/src/base/ftbase.c",
        "%{VendorPaths.freetype}/src/base/ftbbox.c",
        "%{VendorPaths.freetype}/src/base/ftglyph.c",
        "%{VendorPaths.freetype}/src/base/ftbitmap.c",
        "%{VendorPaths.freetype}/src/base/ftstroke.c",
        "%{VendorPaths.freetype}/src/base/ftsynth.c",
        "%{VendorPaths.freetype}/src/sfnt/sfnt.c",
        "%{VendorPaths.freetype}/src/truetype/truetype.c",
        "%{VendorPaths.freetype}/src/type1/type1.c",
        "%{VendorPaths.freetype}/src/cff/cff.c",
        "%{VendorPaths.freetype}/src/cid/type1cid.c",
        "%{VendorPaths.freetype}/src/bdf/bdf.c",
        "%{VendorPaths.freetype}/src/pcf/pcf.c",
        "%{VendorPaths.freetype}/src/pfr/pfr.c",
        "%{VendorPaths.freetype}/src/type42/type42.c",
        "%{VendorPaths.freetype}/src/winfonts/winfnt.c",
        "%{VendorPaths.freetype}/src/gzip/ftgzip.c",
        "%{VendorPaths.freetype}/src/psaux/psaux.c",
        "%{VendorPaths.freetype}/src/raster/raster.c",
        "%{VendorPaths.freetype}/src/sdf/sdf.c",
        "%{VendorPaths.freetype}/src/smooth/smooth.c",
        "%{VendorPaths.freetype}/src/autofit/autofit.c",
        "%{VendorPaths.freetype}/src/pshinter/pshinter.c",
        "%{VendorPaths.freetype}/src/psnames/psnames.c",
        "%{VendorPaths.freetype}/src/svg/svg.c"
    }

    includedirs
    {
        "%{Includes.freetype}"
    }

    buildoptions 
    { 
        "-DFT2_BUILD_LIBRARY"
    }
