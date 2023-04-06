project "imgui"
    kind "StaticLib"
    language "C"

    targetdir ("%{wks.location}/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "%{VendorPaths.imgui}/*.h",
        "%{VendorPaths.imgui}/*.cpp",

        "%{VendorPaths.imgui}/backends/imgui_impl_glfw.cpp",
        "%{VendorPaths.imgui}/backends/imgui_impl_opengl3.cpp",
    }

    includedirs
    {
        "%{Includes.imgui}",
        "%{Includes.imgui}/imgui",
        "%{Includes.glfw}"
    }
