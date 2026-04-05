# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/PlotTests_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/PlotTests_autogen.dir/ParseCache.txt"
  "CMakeFiles/TrigPlotter_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/TrigPlotter_autogen.dir/ParseCache.txt"
  "PlotTests_autogen"
  "TrigPlotter_autogen"
  )
endif()
