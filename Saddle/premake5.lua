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
    }
    
    links
    {
        "freetype",
        "imgui",
        "glad",
        "glfw",
        "stb_image",
        "gdi32",
    }

    filter "system:windows"
        systemversion "latest"
