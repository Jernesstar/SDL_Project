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
        "include",

        "%{wks.location}/Saddle/src",

        "%{Includes.glm}",
        "%{Includes.glfw}/include",
        "%{Includes.glad}/include",
    }

    links
    {
        "Saddle",
        "glfw",
        "glad",
        "gdi32",
    }

    filter "system:windows"
        systemversion "latest"
