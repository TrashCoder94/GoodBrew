project "Shared"
	kind "Utility"
	
	targetdir ("%{wks.location}/Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/Intermediate/" .. outputdir .. "/%{prj.name}")
	
	includedirs
	{
		"%{IncludeDir.GBEngine}",
		"%{IncludeDir.bgfx}",
		"%{IncludeDir.bx}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.spdlog}"
	}
	
	links { "bgfx", "bimg", "bx", "glfw", "ImGui" }
