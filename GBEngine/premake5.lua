project "GBEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("%{wks.location}/Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"Source",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.spdlog}"
	}

	includeAndLinkSFML()

	filter { "system:windows" }
		pchheader "gbpch.h"
		pchsource "Source/gbpch.cpp"
	filter {}
	
	filter { "system:linux" }
		pchheader "gbpch.h"
		pchsource "Source/gbpch.cpp"
		excludes "Source/gbpch.h"
	filter {}
	