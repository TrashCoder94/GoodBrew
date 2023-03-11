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
	filter ""
	filter "configurations:Release"
		defines
		{
			"GB_RELEASE",
			"BX_CONFIG_DEBUG=0"
		}
		runtime "Release"
		optimize "on"
	filter ""
	filter "configurations:Distribution"
		defines
		{
			"GB_DISTRIBUTION",
			"BX_CONFIG_DEBUG=0"
		}
		runtime "Release"
		optimize "on"
	filter ""
	
	filter "platforms:x86"
		architecture "x86"
	filter ""
	filter "platforms:x86_64"
		architecture "x86_64"
	filter ""
	filter "system:windows"
		toolset "v143"
		buildoptions { "/Zc:__cplusplus" }
	filter ""
	filter "system:macosx"
		xcodebuildsettings {
			["MACOSX_DEPLOYMENT_TARGET"] = "10.9",
			["ALWAYS_SEARCH_USER_PATHS"] = "YES",
		};
	filter ""

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
IncludeDir["spdlog"] = "%{wks.location}/GBEngine/ThirdParty/spdlog/include"

IncludeDir["GBEngine"] = "%{wks.location}/GBEngine/Source"

function setBxCompat()
	filter "action:vs*"
		includedirs { "%{IncludeDir.bxCompatMSVC}" }
	filter ""
	filter { "system:windows", "action:gmake" }
		includedirs { "%{IncludeDir.bxCompatMingW}" }
	filter ""
	filter { "system:macosx" }
		includedirs { "%{IncludeDir.bxCompatOSX}" }
		buildoptions { "-x objective-c++" }
	filter ""
end

function includeAndLinkGBEngineLibraryFiles()
	includedirs
	{
		"%{IncludeDir.bgfx}",
		"%{IncludeDir.bx}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GBEngine}"
	}

	postbuildmessage "Copying engine assets to project assets and binaries folder!"

	if os.host() == "windows" then
		links { "GBEngine" }

		postbuildcommands
		{
			"{COPY} %{wks.location}/GBEngine/Assets %{prj.location}/Assets",
			"{COPY} %{prj.location}Assets %{cfg.targetdir}/Assets"
		}
	else
		absolutePathForWorkspaceLocation = path.getabsolute("%{wks.location}")
		absolutePathForProjectLocation = path.getabsolute("%{prj.location}")
		
		-- might have to use -R instead for mac specifically...
		-- dir=$(pwd)
		-- echo "$dir"
		postbuildcommands
		{
			"dir=$(pwd)",
			"pwd",
			"echo $pwd",
			"echo \"$dir\"",
			"chmod o+rx /$dir/../../GBEngine/Assets",
			"chmod o+rx /$dir/Assets",
			"cp -R /$dir/../../GBEngine/Assets/. /$dir/Assets/.",
			"cp -R /$dir/Assets/. /$dir/../../%{cfg.targetdir}/Assets/."
		}
		
		-- cp: cannot stat '/../../GBEngine/Assets/.': No such file or directory
		-- /home/runner/work/GoodBrew/GoodBrew/Examples/Sandbox
		-- cp -a /source/. /dest/
	
		links { "GBEngine", "bgfx", "bimg", "bx", "glfw", "ImGui" }
			
		filter "system:windows"
			links { "gdi32", "kernel32", "psapi" }
		filter ""
		
		filter "system:linux"
			links { "dl", "GL", "pthread", "X11" }
		filter ""
		
		filter "system:macosx"
			links { "QuartzCore.framework", "Metal.framework", "Cocoa.framework", "IOKit.framework", "CoreVideo.framework", "CoreGraphics.framework" }
		filter ""
	end
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
	include "Examples/Sandbox"
group ""

group "GB"
	include "Tests/BuildMachine"
	include "GBEngine"
group ""