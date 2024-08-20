cmake_minimum_required( VERSION 3.10 )

project( canhub LANGUAGES CXX VERSION 1.0.1 )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package( QT NAMES Qt5 Qt6 COMPONENTS Core Network REQUIRED )
find_package( Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network )

set( CMAKE_CXX_STANDARD 20 )

include_directories(
   include/
)

add_library(
   canhub
      src/canserver.cpp
      src/connector.cpp
      src/connectorTcpClient.cpp
      src/connectorCan.cpp
      include/connector.hpp
      include/connectorTcpClient.hpp
      include/connectorCan.hpp
      include/canserver.hpp
      src/connectorTcpServer.cpp
      include/connectorTcpServer.hpp
)

target_include_directories(
   canhub
   INTERFACE
      "include/"
)

target_link_libraries(
   canhub
      Qt${QT_VERSION_MAJOR}::Network
)

add_executable( 
   canserver 
      src/main.cpp
)

target_link_libraries(
   canserver
      canhub
)

add_executable(
   candump
      include/candump.h
      src/candump.cpp
      src/main_candump.cpp
)

target_link_libraries(
   candump
      canhub
)

add_subdirectory( tests )


#---fin------------------------------------------------------------------------
