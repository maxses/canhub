#------------------------------------------------------------------------------
#
# \brief CMakeLists.txt for candump binary
#
#------------------------------------------------------------------------------


use_git_version_from( canhub )


add_executable(
   candump
      include/candump.hpp
      src/candump.cpp
      src/main.cpp
      ${GIT_VERSION_HEADER_${PROJECT_NAME}}
)

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
