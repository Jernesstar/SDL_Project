project "glad"
    kind "StaticLib"
    language "C"

    targetdir ("%{wks.location}/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "%{VendorPaths.glad}/include/*.h",
        "%{VendorPaths.glad}/src/glad.c"
    }

    includedirs
    {
        "%{VendorPaths.glad}/include"
    }

    filter "system:windows"

        files
        {
            "%{VendorPaths.glad}/src/glad_wgl.c"
        }
