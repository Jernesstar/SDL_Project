workspace "Saddle"
    architecture "x64"


project "Saddle"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin")
    objdir ("obj")