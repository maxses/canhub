#------------------------------------------------------------------------------
#
# \brief CMakeLists.txt for CANHub library
#
#------------------------------------------------------------------------------


set (
   canhub_headers
      include/canhub/connector.hpp
      include/canhub/connectorTcpClient.hpp
      include/canhub/connectorCan.hpp
      include/canhub/canserver.hpp
      include/canhub/connectorTcpServer.hpp
)

add_library(
   canhub SHARED
   src/canserver.cpp
   src/connector.cpp
   src/connectorTcpClient.cpp
   src/connectorCan.cpp
   src/connectorTcpServer.cpp
   ${canhub_headers}
)

set_target_properties(
   canhub
      PROPERTIES
         PUBLIC_HEADER
            "${canhub_headers}"
)

target_include_directories(
   canhub
      PRIVATE
         "include/"
      INTERFACE
         "include/"
)

target_link_libraries(
   canhub
      Qt${QT_VERSION_MAJOR}::Network
)

install (
    TARGETS canhub
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)


#---fin------------------------------------------------------------------------
