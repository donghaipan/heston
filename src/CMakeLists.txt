add_library(
  heston STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/black76.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/calculator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/underlying_process.cpp)

target_include_directories(heston PUBLIC ${CMAKE_SOURCE_DIR}/include)
set_target_properties(heston PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
