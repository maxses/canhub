#------------------------------------------------------------------------------
#
# \brief CMakeLists.txt for candump binary
#
#------------------------------------------------------------------------------


find_package( GitVersion REQUIRED )

add_executable(
   canhubdump
      include/candump.hpp
      src/candump.cpp
      src/main.cpp
      ${GIT_VERSION_HEADER}
)

target_link_libraries(
   canhubdump
      canhub
)

target_include_directories(
   canhubdump
      PRIVATE
         "include/"
)

install (
    TARGETS canhubdump
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)


#---fin------------------------------------------------------------------------
