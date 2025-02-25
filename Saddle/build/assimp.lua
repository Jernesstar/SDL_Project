project "assimp"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    targetdir ("%{wks.location}/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        -- "%{VendorPaths.assimp}/code/CApi/*.cpp",
        "%{VendorPaths.assimp}/code/Common/*.cpp",
        "%{VendorPaths.assimp}/code/Geometry/*.cpp",
        "%{VendorPaths.assimp}/code/Material/*.cpp",
        "%{VendorPaths.assimp}/code/Pbrt/*.cpp",
        "%{VendorPaths.assimp}/code/PostProcessing/*.cpp",
        "%{VendorPaths.assimp}/code/AssetLib/Obj/*.cpp",
        -- "%{VendorPaths.assimp}/code/AssetLib/STL/*.cpp",
        -- "%{VendorPaths.assimp}/code/AssetLib/FBX/*.cpp",
        -- "%{VendorPaths.assimp}/code/AssetLib/Blender/*.cpp",
        -- "%{VendorPaths.assimp}/code/AssetLib/Unreal/*.cpp",
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
        "%{VendorPaths.assimp}/code/**Export*.cpp",
        "%{VendorPaths.assimp}/code/Common/*Exporter*.cpp",
        "%{VendorPaths.assimp}/code/Common/Exporter.cpp",
        "%{VendorPaths.assimp}/code/AssetLib/Obj/ObjExporter.cpp",
        "%{VendorPaths.assimp}/code/AssetLib/STL/STLExporter.cpp",
        "%{VendorPaths.assimp}/code/AssetLib/FBX/FBXExporter.cpp",
        "%{VendorPaths.assimp}/code/AssetLib/FBX/FBXExportNode.cpp",
        "%{VendorPaths.assimp}/code/AssetLib/FBX/FBXExportProperty.cpp",
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

    buildoptions
    {
        -- "-fvisibility=hidden",
        -- "-fno-strict-aliasing",
        -- "-Wall",
        "-W",
        -- "-Wno",
        "-long-long",
        -- "-Wa,-mbig-obj",
        "-O3",
        -- "-fsanitize=address",
        -- "-fsanitize=undefined,shift,shift-exponent,integer-divide-by-zero,unreachable,vla-bound,null,return,signed-integer-overflow,bounds,float-divide-by-zero,float-cast-overflow,nonnull-attribute,returns-nonnull-attribute,bool,enum,vptr,pointer-overflow,builtin",
        -- "-fno-sanitize-recover=all"
    }

    links
    {
        "zlib",
        -- "asan"
    }

    defines
    {
        "ASSIMP_NO_EXPORT",
        "ASSIMP_BUILD_RELEASE",
        "WIN32_LEAN_AND_MEAN",
        'ASSIMP_BUILD_COMPILER="g++"',

        "ASSIMP_BUILD_NO_3D_IMPORTER",
        "ASSIMP_BUILD_NO_3DS_IMPORTER",
        "ASSIMP_BUILD_NO_3MF_IMPORTER",
        "ASSIMP_BUILD_NO_AC_IMPORTER",
        "ASSIMP_BUILD_NO_AC3D_IMPORTER",
        "ASSIMP_BUILD_NO_ACC_IMPORTER",
        "ASSIMP_BUILD_NO_ASSBIN_IMPORTER",
        "ASSIMP_BUILD_NO_AMJ_IMPORTER",
        "ASSIMP_BUILD_NO_AMF_IMPORTER",
        "ASSIMP_BUILD_NO_ASE_IMPORTER",
        "ASSIMP_BUILD_NO_ASK_IMPORTER",
        "ASSIMP_BUILD_NO_B3D_IMPORTER",
        "ASSIMP_BUILD_NO_BLEND_IMPORTER",
        "ASSIMP_BUILD_NO_BVH_IMPORTER",
        "ASSIMP_BUILD_NO_C4D_IMPORTER",
        "ASSIMP_BUILD_NO_CSM_IMPORTER",
        "ASSIMP_BUILD_NO_COB_IMPORTER",
        "ASSIMP_BUILD_NO_COLLADA_IMPORTER",
        "ASSIMP_BUILD_NO_DXF_IMPORTER",
        "ASSIMP_BUILD_NO_ENFF_IMPORTER",
        "ASSIMP_BUILD_NO_FBX_IMPORTER",
        "ASSIMP_BUILD_NO_GLTF_IMPORTER",
        "ASSIMP_BUILD_NO_HMP_IMPORTER",
        "ASSIMP_BUILD_NO_IFC_IMPORTER",
        "ASSIMP_BUILD_NO_IQM_IMPORTER",
        "ASSIMP_BUILD_NO_IRR_IMPORTER",
        "ASSIMP_BUILD_NO_IRRMESH_IMPORTER",
        "ASSIMP_BUILD_NO_LWO_IMPORTER",
        "ASSIMP_BUILD_NO_LWS_IMPORTER",
        "ASSIMP_BUILD_NO_LXO_IMPORTER",
        "ASSIMP_BUILD_NO_M3D_IMPORTER",
        "ASSIMP_BUILD_NO_MD2_IMPORTER",
        "ASSIMP_BUILD_NO_MD3_IMPORTER",
        "ASSIMP_BUILD_NO_MD4_IMPORTER",
        "ASSIMP_BUILD_NO_MD5_IMPORTER",
        "ASSIMP_BUILD_NO_MDC_IMPORTER",
        "ASSIMP_BUILD_NO_MDL_IMPORTER",
        "ASSIMP_BUILD_NO_MMD_IMPORTER",
        "ASSIMP_BUILD_NO_MESH_IMPORTER",
        "ASSIMP_BUILD_NO_MOT_IMPORTER",
        "ASSIMP_BUILD_NO_MS3D_IMPORTER",
        "ASSIMP_BUILD_NO_NDO_IMPORTER",
        "ASSIMP_BUILD_NO_NFF_IMPORTER",
        -- "ASSIMP_BUILD_NO_OBJ_IMPORTER",
        "ASSIMP_BUILD_NO_OFF_IMPORTER",
        "ASSIMP_BUILD_NO_OGRE_IMPORTER",
        "ASSIMP_BUILD_NO_OPENGEX_IMPORTER",
        "ASSIMP_BUILD_NO_PLY_IMPORTER",
        "ASSIMP_BUILD_NO_PMX_IMPORTER",
        "ASSIMP_BUILD_NO_PRJ_IMPORTER",
        "ASSIMP_BUILD_NO_Q3D_IMPORTER",
        "ASSIMP_BUILD_NO_Q3BSP_IMPORTER",
        "ASSIMP_BUILD_NO_RAW_IMPORTER",
        "ASSIMP_BUILD_NO_SCN_IMPORTER",
        "ASSIMP_BUILD_NO_SIB_IMPORTER",
        "ASSIMP_BUILD_NO_SMD_IMPORTER",
        "ASSIMP_BUILD_NO_STP_IMPORTER",
        "ASSIMP_BUILD_NO_STL_IMPORTER",
        "ASSIMP_BUILD_NO_TERRAGEN_IMPORTER",
        "ASSIMP_BUILD_NO_UC_IMPORTER",
        "ASSIMP_BUILD_NO_VTA_IMPORTER",
        "ASSIMP_BUILD_NO_X_IMPORTER",
        "ASSIMP_BUILD_NO_X3D_IMPORTER",
        "ASSIMP_BUILD_NO_XGL_IMPORTER",
        "ASSIMP_BUILD_NO_ZGL_IMPORTER",
    }

    filter "system:windows"
        systemversion "latest"
