-- premake5.lua
ROOT = ".."
-- workspace
workspace "serialize"
   -- build options
   configurations { "debug", "release", "dist" }
   -- startproject
   startproject "ecs"
   -- cpp
   language "C++"
   cppdialect "C++Latest"
   -- debug
   debugger "GDB"
   -- defines
   defines {  }
   -- config
   -- :: debug
   filter "configurations:debug"
      symbols "On"
      defines { "CONFIG_DEBUG" }
   -- :: fast
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
-- project lib
project "serialize"
   -- static library
   kind "StaticLib"
   -- include directories
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
   -- precompiled headers
   pchheader "common.hpp"
   pchsource "common.cpp"
   -- binaries
   targetdir(ROOT .. "/lib/%{cfg.buildcfg}")
   objdir(ROOT .. "/bin/%{cfg.system}_%{cfg.buildcfg}")
-- tests :: ecs
project "ecs"
   -- console
   kind "ConsoleApp"
   -- include directories
   includedirs {
      ROOT .. "/include",
      ROOT .. "/src",
      ROOT .. "/modules/*/include",
      ROOT .. "/vendor/*/include"
   }
   -- library directories
   libdirs {
      ROOT .. "/lib/%{cfg.buildcfg}",
      ROOT .. "/modules/*/lib/%{cfg.buildcfg}",
      ROOT .. "/vendor/*/lib/%{cfg.buildcfg}"
   }
   -- files
   files {
      ROOT .. "/tests/ecs.cpp",  --[[ INSERT ADDITIONAL FILES HERE ]]
   }
   -- precompiled headers
   pchheader "common.hpp"
   pchsource "common.cpp"
   -- links
   links { "serialize",  --[[ INSERT ADDITIONAL LINKS HERE ]] }
   -- defines
   defines {  }
   -- binaries
   targetdir(ROOT .. "/bin/tests/%{cfg.system}_%{cfg.buildcfg}")
   objdir(ROOT .. "/bin/tests/%{cfg.system}_%{cfg.buildcfg}/obj")