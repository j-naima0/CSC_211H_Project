# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/college_mental_health_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/college_mental_health_autogen.dir/ParseCache.txt"
  "college_mental_health_autogen"
  )
endif()
