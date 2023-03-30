project "glad"
    kind "StaticLib"
    language "C"

    targetdir ("%{wks.location}/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "include/*.h",
        "src/glad.c"
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        
        files
        {
            "src/glad_wgl.c"
        }
