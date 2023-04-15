option(BUILD_TESTS "Build tests" ON)

if(NOT BUILD_TESTS)
    return()
endif(NOT BUILD_TESTS)

add_executable(stopwatches_tests Stopwatches_tests.cpp)
target_link_libraries(stopwatches_tests PRIVATE GTest::gtest_main stopwatches compiler_flags)    
list(APPEND TESTS stopwatches_tests)

add_executable(ocl_grayscale_tests ocl_grayscale_tests.cpp)
target_link_libraries(ocl_grayscale_tests PRIVATE GTest::gtest_main opencl_base lodepng_wrapper compiler_flags)
list(APPEND TESTS ocl_grayscale_tests)

# Add OpenCL kernel file to the target
set_source_files_properties(grayscale.cl PROPERTIES HEADER_ONLY TRUE)
add_custom_target(grayscale_kernel_header DEPENDS grayscale.cl 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/grayscale.cl
    ${CMAKE_CURRENT_BINARY_DIR}/grayscale.cl)
add_dependencies(ocl_grayscale_tests grayscale_kernel_header)

add_executable(cross_checking_tests cross_checking_tests.cpp)
target_link_libraries(cross_checking_tests PRIVATE GTest::gtest_main utilities compiler_flags)
list(APPEND TESTS cross_checking_tests)

add_executable(occlusion_fill_tests occlusion_fill_tests.cpp)
target_link_libraries(occlusion_fill_tests PRIVATE occlusion_fill GTest::gtest_main compiler_flags)
list(APPEND TESTS occlusion_fill_tests)

include(GoogleTest)

foreach(TEST ${TESTS})
    gtest_discover_tests(${TEST})
endforeach(TEST)
