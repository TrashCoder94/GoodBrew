project "GBEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++14"
	staticruntime "on"

	targetdir ("%{wks.location}/Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/Intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "gbpch.h"
	pchsource "Source/gbpch.cpp"

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
		"%{IncludeDir.bx}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.imgui}"
	}

	links { "bgfx", "bimg", "bx", "glfw", "ImGui" }

	filter "system:windows"
		links { "gdi32", "kernel32", "psapi" }
	
	filter "system:linux"
		links { "dl", "GL", "pthread", "X11" }
	
	filter "system:macosx"
		links { "QuartzCore.framework", "Metal.framework", "Cocoa.framework", "IOKit.framework", "CoreVideo.framework", "CoreGraphics.framework" }
	setBxCompat()
	