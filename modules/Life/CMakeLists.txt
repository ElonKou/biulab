# [build]
aux_source_directory(. MODULES_SOURCE_DIR)

# aux_source_directory(../../utils/frame MODULES_SOURCE_DIR)

aux_source_directory(../../utils/imgui MODULES_SOURCE_DIR)

aux_source_directory(../../utils/tools MODULES_SOURCE_DIR)

add_library(life2d SHARED ${MODULES_SOURCE_DIR})

# [install]
install(TARGETS life2d
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    PERMISSIONS OWNER_WRITE OWNER_EXECUTE OWNER_READ GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    ARCHIVE DESTINATION bin
)

# install(DIRECTORY .
#     DESTINATION include
#     FILES_MATCHING PATTERN "*.h" PATTERN "*.hh"
#     PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ GROUP_WRITE WORLD_READ
# )