project "BGFXHelloWorldTest"
	kind "ConsoleApp"
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
		"%{IncludeDir.bx}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.imgui}"
	}

	links { "GBEngine" }
	setBxCompat()
