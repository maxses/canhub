

if(NOT GIT_VERSION_HEADER)

   set( GIT_VERSION_HEADER_REAL ${CMAKE_BINARY_DIR}/git_version/git_version.h )
   set( GIT_VERSION_HEADER_FAKE ${GIT_VERSION_HEADER_REAL}_doesnotexist )
   set( GIT_VERSION_HEADER ${GIT_VERSION_HEADER_REAL} )

   # Having ${GIT_VERSION_HEADER_REAL} in outputs causes file to be touched
   # and so everything is rebuild
   add_custom_command(
      OUTPUT ${GIT_VERSION_HEADER_FAKE}
      BYPRODUCTS ${GIT_VERSION_HEADER_REAL}
      COMMENT "Generation GIT version file"
      COMMAND
            SOURCE_DIR=${CMAKE_SOURCE_DIR}
            OUTPUT_DIR=${CMAKE_BINARY_DIR}
            PROJECT=${PROJECT_NAME}
               cmake -P ${CMAKE_CURRENT_LIST_DIR}/git_version_script.cmake

   )

   add_custom_target( GitVersion
      DEPENDS ${GIT_VERSION_HEADER_FAKE}
      SOURCES ${GIT_VERSION_HEADER_REAL}
   )

   include_directories( ${CMAKE_BINARY_DIR}/git_version )

else(NOT GIT_VERSION_HEADER)

   set_source_files_properties( ${GIT_VERSION_HEADER_FAKE}
      PROPERTIES
         GENERATED True )

   set_source_files_properties( ${GIT_VERSION_HEADER_REAL}
      PROPERTIES
         GENERATED True )

endif(NOT GIT_VERSION_HEADER)


#---fin------------------------------------------------------------------------
