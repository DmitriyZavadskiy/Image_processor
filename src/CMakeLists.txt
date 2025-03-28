file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(imageproc_lib STATIC ${SOURCE_FILES})
target_include_directories(imageproc_lib PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
