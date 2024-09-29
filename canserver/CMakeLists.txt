#------------------------------------------------------------------------------
#
# \brief CMakeLists.txt for canserver binary
#
#------------------------------------------------------------------------------


find_package( GitVersion REQUIRED )

add_executable( 
   canserver 
      src/main.cpp
      ${GIT_VERSION_HEADER}
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
