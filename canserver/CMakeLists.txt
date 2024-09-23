#------------------------------------------------------------------------------
#
# \brief CMakeLists.txt for canserver binary
#
#------------------------------------------------------------------------------


# parent_git_version_header()
find_package( GitVersion REQUIRED )

add_executable( 
   canserver 
      src/main.cpp
      ${GIT_VERSION_HEADER}
)

add_dependencies( canserver GitVersion )

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
