# This script locates the SFECS library
# ------------------------------------
#
# Usage
# -----
#
# You can enforce a specific version, one of either MAJOR.MINOR.REVISION,
# MAJOR.MINOR or only MAJOR. If nothing is specified, the version won't
# be checked i.e. any version will be accepted. SFECS does not consist of
# multiple components, so specifying COMPONENTS is not required.
#
# Example:
#   find_package( SFECS )       // no specific version
#   find_package( SFECS 0.2 )   // any 0.2 version
#   find_package( SFECS 0.2.3 ) // version 0.2.3 or greater
#
# By default, the dynamic version of SFECS will be found. To find the static
# version instead, you must set the SFECS_STATIC_LIBRARIES variable to TRUE
# before calling find_package( SFECS ). In that case, SFECS_STATIC will also be
# defined by this script.
#
# Example:
#   set( SFECS_STATIC_LIBRARIES TRUE )
#   find_package( SFECS )
#
# Since you have to link all of SFECS's dependencies when you link SFECS
# statically, the variable SFECS_DEPENDENCIES is also defined. See below
# for a detailed description.
#
# On Mac OS X if SFECS_STATIC_LIBRARIES is not set to TRUE then by default CMake
# will search for frameworks unless CMAKE_FIND_FRAMEWORK is set to "NEVER".
# Please refer to CMake documentation for more details.
# Moreover, keep in mind that SFECS frameworks are only available as release
# libraries unlike dylibs which are available for both release and debug modes.
#
# If SFECS is not installed in a standard path, you can use the SFECS_ROOT
# CMake (or environment) variable to tell CMake where to look for SFECS.
#
# Output
# ------
#
# This script defines the following variables:
#   - SFECS_LIBRARY_DEBUG:   the path to the debug library
#   - SFECS_LIBRARY_RELEASE: the path to the release library
#   - SFECS_LIBRARY:         the path to the library to link to
#   - SFECS_FOUND:           TRUE if the SFECS library is found
#   - SFECS_INCLUDE_DIR:     the path where SFECS headers are located (the directory containing the SFECS/Config.hpp file)
#   - SFECS_DEPENDENCIES:    the list of libraries SFECS depends on, in case of static linking
#
# Example (dynamic linking):
#   find_package( SFECS REQUIRED )
#   include_directories( ${SFECS_INCLUDE_DIR} )
#   add_executable( myapp ... )
#   target_link_libraries( myapp ${SFECS_LIBRARY} ... )
#
# Example (static linking):
#   set( SFECS_STATIC_LIBRARIES TRUE )
#   find_package( SFECS REQUIRED )
#   include_directories( ${SFECS_INCLUDE_DIR} )
#   add_executable( myapp ... )
#   target_link_libraries( myapp ${SFECS_LIBRARY} ${SFECS_DEPENDENCIES} ... )

if( SFECS_STATIC_LIBRARIES )
    add_definitions( -DSFECS_STATIC )
endif()

set(
        SFECS_SEARCH_PATHS
        "${SFECS_ROOT}"
        "$ENV{SFECS_ROOT}"
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw
        /opt/local
        /opt/csw
        /opt
)

find_path(
        SFECS_INCLUDE_DIR
        SFECS/Config.hpp
        PATH_SUFFIXES
        include
        PATHS
        ${SFECS_SEARCH_PATHS}
)

