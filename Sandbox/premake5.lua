project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("%{wks.location}/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "src/main.cpp",
    }

    includedirs
    {
        "include",

        "%{wks.location}/Saddle/src",

        "%{Includes.glm}",
        "%{Includes.glfw}/deps",
        "%{Includes.glfw}/include",
    }

    libdirs
    {
        "%{wks.location}/Saddle/vendor/SDL2/lib"
    }

    links
    {
        "Saddle",
        "glfw",
        "gdi32",
    }

    filter "system:windows"
        systemversion "latest"
