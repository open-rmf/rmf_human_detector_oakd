cmake_minimum_required(VERSION 3.8)
project(rmf_human_detector_oakd)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(depthai CONFIG REQUIRED)
find_package(pluginlib REQUIRED)
find_package(rmf_obstacle_ros2 REQUIRED)

#===============================================================================
add_library(rmf_human_detector_oakd src/HumanDetector.cpp)

target_include_directories(rmf_human_detector_oakd
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    ${rmf_obstacle_ros2_INCLUDE_DIRS}
    ${pluginlib_INCLUDE_DIRS}
)

target_link_libraries(rmf_human_detector_oakd
  PUBLIC
    rmf_obstacle_ros2::rmf_obstacle_ros2
    ${pluginlib_LIBRARIES}
)

target_compile_features(rmf_human_detector_oakd INTERFACE cxx_std_17)
target_compile_definitions(rmf_human_detector_oakd PUBLIC "PLUGINLIB__DISABLE_BOOST_FUNCTIONS")

pluginlib_export_plugin_description_file(rmf_obstacle_ros2 plugins.xml)

ament_export_libraries(
  rmf_human_detector_oakd
)

install(
  TARGETS rmf_human_detector_oakd
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

ament_package()
