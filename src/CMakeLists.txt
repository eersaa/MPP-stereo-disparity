add_subdirectory(Stopwatches)

# Add LodePNG without editing the git submodule
add_library(lodepng STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/lodepng/lodepng.cpp
  )

target_include_directories(lodepng 
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/lodepng
  )

add_subdirectory(lodepng_wrapper)
add_subdirectory(utilities)

add_executable(application main.cpp)
target_link_libraries(application
  PRIVATE
  lodepng_wrapper
  utilities
  )
