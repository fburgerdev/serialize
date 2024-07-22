-- premake5.lua
ROOT = ".."

-- workspace
workspace "serialize"
   -- startproject
   startproject "error"
   -- cpp
   language "C++"
   cppdialect "C++20"

   -- debug
   debugger "GDB"

   -- defines
   defines { "BEAVER_LOGGING",  }

   -- dependancies
   -- :: directories
   libdirs {
      ROOT .. "/lib/%{cfg.buildcfg}",
      ROOT .. "/modules/*/lib/%{cfg.buildcfg}",
      ROOT .. "/vendor/*/lib/%{cfg.buildcfg}"
   }
   -- :: libraries
   links { "beaver",  --[[ INSERT ADDITIONAL LINKS HERE ]] }

   -- config
   configurations { "debug", "release", "dist" }
   -- :: debug
   filter "configurations:debug"
      symbols "On"
      defines { "CONFIG_DEBUG" }
      -- precompiled headers
      pchheader "common.hpp"
      pchsource "common.cpp"
   -- :: release
   filter "configurations:release"
      optimize "On"
      defines { "CONFIG_RELEASE" }
      linkoptions{ "-Ofast" }
   -- :: dist
   filter "configurations:dist"
      optimize "On"
      defines { "CONFIG_DIST" }
      linkoptions { "-Ofast" }
   
   -- system
   -- :: windows
   filter "system:windows"
      defines { "SYSTEM_WINDOWS" }
   -- :: linux
   filter "system:linux"
      defines { "SYSTEM_LINUX" }
   
   -- toolset
   -- :: gcc
   filter "toolset:gcc"
      buildoptions { "-Wall", "-Wextra", "-Wpedantic" }

-- project lib
project "serialize"
   -- static library
   kind "StaticLib"

   -- include
   includedirs {
      ROOT,
      ROOT .. "/src",
      ROOT .. "/modules/*/include",
      ROOT .. "/vendor/*/include"
   }
   -- files
   files {
      ROOT .. "/src/**",
      ROOT .. "/vendor/*/src/**",
   }
   
   -- binaries
   targetdir(ROOT .. "/lib/%{cfg.buildcfg}")
   objdir(ROOT .. "/bin/%{cfg.system}_%{cfg.buildcfg}")
-- tests :: error
project "error"
   -- console
   kind "ConsoleApp"

   -- include
   includedirs {
      ROOT .. "/include",
      ROOT .. "/src",
      ROOT .. "/modules/*/include",
      ROOT .. "/vendor/*/include"
   }
   -- files
   files {
      ROOT .. "/tests/error.cpp",
      --[[ INSERT ADDITIONAL FILES HERE ]]
   }

   -- defines
   defines { "BEAVER_LOGGING" }

   -- libraries
   links { "serialize", "beaver",  --[[ INSERT ADDITIONAL LINKS HERE ]] }

   -- binaries
   targetdir(ROOT .. "/bin/tests/%{cfg.system}_%{cfg.buildcfg}")
   objdir(ROOT .. "/bin/tests/%{cfg.system}_%{cfg.buildcfg}/obj")