include "./ThirdParty/premake/premake_customization/solution_items.lua"

workspace "GB"
	architecture "x86_64"
	startproject "BGFXHelloWorldTest"
	
	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

	if os.is64bit() and not os.host() == "windows" then
		platforms "x86_64"
	else
		platforms { "x86", "x86_64" }
	end

	if not os.host() == "macosx" then
		solution_items { ".editorconfig" }
	end

	flags
	{
		"MultiProcessorCompile"
	}
	
	linkoptions 
	{ 
		"-IGNORE:4006"
	}
	
	filter "configurations:Debug"
		defines
		{
			"GB_DEBUG",
			"BX_CONFIG_DEBUG=1"
		}
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines
		{
			"GB_RELEASE",
			"BX_CONFIG_DEBUG=0"
		}
		runtime "Release"
		optimize "on"
	filter "configurations:Distribution"
		defines
		{
			"GB_DISTRIBUTION",
			"BX_CONFIG_DEBUG=0"
		}
		runtime "Release"
		optimize "on"
		
	filter "platforms:x86"
		architecture "x86"
	filter "platforms:x86_64"
		architecture "x86_64"
	filter "system:windows"
		toolset "v143"
		buildoptions { "/Zc:__cplusplus" }
	filter "system:macosx"
		xcodebuildsettings {
			["MACOSX_DEPLOYMENT_TARGET"] = "10.9",
			["ALWAYS_SEARCH_USER_PATHS"] = "YES",
		};

-- Folder to put Binaries and Intermediate files into
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories
IncludeDir = {}
IncludeDir["bgfx"] = "%{wks.location}/GBEngine/ThirdParty/bgfx/include"
IncludeDir["bgfx3rdParty"] = "%{wks.location}/GBEngine/ThirdParty/bgfx/3rdparty"
IncludeDir["bgfx3rdPartydxsdk"] = "%{wks.location}/GBEngine/ThirdParty/bgfx/3rdparty/dxsdk/include"
IncludeDir["bgfx3rdPartyKhronos"] = "%{wks.location}/GBEngine/ThirdParty/bgfx/3rdparty/khronos"
IncludeDir["bimg"] = "%{wks.location}/GBEngine/ThirdParty/bimg/include"
IncludeDir["bimg3rdPartyAstcCodec"] = "%{wks.location}/GBEngine/ThirdParty/bimg/3rdparty/astc-codec"
IncludeDir["bimg3rdPartyAstcCodecInclude"] = "%{wks.location}/GBEngine/ThirdParty/bimg/3rdparty/astc-codec/include"
IncludeDir["bx"] = "%{wks.location}/GBEngine/ThirdParty/bx/include"
IncludeDir["bx3rdParty"] = "%{wks.location}/GBEngine/ThirdParty/bx/3rdparty"
IncludeDir["bxCompatMSVC"] = "%{wks.location}/GBEngine/ThirdParty/bx/include/compat/msvc"
IncludeDir["bxCompatMingW"] = "%{wks.location}/GBEngine/ThirdParty/bx/include/compat/mingw"
IncludeDir["bxCompatOSX"] = "%{wks.location}/GBEngine/ThirdParty/bx/include/compat/osx"
IncludeDir["glfw"] = "%{wks.location}/GBEngine/ThirdParty/glfw/include"
IncludeDir["imgui"] = "%{wks.location}/GBEngine/ThirdParty/imgui"

function setBxCompat()
	filter "action:vs*"
		includedirs { "%{IncludeDir.bxCompatMSVC}" }
	filter { "system:windows", "action:gmake" }
		includedirs { "%{IncludeDir.bxCompatMingW}" }
	filter { "system:macosx" }
		includedirs { "%{IncludeDir.bxCompatOSX}" }
		buildoptions { "-x objective-c++" }
end

group "Dependencies"
	include "ThirdParty/premake"
	include "GBEngine/ThirdParty/bgfx"
	include "GBEngine/ThirdParty/bimg"
	include "GBEngine/ThirdParty/bx"
	include "GBEngine/ThirdParty/glfw"
	include "GBEngine/ThirdParty/imgui"
group ""

group "Examples"
	include "Examples/BGFXHelloWorldTest"
group ""

group "GB"
	include "GBEngine"
group ""