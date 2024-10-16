# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "AT_KRL_STRUCTS_autogen"
  "CMakeFiles\\AT_KRL_STRUCTS_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\AT_KRL_STRUCTS_autogen.dir\\ParseCache.txt"
  )
endif()
