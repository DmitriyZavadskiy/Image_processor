add_library(
    bmp
    dumper.cpp
    loader.cpp
)

target_link_libraries(
    bmp
    image
)