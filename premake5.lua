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
         
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
