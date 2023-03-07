option(BUILD_UTILITIES "Build the utilities library" ON)

if (NOT BUILD_UTILITIES)
    return()
endif()

add_library(utilities util.cpp)

target_include_directories(utilities
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    )

# link our compiler flags interface library
target_link_libraries(utilities compiler_flags)

add_executable(utilities_example example.cpp)
target_link_libraries(utilities_example utilities compiler_flags)
