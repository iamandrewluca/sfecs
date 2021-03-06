cmake_minimum_required( VERSION 3.3 )

function( build_example SAMPLE_NAME SOURCES )
    add_executable( ${SAMPLE_NAME} ${SOURCES} )
    target_link_libraries( ${SAMPLE_NAME} SFECS ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${OPENGL_gl_LIBRARY} )

    install(
            TARGETS ${SAMPLE_NAME}
            RUNTIME DESTINATION "${PROJECT_SOURCE_DIR}/install/examples" COMPONENT examples
    )

    install(
            FILES ${SOURCES}
            DESTINATION "${PROJECT_SOURCE_DIR}/install/examples" COMPONENT examples
    )
endfunction()

build_example( "Prototype1" "Proto1.cpp" )
build_example( "Prototype2" "Proto2.cpp" )
build_example( "Prototype3" "Proto3.cpp" )
build_example( "Prototype4" "Proto4.cpp" )

# Copy data directory to build cache directory to be able to run examples from
# there. Useful for testing stuff.
# Don't try to copy if the directories are the same.
#if( NOT ( "${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}" ) )
#    add_custom_command(
#            TARGET "SFECS-Test"
#            COMMAND "${CMAKE_COMMAND}"
#            ARGS -E copy_directory "${PROJECT_SOURCE_DIR}/examples/data" "${PROJECT_BINARY_DIR}/examples/data"
#    )
#endif()

#install(
#        DIRECTORY data
#        DESTINATION "${SHARE_PATH}/examples"
#)