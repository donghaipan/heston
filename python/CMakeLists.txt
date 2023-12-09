pybind11_add_module(
  pyheston ${CMAKE_CURRENT_SOURCE_DIR}/python_binding.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/calculation_binding.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/underlying_process_binding.cpp)

target_include_directories(pyheston PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(pyheston PRIVATE heston)
set_target_properties(pyheston PROPERTIES OUTPUT_NAME heston)
