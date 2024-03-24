idf_component_register(
    SRC_DIRS
    "."
    "gui_app"
    "gui_app/screens"
    "gui_app/images"
    "gui_app/fonts"
    INCLUDE_DIRS
    "include"
    )
spiffs_create_partition_image(storage ../spiffs FLASH_IN_PROJECT)


