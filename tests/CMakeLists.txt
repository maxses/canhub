#------------------------------------------------------------------------------
#
# \brief CMakeLists.txt for tests for CANHub
#
#------------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.11)
project( canhub_tests )

find_package(Catch2 3 QUIET)
if (Catch2_FOUND)
    add_definitions( "-DCATCH_V3" )
    set(CATCH2_TARGET Catch2::Catch2WithMain)
else()
    find_package(Catch2 2 REQUIRED)
    add_definitions( "-DCATCH_V2" )
    set(CATCH2_TARGET Catch2::Catch2)
endif()

set(
   headers
      test_connector.hpp
)


set(
   sources
      test_routing.cpp
      test_connector.cpp
)

add_executable(
   ${PROJECT_NAME}
      ${sources}
      ${headers}
)

target_link_libraries(
   ${PROJECT_NAME}
      canhub
      ${CATCH2_TARGET}
)

add_test(
   NAME ${PROJECT_NAME}
   COMMAND ${PROJECT_NAME}
   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)


#------------------------------------------------------------------------------
