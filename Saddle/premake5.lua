project "Saddle"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir ("%{wks.location}/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "src/**.h",
        "src/**.cpp"
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
        "glfw"
    }
