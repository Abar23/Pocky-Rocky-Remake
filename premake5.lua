workspace "Pocky-Rocky-Remake"
    architecture "x86_64"
    startproject "Pocky-Rocky-Remake"

    configurations
    {
        "Debug",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    outputDir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

    vendorIncludes = {}
    vendorIncludes["Glad"] = "./vendor/glad/include"
    vendorIncludes["GLFW"] = "./vendor/GLFW/include"
    vendorIncludes["stb_image"] = "./vendor/stb/"
    
    group "Dependencies"
        include "./vendor/Glad"
        include "./vendor/GLFW"

    project "Pocky-Rocky-Remake"
        location "."
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        staticruntime "on"
        
        targetdir ("./build/bin/" .. outputDir .. "/%{prj.name}")
        objdir ("./build/obj/" .. outputDir .. "/%{prj.name}")

        files
        {
            "./src/**.cpp",
            "./src/**.h",
            "./src/**.inl",
            "./vendor/stb/stb_image/**.h"
        }

        defines
        {
            "_USE_MATH_DEFINES",
            "_USE_MATH_DEFINES",
            "GLFW_INCLUDE_NONE"
        }

        includedirs
        {
            "%{wks.name}/src",
            "%{vendorIncludes.Glad}",
            "%{vendorIncludes.GLFW}",
            "%{vendorIncludes.stb_image}"
        }

        links
        {
            "GLFW",
            "Glad",
            "opengl32.lib"
        }

        filter "system:windows"
            systemversion "latest"

        filter "configurations:Debug"
            runtime "Debug"
            symbols "On"

            defines
            {
                "DEBUG"
            }

        filter "configurations:Release"
            runtime "Release"
            optimize "On"