project "glfw"
    kind "StaticLib"
    language "C"

    targetdir ("%{wks.location}/bin")
    objdir ("%{wks.location}/obj")

    files
    {
        "%{VendorPaths.glfw}/include/GLFW/glfw3.h",
        "%{VendorPaths.glfw}/include/GLFW/glfw3native.h",
        "%{VendorPaths.glfw}/src/internal.h",
        "%{VendorPaths.glfw}/src/platform.h",
        "%{VendorPaths.glfw}/src/mappings.h",
        "%{VendorPaths.glfw}/src/context.c",
        "%{VendorPaths.glfw}/src/init.c",
        "%{VendorPaths.glfw}/src/input.c",
        "%{VendorPaths.glfw}/src/monitor.c",
        "%{VendorPaths.glfw}/src/platform.c",
        "%{VendorPaths.glfw}/src/vulkan.c",
        "%{VendorPaths.glfw}/src/window.c",
        "%{VendorPaths.glfw}/src/null_platform.h",
        "%{VendorPaths.glfw}/src/null_joystick.h",
        "%{VendorPaths.glfw}/src/null_init.c",
        "%{VendorPaths.glfw}/src/null_monitor.c",
        "%{VendorPaths.glfw}/src/null_window.c",
        "%{VendorPaths.glfw}/src/null_joystick.c",
    }

    includedirs
    {
        "%{VendorPaths.glfw}/src"
    }

    filter "system:windows"
        systemversion "latest"
    
        files
        {
            "%{VendorPaths.glfw}/src/win32_init.c",
            "%{VendorPaths.glfw}/src/win32_module.c",
            "%{VendorPaths.glfw}/src/win32_joystick.c",
            "%{VendorPaths.glfw}/src/win32_monitor.c",
            "%{VendorPaths.glfw}/src/win32_time.h",
            "%{VendorPaths.glfw}/src/win32_time.c",
            "%{VendorPaths.glfw}/src/win32_thread.h",
            "%{VendorPaths.glfw}/src/win32_thread.c",
            "%{VendorPaths.glfw}/src/win32_window.c",
            "%{VendorPaths.glfw}/src/wgl_context.c",
            "%{VendorPaths.glfw}/src/egl_context.c",
            "%{VendorPaths.glfw}/src/osmesa_context.c"
        }

        defines 
        { 
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }
