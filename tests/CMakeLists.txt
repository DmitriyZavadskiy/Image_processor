add_catch(test_affine_tile test_affine_tile.cpp)

target_link_libraries(
    test_affine_tile
    filters
)

add_catch(test_blur test_blur.cpp)

target_link_libraries(
    test_blur
    filters
)

add_catch(test_crop test_crop.cpp)

target_link_libraries(
    test_crop
    filters
)

add_catch(test_edge test_edge.cpp)

target_link_libraries(
    test_edge
    filters
)

add_catch(test_sharpen test_sharpen.cpp)

target_link_libraries(
    test_sharpen
    filters
)

add_catch(test_grayscale test_grayscale.cpp)

target_link_libraries(
    test_grayscale
    filters
)

add_catch(test_neg test_neg.cpp)

target_link_libraries(
    test_neg
    filters
)

add_catch(test_args test_args.cpp)

target_link_libraries(
    test_args
    args
)

add_catch(test_dumper test_dumper.cpp)

target_link_libraries(
    test_dumper
    bmp
)

add_catch(test_loader test_loader.cpp)

target_link_libraries(
    test_loader
    bmp
)
