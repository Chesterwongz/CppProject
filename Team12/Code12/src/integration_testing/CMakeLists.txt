file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/" *.h *.hpp)
add_executable(integration_testing ${srcs} ${headers})


target_link_libraries(integration_testing spa)
