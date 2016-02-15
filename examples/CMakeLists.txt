cmake_minimum_required( VERSION 3.3 )

function( build_example SAMPLE_NAME SOURCES )
    add_executable( ${SAMPLE_NAME} ${SOURCES} )
    target_link_libraries( ${SAMPLE_NAME} SFECS ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${OPENGL_gl_LIBRARY} )

    install(
            TARGETS ${SAMPLE_NAME}
            RUNTIME DESTINATION "${SHARE_PATH}/examples" COMPONENT examples
    )

    install(
            FILES ${SOURCES}
            DESTINATION "${SHARE_PATH}/examples" COMPONENT examples
    )
endfunction()

build_example( "HelloWorld" "HelloWorld.cpp" )