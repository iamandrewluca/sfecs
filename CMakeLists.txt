cmake_minimum_required(VERSION 3.3)
project(SFECS)

set( SFECS_MAJOR_VERSION 1 )
set( SFECS_MINOR_VERSION 0 )
set( SFECS_REVISION_VERSION 0 )

### USER INPUT ###

set( SFECS_BUILD_SHARED_LIBS true CACHE BOOL "Build shared library." )
set( SFECS_BUILD_EXAMPLES true CACHE BOOL "Build examples." )
set( SFECS_BUILD_DOC false CACHE BOOL "Generate API documentation." )
set( SFML_STATIC_LIBRARIES false CACHE BOOL "Do you want to link SFML statically?" )


# Tell CMake where to find additional find Modules
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

set(SFML_ROOT "C:/SFML")
find_package(SFML REQUIRED system window graphics network audio)

set( INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include" )
set( SOURCE_PATH "${PROJECT_SOURCE_DIR}/src" )

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/SFECS/*.hpp src/SFECS/*.cpp )

include_directories( "${INCLUDE_PATH}" )
include_directories( "${SOURCE_PATH}" )
include_directories( SYSTEM "${SFML_INCLUDE_DIR}" )

# Set the library output directory
set( LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib" )

# Add the library.
if( SFECS_BUILD_SHARED_LIBS )
    add_library( SFECS SHARED ${SOURCES} )

    set_target_properties( SFECS PROPERTIES DEBUG_POSTFIX -d )
else()
    add_definitions( -DSFECS_STATIC )
    add_library( SFECS ${SOURCES} )

    set_target_properties( SFECS PROPERTIES DEBUG_POSTFIX -s-d )
    set_target_properties( SFECS PROPERTIES RELEASE_POSTFIX -s )
    set_target_properties( SFECS PROPERTIES MINSIZEREL_POSTFIX -s )
endif()

# Tell the compiler to export when necessary.
set_target_properties( SFECS PROPERTIES DEFINE_SYMBOL SFECS_EXPORTS )

# Platform- and compiler-specific options.
if( WIN32 )
    set( SFECS_STATIC_STD_LIBS FALSE CACHE BOOL "Use statically linked standard/runtime libraries? This option must match the one used for SFML." )

    # Determine whether we're dealing with a TDM compiler or not
    if( CMAKE_COMPILER_IS_GNUCXX )
        execute_process( COMMAND "${CMAKE_CXX_COMPILER}" "--version" OUTPUT_VARIABLE GCC_COMPILER_VERSION )
        string( REGEX MATCHALL ".*(tdm[64]*-[1-9]).*" COMPILER_GCC_TDM "${GCC_COMPILER_VERSION}" )
    endif()

    # Allow the static linking of the runtime libraries
    if( SFECS_STATIC_STD_LIBS )
        if( SFECS_BUILD_SHARED_LIBS )
            message( FATAL_ERROR "\n-> SFECS_STATIC_STD_LIBS and SFECS_BUILD_SHARED_LIBS are not compatible.\n-> They lead to multiple runtime environments which results in undefined behavior.\n" )
        else()
            add_definitions( -DSFML_STATIC )
            if( MSVC )
                foreach( flag CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE )
                    if( ${flag} MATCHES "/MD" )
                        string( REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}" )
                    endif()
                endforeach()
            elseif( CMAKE_COMPILER_IS_GNUCXX AND NOT COMPILER_GCC_TDM )
                set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++" )
            endif()
        endif()
    elseif( COMPILER_GCC_TDM )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -shared-libgcc -shared-libstdc++" )
    endif()

    add_definitions( -DWIN32 )
    target_link_libraries( SFECS ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${OPENGL_gl_LIBRARY} )

    if( CMAKE_COMPILER_IS_GNUCXX )
        if( SFECS_BUILD_SHARED_LIBS )
            set_target_properties( SFECS PROPERTIES PREFIX "" )
        endif()

        set_target_properties( SFECS PROPERTIES IMPORT_SUFFIX ".a" )
    endif()

    set( SHARE_PATH "." )
    set( LIB_PATH "lib" )
elseif( APPLE )
    find_library( COREFOUNDATION_LIBRARY CoreFoundation )
    mark_as_advanced( COREFOUNDATION_LIBRARY )

    include_directories( SYSTEM /System/Library/Frameworks/CoreFoundation.framework/Headers )
    target_link_libraries( SFECS ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${OPENGL_gl_LIBRARY} ${COREFOUNDATION_LIBRARY} )
    set( SHARE_PATH "${CMAKE_INSTALL_PREFIX}/share/SFECS" )
    set( LIB_PATH "lib" )
elseif( "${CMAKE_SYSTEM_NAME}" MATCHES "Linux" )
    target_link_libraries( SFECS ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${OPENGL_gl_LIBRARY} ${X11_LIBRARIES} )
    set( SHARE_PATH "${CMAKE_INSTALL_PREFIX}/share/SFECS" )

    if( LIB_SUFFIX )
        set( LIB_PATH "lib${LIB_SUFFIX}" )
    else()
        set( LIB_PATH "lib" )
    endif()
else()
    target_link_libraries( SFECS ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${OPENGL_gl_LIBRARY} )
    set( SHARE_PATH "${CMAKE_INSTALL_PREFIX}/share/SFECS" )
    set( LIB_PATH "lib" )
endif()

if( CMAKE_CXX_COMPILER MATCHES ".*clang[+][+]" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
    set( CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}" )
elseif( CMAKE_COMPILER_IS_GNUCXX )
    set( CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}" )
endif()

### EXAMPLES ###

if( SFECS_BUILD_EXAMPLES )
    add_subdirectory( "examples" )
endif()

### DOCUMENTATION ###

if( SFECS_BUILD_DOC )
    add_subdirectory( "doc" )
endif()

### INSTALL TARGETS ###

install(
        TARGETS SFECS
        RUNTIME DESTINATION bin COMPONENT bin
        LIBRARY DESTINATION "${LIB_PATH}" COMPONENT bin
        ARCHIVE DESTINATION "${LIB_PATH}" COMPONENT dev
)

install(
        DIRECTORY include
        DESTINATION .
)

install(
        FILES README.md AUTHORS.md LICENSE.md CHANGELOG.md
        DESTINATION "${SHARE_PATH}"
)

install(
        FILES cmake/Modules/FindSFECS.cmake
        DESTINATION "${SHARE_PATH}/cmake/Modules"
)