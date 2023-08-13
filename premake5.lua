include "./ThirdParty/premake/premake_customization/solution_items.lua"

workspace "GB"
	architecture "x86_64"
	
	configurations
	{
		"Debug",
		"Release",
		"Shipping"
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
		"-IGNORE:4006,4099"
	}
	
	defines
	{
		"SFML_STATIC"
	}
	
	filter { "configurations:Debug" }
		defines
		{
			"GB_DEBUG",
			"GB_IMGUI_ENABLED"
		}
		runtime "Debug"
		symbols "on"
	filter {}
	filter { "configurations:Release" }
		defines
		{
			"GB_RELEASE",
			"GB_IMGUI_ENABLED"
		}
		runtime "Release"
		optimize "on"
	filter {}
	filter { "configurations:Shipping" }
		defines
		{
			"GB_SHIPPING",
			"GB_IMGUI_ENABLED"
		}
		runtime "Release"
		optimize "on"
	filter {}
	
	filter { "platforms:x86" }
		architecture "x86"
	filter {}
	filter { "platforms:x86_64" }
		architecture "x86_64"
	filter {}
	filter { "system:windows" }
		toolset "v143"
		buildoptions { "/Zc:__cplusplus" }
	filter {}
	filter { "system:macosx" }
		xcodebuildsettings {
			["MACOSX_DEPLOYMENT_TARGET"] = "10.9",
			["ALWAYS_SEARCH_USER_PATHS"] = "YES",
		};
	filter {}

-- Folder to put Binaries and Intermediate files into
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories
IncludeDir = {}
IncludeDir["SFMLWindows"] = "%{wks.location}/GBEngine/ThirdParty/SFML/Windows/include"
IncludeDir["SFMLMac"] = "%{wks.location}/GBEngine/ThirdParty/SFML/Mac/include"
IncludeDir["imgui"] = "%{wks.location}/GBEngine/ThirdParty/imgui"
IncludeDir["spdlog"] = "%{wks.location}/GBEngine/ThirdParty/spdlog/include"
IncludeDir["GBEngine"] = "%{wks.location}/GBEngine/Source"

function includeAndLinkSFML ()
	filter { "system:windows" }
		includedirs 
		{ 
			"%{IncludeDir.SFMLWindows}"
		}
		libdirs
		{
			"%{wks.location}/GBEngine/ThirdParty/SFML/Windows/lib"
		}
	filter {}
	
	filter { "system:windows", "configurations:Debug" }
		links
		{
			"sfml-graphics-s-d",
			"sfml-window-s-d",
			"sfml-audio-s-d",
			"sfml-network-s-d",
			"sfml-system-s-d",
			"opengl32",
			"freetype",
			"winmm",
			"gdi32",
			"openal32",
			"flac",
			"vorbisenc",
			"vorbisfile",
			"vorbis",
			"ogg",
			"ws2_32"
		}
	filter {}
	
	filter { "system:windows", "not configurations:Debug" }
		links
		{
			"sfml-graphics-s",
			"sfml-window-s",
			"sfml-audio-s",
			"sfml-network-s",
			"sfml-system-s",
			"opengl32",
			"freetype",
			"winmm",
			"gdi32",
			"openal32",
			"flac",
			"vorbisenc",
			"vorbisfile",
			"vorbis",
			"ogg",
			"ws2_32"
		}
	filter {}
	
	filter { "system:macosx" }
		includedirs 
		{ 
			"%{IncludeDir.SFMLMac}"
		}
		libdirs
		{
			"/Library/Frameworks"
		}
		links
		{
			"QuartzCore.framework", 
			"Metal.framework",
			"Cocoa.framework",
			"IOKit.framework",
			"CoreVideo.framework", 
			"CoreGraphics.framework",
			"OpenAL.framework",
			"FLAC.framework",
			"vorbisenc.framework",
			"vorbisfile.framework",
			"vorbis.framework",
			"ogg.framework",
			"sfml-graphics.framework",
			"sfml-window.framework",
			"sfml-audio.framework",
			"sfml-network.framework",
			"sfml-system.framework"
		}
		
		-- https://stackoverflow.com/questions/29465141/linking-mac-frameworks-using-premake-and-gnu-make
		-- Frameworks appear to need extra options for build/linking since premake doesn't automatically add them to the command line for compiling
		-- So you have to manually add these options in for now...
		-- Using /Library/Frameworks since that seems to be the standard place for all non system frameworks...
		buildoptions 
		{
			"-F /Library/Frameworks"
		}
		linkoptions 
		{
			"-F /Library/Frameworks"
		}
	filter {}
	
	filter { "system:linux" }
		links
		{
			"sfml-graphics",
			"sfml-window",
			"sfml-audio",
			"sfml-network",
			"sfml-system",
			"dl", 
			"GL", 
			"pthread", 
			"X11"
		}
	filter {}
end

function includeAndLinkGBEngine ()
	includeAndLinkSFML()
	
	includedirs
	{
		"%{IncludeDir.imgui}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GBEngine}"
	}
	links 
	{ 
		"GBEngine",
		"ImGui"
	}

	postbuildmessage "Copying engine assets to project assets and binaries folder!"

	filter { "system:windows" }
		postbuildcommands
		{
			"{COPY} %{wks.location}/GBEngine/Assets %{prj.location}/Assets",
			"{COPY} %{prj.location}Assets %{cfg.targetdir}/Assets"
		}
	filter {}

	filter { "system:macosx" }
		postbuildcommands
		{
			"cp -R /$(PWD)/GBEngine/Assets/. /$(CURDIR)/Assets/",
			"cp -R /$(CURDIR)/Assets/. /$(CURDIR)/%{cfg.targetdir}/Assets/"
		}
	filter {}

	filter { "system:linux" }
		postbuildcommands
		{
			"cp -R /$(PWD)/GBEngine/Assets/. /$(CURDIR)/Assets/",
			"cp -R /$(CURDIR)/Assets/. /$(CURDIR)/%{cfg.targetdir}/Assets/"
		}
	filter {}
end

group "Dependencies"
	include "ThirdParty/premake"
	include "GBEngine/ThirdParty/imgui"
group ""

group "Examples"
	include "Examples/Sandbox"
group ""

group "GB"
	include "GBEngine"
	include "GBEditor"
	include "GBLauncher"
group ""

group "GB/Tests"
	include "Tests/BootupAndShutdown"
group ""