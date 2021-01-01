# [build]
aux_source_directory(. MODULES_SOURCE_DIR)

aux_source_directory(../../utils/frame MODULES_SOURCE_DIR)

aux_source_directory(../../utils/imgui MODULES_SOURCE_DIR)

aux_source_directory(../../utils/tools MODULES_SOURCE_DIR)

link_libraries(biulabwidget)

add_library(simplemap SHARED ${MODULES_SOURCE_DIR})

include_directories(
    include
    ./
    ../../include
    ../MapEditor
    ../BiulabWidget
)

# [install]
install(TARGETS simplemap
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    PERMISSIONS OWNER_WRITE OWNER_EXECUTE OWNER_READ GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    ARCHIVE DESTINATION bin
)

install(DIRECTORY .
    DESTINATION include
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hh"
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ GROUP_WRITE WORLD_READ
)