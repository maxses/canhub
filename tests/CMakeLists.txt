#------------------------------------------------------------------------------
#
# \brief	CMakeLists.txt file for "liblepto"
#
#------------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.11)
project( tests )

if( EXISTS /usr/include/catch2 )
        add_definitions( "-DCATCH2" )
        find_package(Catch2 REQUIRED)
        set( CATCH_LIBRARY "Catch2::Catch2WithMain" )
elseif( EXISTS /usr/include/catch )
        add_definitions( "-DCATCH" )
endif( EXISTS /usr/include/catch2 )


set(headers
   test_connector.hpp
)


set(sources
   test_routing.cpp
   test_connector.cpp
)

add_executable( tests
   ${sources}
   ${headers}
)

target_link_libraries(
   tests
   canclient
   ${CATCH_LIBRARY}
)

add_test(
   NAME tests
   COMMAND tests
   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)


#------------------------------------------------------------------------------
