cmake_minimum_required(VERSION 3.40 FATAL_ERROR)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(logbook
        VERSION 0.1.0
        DESCRIPTION "Standalone C++ Console Text journal library."
        LANGUAGES CXX
)

set(SRC_PREFIX ${PROJECT_NAME})

set(HEADERS
    ${SRC_PREFIX}/exports.h
    ${SRC_PREFIX}/colors.h
    ${SRC_PREFIX}/glyphs.h
    ${SRC_PREFIX}/unicode_glyphs_table.i.h
    ${SRC_PREFIX}/rem.h
    ${SRC_PREFIX}/string.h
    ${SRC_PREFIX}/buffer.h
    ${SRC_PREFIX}/book.h
    ${SRC_PREFIX}/border_glyphes_set.h
)


add_library(${PROJECT_NAME}

    #STATIC
    SHARED
    ${HEADERS}
    ${SRC_PREFIX}/colors.cxx
    ${SRC_PREFIX}/glyphs.cxx
    ${SRC_PREFIX}/string.cxx
    ${SRC_PREFIX}/rem.cxx
    ${SRC_PREFIX}/buffer.cxx
    ${SRC_PREFIX}/book.cxx
    ${SRC_PREFIX}/book.file.cxx
    ${SRC_PREFIX}/border_glyphes_set.cxx
    ${SRC_PREFIX}/book.log.cxx
)



target_include_directories(${PROJECT_NAME} PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                           $<INSTALL_INTERFACE:include/${SRC_PREFIX}>
)

get_target_property(MY_INCLUDES ${PROJECT_NAME} INCLUDE_DIRECTORIES)
message(STATUS "Include directories for ${PROJECT_NAME}: ${MY_INCLUDES}")
message(STATUS "source dir: ${CMAKE_CURRENT_SOURCE_DIR}")

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${FRAMEWORK}.${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${HEADERS}"
)



target_compile_definitions(${PROJECT_NAME} PUBLIC "${PROJECT_NAME}_DEBUG=$<CONFIG:Debug>")
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${PROJECT_NAME}_export")

IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    )
ENDIF ()


target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS} sqlite3) # and other system dependencies...



install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bi§
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}
)




add_custom_target("uninstall_${PROJECT_NAME}" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall_${PROJECT_NAME}"
    POST_BUILD
    COMMENT "Uninstall ${PROJECT_NAME} files under include and lib"
    COMMAND rm -vrf ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME} ${CMAKE_INSTALL_PREFIX}/lib/lib${PROJECT_NAME}++* || echo "Nothing in install_manifest.txt to be uninstalled!"
)

add_subdirectory(playground)
