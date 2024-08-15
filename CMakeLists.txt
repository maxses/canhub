cmake_minimum_required(VERSION 3.10)

project(canserver LANGUAGES CXX VERSION 1.0.1)

find_package(Qt6 REQUIRED COMPONENTS Core Network )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if( NOT Qt6_FOUND )
   find_package( Qt5 COMPONENTS Core Network REQUIRED )
   set( QT_VERSION 5 )
   set( QT5 Yes )
else ( NOT Qt6_FOUND )
   set( QT_VERSION 6 )
endif( NOT Qt6_FOUND )


set(CMAKE_CXX_STANDARD 20)

include_directories(
   include/
)

add_library( canclient
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
   canclient INTERFACE "include/"
)

target_link_libraries(
   canclient
   Qt${QT_VERSION}::Network
)

add_executable( 
   canserver 
   src/main.cpp
)

target_link_libraries(
   canserver
   canclient
)

add_executable( candump
   include/candump.h
   src/candump.cpp
   src/main_candump.cpp
)

target_link_libraries(
   candump
   canclient
)

add_subdirectory( tests )


#---fin------------------------------------------------------------------------
