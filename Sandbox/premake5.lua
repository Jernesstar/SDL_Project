project "Sandbox"
    kind "ConsoleApp"
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
        "%{wks.location}/Saddle/src",

        "%{Includes.freetype}",
        "%{Includes.glad}",
        "%{Includes.glfw}",
        "%{Includes.glm}",
        "%{Includes.stb_image}",
        "%{Includes.imgui}",
        "%{Includes.assimp}"
    }

    links
    {
        "Saddle",
        "freetype",
        "imgui",
        "glfw",
        "glad",
        "stb_image",
        "assimp",
        "gdi32",
    }

    filter "system:windows"
        systemversion "latest"
