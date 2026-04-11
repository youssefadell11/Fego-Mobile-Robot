cmake_minimum_required(VERSION 3.8)
project(diffdrive_arduino)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(hardware_interface REQUIRED)
find_package(pluginlib REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(asio_cmake_module REQUIRED)
find_package(io_context REQUIRED)
find_package(serial_driver REQUIRED)

add_library(${PROJECT_NAME} SHARED
  src/arduino_interface.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  hardware_interface
  pluginlib
  std_msgs
  asio_cmake_module
  io_context
  serial_driver
)

pluginlib_export_plugin_description_file(hardware_interface diffdrive_arduino.xml)

install(TARGETS ${PROJECT_NAME}
  DESTINATION lib
)

install(DIRECTORY include/
  DESTINATION include
)

ament_export_dependencies(rclcpp hardware_interface pluginlib std_msgs serial_driver)

ament_package()