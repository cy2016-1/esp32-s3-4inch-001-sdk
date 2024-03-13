idf_component_register(
    SRC_DIRS
        "."
        "gui"
        "gui/font"
        "gui/assert"
        "app"

    INCLUDE_DIRS
        "."
        "gui"
        "app"
    )

# spiffs_create_partition_image(storage ../spiffs FLASH_IN_PROJECT)

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")


