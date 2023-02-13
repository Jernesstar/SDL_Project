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
    }

    links
    {
        "Saddle",
        "freetype",
        "glfw",
        "glad",
        "stb_image",
        "gdi32",
    }

    filter "system:windows"
        systemversion "latest"
