add_library(image image.cpp color.cpp)
target_include_directories(image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
