#------------------------------------------------------------------------------
#
# \brief CMakeLists.txt for tests for CANHub
#
#------------------------------------------------------------------------------


find_package( Catch2 3 )
if( NOT Catch2_FOUND )
   find_package( Catch )
   if( NOT Catch_FOUND )
      # find_package does not work for Catch, at least on ubuntu 20.04
      if( EXISTS /usr/include/catch )
         add_definitions( "-DCATCH_V1" )
      elseif( EXISTS /usr/include/catch2 )
         if( EXISTS /usr/include/catch2/catch_test_macros.hpp )
            add_definitions( "-DCATCH_V3" )
         else()
            add_definitions( "-DCATCH_V2" )
         endif()
      else( EXISTS /usr/include/catch2 )
         message( FATAL_ERROR "Install eeither Catch or Catch2")
      endif( EXISTS /usr/include/catch )
   endif( NOT Catch_FOUND )
   add_definitions( "-DCATCH_V1" )
else( NOT Catch2_FOUND)
   add_definitions( "-DCATCH_V3" )
   set( CATCH_LIBRARY "Catch2::Catch2WithMain" )
endif( NOT Catch2_FOUND )


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
   canhub
   ${CATCH_LIBRARY}
)

add_test(
   NAME tests
   COMMAND tests
   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)


#------------------------------------------------------------------------------
