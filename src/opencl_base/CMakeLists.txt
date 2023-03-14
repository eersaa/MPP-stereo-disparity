add_library(opencl_base opencl_base.cpp)

target_include_directories(opencl_base
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    )

target_link_libraries(opencl_base lodepng compiler_flags)
