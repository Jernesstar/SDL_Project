project "Saddle"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir ("%{wks.location}/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "src/**.h",
        "src/**.cpp",
    }

    includedirs
    {
        "src",

        "%{Includes.freetype}",
        "%{Includes.glad}",
        "%{Includes.glfw}",
        "%{Includes.glm}",
        "%{Includes.stb_image}",
        "%{Includes.imgui}",
        "%{Includes.imgui}/imgui",
        "%{Includes.assimp}"
    }
    
    links
    {
        "freetype",
        "imgui",
        "glad",
        "glfw",
        "stb_image",
        "assimp",
        "gdi32",
    }

    linkoptions
    {
        "../bin/assimp-vc143-mtd.lib",
    }

    filter "system:windows"
        systemversion "latest"
