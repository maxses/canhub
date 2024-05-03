cmake_minimum_required(VERSION 3.10)

project(canserver LANGUAGES CXX VERSION 1.0.1)

# find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui SerialPort )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# if( NOT Qt6_FOUND )
        find_package( Qt5 COMPONENTS Core Widgets Network REQUIRED )
        set( QT_VERSION 5 )
        set( QT5 Yes )
# endif( NOT Qt6_FOUND )


set(CMAKE_CXX_STANDARD 20)

add_executable( canserver 
   main.cpp
   canserver.cpp
   canserver.hpp
   connection.cpp
   connection.hpp
   # Qt${QT_VERSION}::Widgets
)

target_link_libraries(
   canserver
   Qt${QT_VERSION}::Widgets
   Qt${QT_VERSION}::Network
)

#---fin------------------------------------------------------------------------
