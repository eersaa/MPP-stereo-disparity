option(BUILD_TESTS "Build tests" ON)

if(NOT BUILD_TESTS)
    return()
endif(NOT BUILD_TESTS)

add_executable(stopwatches_tests Stopwatches_tests.cpp)
target_link_libraries(stopwatches_tests PRIVATE GTest::gtest_main stopwatches compiler_flags)    
list(APPEND TESTS stopwatches_tests)

add_executable(ocl_grayscale_tests ocl_grayscale_tests.cpp)
target_link_libraries(ocl_grayscale_tests PRIVATE GTest::gtest_main opencl_base compiler_flags)
list(APPEND TESTS ocl_grayscale_tests)

# Add OpenCL kernel file to the target
set_source_files_properties(grayscale.cl PROPERTIES HEADER_ONLY TRUE)
add_custom_target(grayscale_kernel_header DEPENDS grayscale.cl)
add_dependencies(ocl_grayscale_tests grayscale_kernel_header)

# Copy OpenCL kernel file to the binary directory
add_custom_command(
    TARGET ocl_grayscale_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/grayscale.cl
    ${CMAKE_CURRENT_BINARY_DIR}/grayscale.cl
    )

include(GoogleTest)

foreach(TEST ${TESTS})
    gtest_discover_tests(${TEST})
endforeach(TEST)
