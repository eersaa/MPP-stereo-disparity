option(BUILD_RUNTIMER "Build the runtimer library" ON)

if (NOT BUILD_RUNTIMER)
    return()
endif()

add_library(runtimer runtimer.cpp)

target_include_directories(runtimer
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(runtimer_example example.cpp)
target_link_libraries(runtimer_example runtimer)

# link our compiler flags interface library
target_link_libraries(runtimer compiler_flags)
