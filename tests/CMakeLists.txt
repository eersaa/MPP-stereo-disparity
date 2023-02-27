option(BUILD_TESTS "Build tests" ON)

if(NOT BUILD_TESTS)
    return()
endif(NOT BUILD_TESTS)

add_executable(stopwatches_tests Stopwatches_tests.cpp)
target_link_libraries(stopwatches_tests PRIVATE GTest::gtest_main stopwatches compiler_flags)    
list(APPEND TESTS stopwatches_tests)

include(GoogleTest)

foreach(TEST ${TESTS})
    gtest_discover_tests(${TEST})
endforeach(TEST)
