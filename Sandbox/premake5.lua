project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

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
    }

    filter "system:windows"
        systemversion "latest"

        links
        {
            "gdi32"
        }

    filter "system:linux"
        links
        {
            "pthread",
            "dl"
        }