set( SFECS_VERSION_OK true )
if( SFECS_FIND_VERSION AND SFECS_INCLUDE_DIR )
    file( READ "${SFECS_INCLUDE_DIR}/SFECS/Config.hpp" SFECS_CONFIG_HPP )

    string( REGEX MATCH ".*#define SFECS_MAJOR_VERSION ([0-9]+).*#define SFECS_MINOR_VERSION ([0-9]+).*#define SFECS_REVISION_VERSION ([0-9]+).*" SFECS_CONFIG_HPP "${SFECS_CONFIG_HPP}" )
    string( REGEX REPLACE ".*#define SFECS_MAJOR_VERSION ([0-9]+).*" "\\1" SFECS_VERSION_MAJOR "${SFECS_CONFIG_HPP}" )
    string( REGEX REPLACE ".*#define SFECS_MINOR_VERSION ([0-9]+).*" "\\1" SFECS_VERSION_MINOR "${SFECS_CONFIG_HPP}" )
    string( REGEX REPLACE ".*#define SFECS_REVISION_VERSION ([0-9]+).*" "\\1" SFECS_VERSION_PATCH "${SFECS_CONFIG_HPP}" )

    math( EXPR SFECS_REQUESTED_VERSION "${SFECS_FIND_VERSION_MAJOR} * 10000 + ${SFECS_FIND_VERSION_MINOR} * 100 + ${SFECS_FIND_VERSION_PATCH}" )

    if( SFECS_VERSION_MAJOR OR SFECS_VERSION_MINOR OR SFECS_VERSION_PATCH )
        math( EXPR SFECS_VERSION "${SFECS_VERSION_MAJOR} * 10000 + ${SFECS_VERSION_MINOR} * 100 + ${SFECS_VERSION_PATCH}" )

        if( SFECS_VERSION LESS SFECS_REQUESTED_VERSION )
            set( SFECS_VERSION_OK false )
        endif()
    else()
        # SFECS version is < 0.3.0
        if( SFECS_REQUESTED_VERSION GREATER 300 )
            set( SFECS_VERSION_OK false )
            set( SFECS_VERSION_MAJOR 0 )
            set( SFECS_VERSION_MINOR x )
            set( SFECS_VERSION_PATCH y )
        endif()
    endif()
endif()

find_library(
        SFECS_LIBRARY_DYNAMIC_RELEASE
        NAMES
        sfecs
        PATH_SUFFIXES
        lib
        lib64
        PATHS
        ${SFECS_SEARCH_PATHS}
)

find_library(
        SFECS_LIBRARY_DYNAMIC_DEBUG
        NAMES
        sfecs-d
        PATH_SUFFIXES
        lib
        lib64
        PATHS
        ${SFECS_SEARCH_PATHS}
)

find_library(
        SFECS_LIBRARY_STATIC_RELEASE
        NAMES
        sfecs-s
        PATH_SUFFIXES
        lib
        lib64
        PATHS
        ${SFECS_SEARCH_PATHS}
)

find_library(
        SFECS_LIBRARY_STATIC_DEBUG
        NAMES
        sfecs-s-d
        PATH_SUFFIXES
        lib
        lib64
        PATHS
        ${SFECS_SEARCH_PATHS}
)

if( SFECS_STATIC_LIBRARIES )
    if( SFECS_LIBRARY_STATIC_RELEASE )
        set( SFECS_LIBRARY_RELEASE "${SFECS_LIBRARY_STATIC_RELEASE}" )
    endif()
    if( SFECS_LIBRARY_STATIC_DEBUG )
        set( SFECS_LIBRARY_DEBUG "${SFECS_LIBRARY_STATIC_DEBUG}" )
    endif()
else()
    if( SFECS_LIBRARY_DYNAMIC_RELEASE )
        set( SFECS_LIBRARY_RELEASE "${SFECS_LIBRARY_DYNAMIC_RELEASE}" )
    endif()
    if( SFECS_LIBRARY_DYNAMIC_DEBUG )
        set( SFECS_LIBRARY_DEBUG "${SFECS_LIBRARY_DYNAMIC_DEBUG}" )
    endif()
endif()

mark_as_advanced(
        SFECS_LIBRARY_STATIC_RELEASE
        SFECS_LIBRARY_STATIC_DEBUG
        SFECS_LIBRARY_DYNAMIC_RELEASE
        SFECS_LIBRARY_DYNAMIC_DEBUG
)

