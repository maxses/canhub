#-----------------------------------------------------------------------------
#
# \brief		CMake module to create an git version information header file
#
#				Example of usage:
#
#					[...]
#
#					find_package(GitVersion REQUIRED)
#
#					add_executable( ${PROJECT_NAME}
#								src/main.cpp
#								${GIT_VERSION_HEADER}
#					)
#
#					[...]
#           If the cmake-cariable "BUILD_ID" is set, it is set as C/C++ 
#           definition/macro. 
#           This can be used by build/servers/release-scripts.
#           Applications can send the build-id it via UART/CAN.
#           It is needed to find the matching elf file for debugging an
#           flashed firmware. Just the same firmware-version is not sufficient.
#
# \author	Maximilian Seesslen <mes@seesslen.net>
#
#-----------------------------------------------------------------------------


if ( GIT_VERSION_HEADER_${PROJECT_NAME} )
   message( FATAL_ERROR "Variable for GIT_VERSION_HEADER_${PROJECT_NAME} already set" )
endif()

set ( GIT_VERSION_HEADER_${PROJECT_NAME}  "${CMAKE_CURRENT_BINARY_DIR}/git_version_${PROJECT_NAME}.h" )
set ( GIT_VERSION_ROOT_HEADER_${PROJECT_NAME}  "${CMAKE_CURRENT_BINARY_DIR}/git_version_root.h" )

include_directories ( "${CMAKE_CURRENT_BINARY_DIR}" )

add_custom_target( git_creater_${PROJECT_NAME}
    COMMAND
         SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR} PROJECT=${PROJECT_NAME} cmake -P ${CMAKE_CURRENT_LIST_DIR}/git_version_script.cmake
)

add_custom_target( git_creater_${PROJECT_NAME}_root
    COMMAND
         SOURCE_DIR=${CMAKE_SOURCE_DIR} OUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR} PROJECT=root cmake -P ${CMAKE_CURRENT_LIST_DIR}/git_version_script.cmake
)

add_custom_command(
    OUTPUT
         ${GIT_VERSION_HEADER_${PROJECT_NAME}}
    DEPENDS
         DEPENDS git_creater_${PROJECT_NAME}
)

add_custom_command(
	 OUTPUT
         ${GIT_VERSION_ROOT_HEADER_${PROJECT_NAME}}
    DEPENDS
         DEPENDS git_creater_${PROJECT_NAME}_root
)

set_source_files_properties(
   ${GIT_VERSION_HEADER_${PROJECT_NAME}}
	PROPERTIES GENERATED TRUE
)

set_source_files_properties(
   ${GIT_VERSION_ROOT_HEADER_${PROJECT_NAME}}
	PROPERTIES GENERATED TRUE
)

install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/versions_${PROJECT_NAME}.txt
	DESTINATION
		share/doc
   OPTIONAL
)


# BUILD_ID might be set by build scripts
if ( BUILD_ID )
   add_definitions( -DBUILD_ID=${BUILD_ID} )
endif ( BUILD_ID )


function ( use_git_version_from FROM_PROJECT )
   add_custom_command(
       OUTPUT
            ${GIT_VERSION_HEADER_${FROM_PROJECT}}
       DEPENDS
            DEPENDS git_creater_${FROM_PROJECT}
   )
   set ( GIT_VERSION_HEADER_${PROJECT_NAME}  ${GIT_VERSION_HEADER_${FROM_PROJECT}} PARENT_SCOPE )
   #message( "PROJECT_NAME: ${PROJECT_NAME}" )
   #message( "GIT_VERSION_HEADER_${PROJECT_NAME}: ${GIT_VERSION_HEADER_${PROJECT_NAME}}" )
   #message( "GIT_VERSION_HEADER_kokon_husk: ${GIT_VERSION_HEADER_kokon_husk}" )
   #message( FATAL_ERROR "###" )
endfunction()


#---fin.----------------------------------------------------------------------
