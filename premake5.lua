include "./vendor/premake/premake_customization/clean_build.lua"

workspace "Spike"
    architecture "x86_64"
    startproject "Spike-Editor"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
    flags
    {
        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Spike/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Spike/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Spike/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Spike/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Spike/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/Spike/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/Spike/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/Spike/vendor/ImGuizmo"
IncludeDir["Assimp"] = "%{wks.location}/Spike/vendor/assimp/include"
IncludeDir["box2D"] = "%{wks.location}/Spike/vendor/box2D/include"
IncludeDir["mono"] = "%{wks.location}/Spike/vendor/mono/include"
IncludeDir["FontAwesome"] = "%{wks.location}/Spike-Editor/src"

LibraryDir = {}
LibraryDir["mono"] = "%{wks.location}/Spike/vendor/mono/lib/Debug/mono-2.0-sgen.lib"
LibraryDir["Assimp"] = "%{wks.location}/Spike/vendor/assimp/lib/assimp-vc142-mt.lib"

group "Dependencies"
    include "Spike/vendor/GLFW"
    include "Spike/vendor/Glad"
    include "Spike/vendor/imgui"
    include "Spike/vendor/yaml-cpp"
    include "Spike/vendor/box2D"
group ""

include "Spike"
include "Sandbox"
include "Spike-Editor"

project "Spike-ScriptCore"
    location "Spike-ScriptCore"
    kind "SharedLib"
    language "C#"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.cs",
    }