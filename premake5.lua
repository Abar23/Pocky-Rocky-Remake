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
    
    group "Dependencies"
        include "./vendor/Glad"
        include "./vendor/GLFW"
        include "./vendor/ImGui"
    group ""

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
        }

        defines
        {
            "_USE_MATH_DEFINES",
            "_USE_MATH_DEFINES",
            "GLFW_INCLUDE_NONE",
            "STB_IMAGE_IMPLEMENTATION"
        }

        includedirs
        {
            "./src",
            "./vendor/glad/include",
            "./vendor/GLFW/include",
            "./vendor/OpenAL/include",
            "./vendor/imgui/include",
            "./vendor/dr_libs/include",
            "./vendor/stb/include"
        }

        links
        {
            "GLFW",
            "Glad",
            "ImGui",
            "opengl32.lib"
        }

        filter "system:windows"
            systemversion "latest"

            filter "configurations:Debug"
                
            filter { "system:windows" }
                
                prebuildcommands 
                { 
                    "copy \"$(ProjectDir)\\vendor\\OpenAL\\libs\\Win64\\Debug\\*.dll\" \"$(ProjectDir)$(OutDir)\"" 
                }

                links   
                {
                    "./vendor/OpenAL/libs/Win64/Debug/OpenAL32.lib"
                }

            
            filter "configurations:Release"

                prebuildcommands 
                { 
                    "copy \"$(ProjectDir)\\vendor\\OpenAL\\libs\\Win64\\Release\\*.dll\" \"$(ProjectDir)$(OutDir)\"" 
                }

                links   
                {
                    "./vendor/OpenAL/libs/Win64/Release/OpenAL32.lib"
                }

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