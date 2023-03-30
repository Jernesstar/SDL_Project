project "imgui"
    kind "StaticLib"
    language "C"

    targetdir ("%{wks.location}/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "%{VendorPaths.imgui}/*.h",
        "%{VendorPaths.imgui}/*.cpp",
    }

    includedirs
    {
        "%{VendorPaths.imgui}/include"
    }
