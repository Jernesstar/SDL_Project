project "Saddle"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir ("%{wks.location}/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "src/Saddle/Core/Application.h",
        "src/Saddle/Core/Application.cpp",
        "src/OpenGL/Window.h",
        "src/OpenGL/Window.cpp",
    }

    includedirs
    {
        "src",

        "%{Includes.glm}",
        "%{Includes.glfw}/deps",
        "%{Includes.glfw}/include",
    }
    
    links
    {
        "glfw",
        "gdi32",
        "opengl"
    }

    filter "system:windows"
        systemversion "latest"
