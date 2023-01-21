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
        "src/Saddle/ECS/*.h",
        "src/Saddle/ECS/*.cpp",
        "src/OpenGL/*.h",
        "src/OpenGL/*.cpp",
    }

    includedirs
    {
        "src",

        "%{Includes.glm}",
        "%{Includes.glfw}",
        "%{Includes.glad}",
        "%{Includes.stb_image}",
    }
    
    links
    {
        "glfw",
        "glad",
        "stb_image",
        "gdi32"
    }

    filter "system:windows"
        systemversion "latest"
