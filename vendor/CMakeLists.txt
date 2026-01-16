cmake_policy(SET CMP0079 NEW)

add_subdirectory(fpng)
target_include_directories(fpng INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/fpng/)
target_link_libraries(rtk fpng)

add_subdirectory(glm)
target_include_directories(glm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/glm)
target_link_libraries(rtk glm)