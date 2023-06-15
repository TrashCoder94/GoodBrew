project "GBEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"%{IncludeDir.bgfx}",
		"%{IncludeDir.bimg}",
		"%{IncludeDir.bx}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.nanovg}"
	}

	links { "bgfx", "bimg", "bx", "glfw", "ImGui" }

	filter "files:ThirdParty/nanovg/**.cpp"
		flags { "NoPCH" }
	filter ""

	filter "system:windows"
		links { "gdi32", "kernel32", "psapi" }
		pchheader "gbpch.h"
		pchsource "Source/gbpch.cpp"
	filter ""
	
	filter "system:linux"
		links { "dl", "GL", "pthread", "X11" }
		pchheader "gbpch.h"
		pchsource "Source/gbpch.cpp"
	filter ""
	
	filter "system:macosx"
		links { "QuartzCore.framework", "Metal.framework", "Cocoa.framework", "IOKit.framework", "CoreVideo.framework", "CoreGraphics.framework" }
	filter ""
	
	setBxCompat()
	