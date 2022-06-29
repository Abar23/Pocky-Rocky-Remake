project "ImGui"
	kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

	targetdir ("./build/bin/" .. outputDir .. "/%{prj.name}")
	objdir ("./build/obj/" .. outputDir .. "/%{prj.name}")

	files
	{
		"include/ImGui/imconfig.h",
		"include/ImGui/imstb_rectpack.h",
		"include/ImGui/imstb_textedit.h",
		"include/ImGui/imstb_truetype.h",
		"include/ImGui/imgui_internal.h",
		"include/ImGui/imgui.h",
		"imgui.cpp",
		"imgui_draw.cpp",
		"imgui_widgets.cpp",
		"imgui_tables.cpp",
		"imgui_demo.cpp"
	}

	filter "system:windows"
		systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"