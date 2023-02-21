option(BUILD_TESTS "Build tests" ON)

if(NOT BUILD_TESTS)
    return()
endif(NOT BUILD_TESTS)

add_executable(runtimer_tests runtimer_tests.cpp)
target_link_libraries(runtimer_tests PRIVATE GTest::gtest_main runtimer compiler_flags)    
list(APPEND TESTS runtimer_tests)

include(GoogleTest)

foreach(TEST ${TESTS})
    gtest_discover_tests(${TEST})
endforeach(TEST)
