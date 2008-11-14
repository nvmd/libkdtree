project (libkdtree CXX)
cmake_minimum_required (VERSION 2.6.0)

if (WIN32)

   # Maximum warning level
   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")

   # Be strict about warnings... make them errors
   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")

   # Detect 64-bit portability issues
   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wp64")

else (WIN32)

   # Maximum warning level
   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

endif (WIN32)

include_directories (${PROJECT_SOURCE_DIR})

add_subdirectory(examples)
