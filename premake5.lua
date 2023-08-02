require "cmake"

workspace "learnOpenGL"
   configurations { "Debug", "Release" }

local srcDir = "src/"
local macLibPath = "deps/lib_mac/"
local winLibPath = "deps/lib_win/"
local linLibPath = "deps/lib_linux/"
local includePath = "deps/include/"

project "hellOpenGL"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"
   architecture "x64"

   files {  srcDir .. "**.h",
            srcDir .."**.c",
            srcDir .. "**.cpp" 
   }
   
   includedirs { includePath }

   if os.host() == "macosx" then
      links {  
         "glfw3",
         "OpenGL.framework",
         "Cocoa.framework",
         "IOKit.framework"
      }
      
      libdirs {
         macLibPath
      }
   end
   
   if os.host() == "windows" then
      characterset ("MBCS")
      links {
         "glfw3",
         "opengl32"
      }

      libdirs {
         winLibPath
      }
   end

   if os.host() == "linux" then
      links {
         "glfw3",
         "gl"
      }
      libdirs {
         linLibPath
      }
   end

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
