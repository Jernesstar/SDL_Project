project "assimp"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir ("%{wks.location}/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "%{VendorPaths.assimp}/code/",
        "%{VendorPaths.assimp}/code/CApi/*.cpp",
        "%{VendorPaths.assimp}/code/Common/*.cpp",
        "%{VendorPaths.assimp}/code/Geometry/*.cpp",
        "%{VendorPaths.assimp}/code/Material/*.cpp",
        "%{VendorPaths.assimp}/code/Pbrt/*.cpp",
        "%{VendorPaths.assimp}/code/PostProcessing/*.cpp",
        "%{VendorPaths.assimp}/code/AssetLib/Obj/*.cpp",
        "%{VendorPaths.assimp}/code/AssetLib/STL/*.cpp",
        "%{VendorPaths.assimp}/code/AssetLib/FBX/*.cpp",
        "%{VendorPaths.assimp}/code/AssetLib/Blender/*.cpp",
        "%{VendorPaths.assimp}/code/AssetLib/Unreal/*.cpp",
        "%{VendorPaths.assimp}/contrib/clipper/**.cpp",
        "%{VendorPaths.assimp}/contrib/gtest/**.cpp",
        "%{VendorPaths.assimp}/contrib/Open3DGC/**.cpp",
        "%{VendorPaths.assimp}/contrib/openddlparser/**.cpp",
        "%{VendorPaths.assimp}/contrib/poly2tri/**.cpp",
        "%{VendorPaths.assimp}/contrib/pugixml/**.cpp",
        "%{VendorPaths.assimp}/contrib/unzip/**.c",
        "%{VendorPaths.assimp}/contrib/zip/**.c",
    }

    removefiles
    {
        "%{VendorPaths.assimp}/code/AssetLib/Obj/ObjExporter.cpp",
        "%{VendorPaths.assimp}/code/AssetLib/STL/STLExporter.cpp",
        "%{VendorPaths.assimp}/code/AssetLib/FBX/FBXExporter.cpp",
        "%{VendorPaths.assimp}/code/AssetLib/FBX/FBXExporteNode.cpp",
        "%{VendorPaths.assimp}/code/AssetLib/FBX/FBXExporteProperty.cpp",
    }

    includedirs
    {
        "%{Includes.assimp}",
        "%{VendorPaths.assimp}",
        "%{VendorPaths.assimp}/code",
        "%{VendorPaths.assimp}/contrib",
        "%{VendorPaths.assimp}/contrib/unzip",
        "%{VendorPaths.assimp}/contrib/zip/src",
        "%{VendorPaths.assimp}/contrib/pugixml/src",
        "%{VendorPaths.assimp}/contrib/rapidjson/include",
        "%{VendorPaths.assimp}/contrib/utf8cpp/source/utf8",
        "%{VendorPaths.assimp}/contrib/openddlparser/include",
    }

    defines
    {
        "ASSIMP_NO_EXPORT",
        "ASSIMP_ASAN=OFF",
        "ASSIMP_UBSAN=OFF",
        "ASSIMP_BUILD_RELEASE",
        "ASSIMP_BUILD_NO_M3D_IMPORTER",
        "ASSIMP_BUILD_NO_M3D_EXPORTER",
        "ASSIMP_BUILD_NO_C4D_IMPORTER",
        "ASSIMP_BUILD_NO_C4D_EXPORTER",
        "WIN32_LEAN_AND_MEAN",
        "ASSIMP_BUILD_COMPILER=\"g++\""
    }

    buildoptions
    {
        "-fvisibility=hidden",
        "-fno-strict-aliasing",
        "-Wall",
        "-Wno",
        "-long-long",
        "-mbig-obj", -- -Wa
        "-O3",
        "-fsanitize=address",
        "-fsanitize=undefined,shift,shift-exponent,integer-divide-by-zero,unreachable,vla-bound,null,return,signed-integer-overflow,bounds,float-divide-by-zero,float-cast-overflow,nonnull-attribute,returns-nonnull-attribute,bool,enum,vptr,pointer-overflow,builtin",
        "-fno-sanitize-recover=all"
    }

    links
    {
        "zlib",
        "asan"
    }

    filter "system:windows"
        systemversion "latest"
