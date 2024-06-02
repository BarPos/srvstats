cmake_minimum_required (VERSION 3.8)

project ("srvstats")

SET(CMAKE_CXX_STANDARD 20)

add_executable("srvstats")

target_include_directories("srvstats" PRIVATE "${CMAKE_SOURCE_DIR}/src/" "${CMAKE_SOURCE_DIR}/external/asio/include")

if (WIN32)
    target_compile_definitions("srvstats" PRIVATE "_WINDOWS")
endif (WIN32)
if (UNIX)
    target_compile_definitions("srvstats" PRIVATE "_LINUX")
    target_link_libraries("srvstats" PRIVATE "pthread")
endif (UNIX)

add_custom_command(TARGET "srvstats" POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "${CMAKE_SOURCE_DIR}/src/index.html"
     "${CMAKE_BINARY_DIR}/index.html" 
  COMMENT "Copying index to output directory")

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/**.cpp")
target_sources("srvstats" PRIVATE "${APP_SOURCES}")
