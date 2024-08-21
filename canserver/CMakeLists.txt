#------------------------------------------------------------------------------
#
# \brief CMakeLists.txt for canserver binary
#
#------------------------------------------------------------------------------


use_git_version_from( canhub )


add_executable( 
   canserver 
      src/main.cpp
      ${GIT_VERSION_HEADER_${PROJECT_NAME}}
)

target_link_libraries(
   canserver
      canhub
)

install (
    TARGETS canserver
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)


#---fin------------------------------------------------------------------------
