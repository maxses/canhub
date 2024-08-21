#------------------------------------------------------------------------------
#
# \brief CMakeLists.txt husk for CANHub libraries and binaries
#
#------------------------------------------------------------------------------

cmake_minimum_required( VERSION 3.10 )

project( canhub LANGUAGES CXX VERSION 1.0.1 )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_MODULE_PATH   "${CMAKE_SOURCE_DIR}/cmake" )

find_package( QT NAMES Qt5 Qt6 COMPONENTS Core Network REQUIRED )
find_package( Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network )
find_package( GitVersion REQUIRED )

set( CMAKE_CXX_STANDARD 20 )

add_subdirectory( canhub )
add_subdirectory( canserver )
add_subdirectory( candump )
add_subdirectory( tests )


#---fin------------------------------------------------------------------------
