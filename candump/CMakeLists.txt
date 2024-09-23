#------------------------------------------------------------------------------
#
# \brief CMakeLists.txt for candump binary
#
#------------------------------------------------------------------------------


# parent_git_version_header()

# find_package( GitVersion REQUIRED )

add_executable(
   candump
      include/candump.hpp
      src/candump.cpp
      src/main.cpp
      # ${GIT_VERSION_HEADER}
)

add_dependencies( candump GitVersion )

target_link_libraries(
   candump
      canhub
)

target_include_directories(
   candump
      PRIVATE
         "include/"
)

install (
    TARGETS candump
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)


#---fin------------------------------------------------------------------------
