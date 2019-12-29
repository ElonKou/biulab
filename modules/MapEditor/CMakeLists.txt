# [build]
aux_source_directory(. MODULES_SOURCE_DIR)

aux_source_directory(../../lib/frame MODULES_SOURCE_DIR)

aux_source_directory(../../lib/imgui MODULES_SOURCE_DIR)

aux_source_directory(../../lib/tools MODULES_SOURCE_DIR)

add_library(mapeditor SHARED ${MODULES_SOURCE_DIR})

include_directories(
    include
    ../Robbie
)

# [install]
install(TARGETS mapeditor
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    PERMISSIONS OWNER_WRITE OWNER_EXECUTE OWNER_READ GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    ARCHIVE DESTINATION lib
)

install(DIRECTORY .
    DESTINATION include
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hh"
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ GROUP_WRITE WORLD_READ
)