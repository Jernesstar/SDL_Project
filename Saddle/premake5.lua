project "Saddle"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir ("%{wks.location}/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "src/Saddle/Core/*.h",
        "src/Saddle/Core/*.cpp",
        "src/Saddle/Events/*.h",
        "src/Saddle/Events/*.cpp",
        "src/Saddle/Renderer/*.h",
        "src/Saddle/Renderer/*.cpp",
        "src/OpenGL/*.h",
        "src/OpenGL/*.cpp",
    }

    includedirs
    {
        "src",

        "%{Includes.glm}",
        "%{Includes.glfw}/deps",
        "%{Includes.glfw}/include",
        "%{Includes.glad}/include",
    }
    
    links
    {
        "glfw",
        "glad",
        "gdi32"
    }

    filter "system:windows"
        systemversion "latest"