if( SFECS_LIBRARY_RELEASE OR SFECS_LIBRARY_DEBUG )
    if( SFECS_LIBRARY_RELEASE AND SFECS_LIBRARY_DEBUG )
        set( SFECS_LIBRARY debug "${SFECS_LIBRARY_DEBUG}" optimized "${SFECS_LIBRARY_RELEASE}" )
    elseif( SFECS_LIBRARY_DEBUG AND NOT SFECS_LIBRARY_RELEASE )
        set( SFECS_LIBRARY_RELEASE "${SFECS_LIBRARY_DEBUG}" )
        set( SFECS_LIBRARY "${SFECS_LIBRARY_DEBUG}" )
    elseif( SFECS_LIBRARY_RELEASE AND NOT SFECS_LIBRARY_DEBUG )
        set( SFECS_LIBRARY_DEBUG "${SFECS_LIBRARY_RELEASE}" )
        set( SFECS_LIBRARY "${SFECS_LIBRARY_RELEASE}" )
    endif()

    set( SFECS_FOUND true )
else()
    set( SFECS_LIBRARY "" )
    set( SFECS_FOUND false )
endif()

mark_as_advanced(
        SFECS_LIBRARY
        SFECS_LIBRARY_RELEASE
        SFECS_LIBRARY_DEBUG
)

if( SFECS_STATIC_LIBRARIES )
    set( SFECS_DEPENDENCIES )
    set( SFECS_MISSING_DEPENDENCIES )

    if( "${CMAKE_SYSTEM_NAME}" MATCHES "Linux" )
        find_library( X11_LIBRARY NAMES X11 PATHS ${SFECS_SEARCH_PATHS} PATH_SUFFIXES lib )

        if( ${X11_LIBRARY} STREQUAL "X11_LIBRARY-NOTFOUND" )
            unset( X11_LIBRARY )
            set( SFECS_MISSING_DEPENDENCIES "${SFECS_MISSING_DEPENDENCIES} X11" )
        endif()
    endif()

    if( "${CMAKE_SYSTEM_NAME}" MATCHES "Windows" )
        set( SFECS_DEPENDENCIES ${SFECS_DEPENDENCIES} "opengl32" )
    elseif( ( "${CMAKE_SYSTEM_NAME}" MATCHES "Linux" ) OR ( "${CMAKE_SYSTEM_NAME}" MATCHES "FreeBSD" ) )
        set( SFECS_DEPENDENCIES ${SFECS_DEPENDENCIES} "GL" ${X11_LIBRARY} )
    elseif( "${CMAKE_SYSTEM_NAME}" MATCHES "Darwin" )
        set( SFECS_DEPENDENCIES ${SFECS_DEPENDENCIES} "-framework OpenGL -framework Foundation" )
    endif()
endif()

if( NOT SFECS_INCLUDE_DIR OR NOT SFECS_LIBRARY )
    set( SFECS_FOUND false )
endif()

if( NOT SFECS_FOUND )
    set( FIND_SFECS_ERROR "SFECS not found." )
elseif( NOT SFECS_VERSION_OK )
    set( FIND_SFECS_ERROR "SFECS found but version too low, requested: ${SFECS_FIND_VERSION}, found: ${SFECS_VERSION_MAJOR}.${SFECS_VERSION_MINOR}.${SFECS_VERSION_PATCH}" )
    set( SFECS_FOUND false )
elseif( SFECS_STATIC_LIBRARIES AND SFECS_MISSING_DEPENDENCIES )
    set( FIND_SFECS_ERROR "SFECS found but some of its dependencies are missing: ${SFECS_MISSING_DEPENDENCIES}" )
    set( SFECS_FOUND false )
endif()

if( NOT SFECS_FOUND )
    if( SFECS_FIND_REQUIRED )
        message( FATAL_ERROR "${FIND_SFECS_ERROR}" )
    elseif( NOT SFECS_FIND_QUIETLY )
        message( "${FIND_SFECS_ERROR}" )
    endif()
else()
    if( SFECS_FIND_VERSION )
        message( STATUS "Found SFECS version ${SFECS_VERSION_MAJOR}.${SFECS_VERSION_MINOR}.${SFECS_VERSION_PATCH} in ${SFECS_INCLUDE_DIR}" )
    else()
        message( STATUS "Found SFECS in ${SFECS_INCLUDE_DIR}" )
    endif()
endif()