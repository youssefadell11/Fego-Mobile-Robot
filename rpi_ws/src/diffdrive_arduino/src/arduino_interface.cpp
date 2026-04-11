#include "diffdrive_arduino/arduino_interface.hpp"

#include <chrono>
#include <cmath>
#include <limits>
#include <memory>
#include <vector>
#include <sstream>

#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include "rclcpp/rclcpp.hpp"

namespace diffdrive_arduino
{

hardware_interface::CallbackReturn DiffDriveArduinoHardware::on_init(
  const hardware_interface::HardwareInfo & info)
{
  if (
    hardware_interface::SystemInterface::on_init(info) !=
    hardware_interface::CallbackReturn::SUCCESS)
  {
    return hardware_interface::CallbackReturn::ERROR;
  }

  cfg_.left_wheel_name = info_.hardware_parameters["left_wheel_name"];
  cfg_.right_wheel_name = info_.hardware_parameters["right_wheel_name"];
  cfg_.loop_rate = std::stof(info_.hardware_parameters["loop_rate"]);
  cfg_.device = info_.hardware_parameters["device"];
  cfg_.baud_rate = std::stoi(info_.hardware_parameters["baud_rate"]);
  cfg_.timeout_ms = std::stoi(info_.hardware_parameters["timeout"]);
  cfg_.enc_counts_per_rev = std::stoi(info_.hardware_parameters["enc_counts_per_rev"]);

  hw_velocities_.resize(info_.joints.size(), std::numeric_limits<double>::quiet_NaN());
  hw_positions_.resize(info_.joints.size(), std::numeric_limits<double>::quiet_NaN());
  hw_commands_.resize(info_.joints.size(), std::numeric_limits<double>::quiet_NaN());

  for (const hardware_interface::ComponentInfo & joint : info_.joints)
  {
    if (joint.command_interfaces.size() != 1)
    {
      RCLCPP_FATAL(
        rclcpp::get_logger("DiffDriveArduinoHardware"),
        "Joint '%s' has %zu command interfaces found. 1 expected.", joint.name.c_str(),
        joint.command_interfaces.size());
      return hardware_interface::CallbackReturn::ERROR;
    }

    if (joint.command_interfaces[0].name != hardware_interface::HW_IF_VELOCITY)
    {
      RCLCPP_FATAL(
        rclcpp::get_logger("DiffDriveArduinoHardware"),
        "Joint '%s' have %s command interfaces found. '%s' expected.", joint.name.c_str(),
        joint.command_interfaces[0].name.c_str(), hardware_interface::HW_IF_VELOCITY);
      return hardware_interface::CallbackReturn::ERROR;
    }
  }

  debug_node_ = std::make_shared<rclcpp::Node>("arduino_pwm_debug");
  pwm_pub_ = debug_node_->create_publisher<std_msgs::msg::Int32MultiArray>("/cmd_vel_pwm", 10);
  RCLCPP_INFO(rclcpp::get_logger("DiffDriveArduinoHardware"), "Custom PWM Debug Publisher Initialized!");

  return hardware_interface::CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::StateInterface> DiffDriveArduinoHardware::export_state_interfaces()
{
  std::vector<hardware_interface::StateInterface> state_interfaces;
  for (auto i = 0u; i < info_.joints.size(); i++)
  {
    state_interfaces.emplace_back(hardware_interface::StateInterface(
      info_.joints[i].name, hardware_interface::HW_IF_POSITION, &hw_positions_[i]));
    state_interfaces.emplace_back(hardware_interface::StateInterface(
      info_.joints[i].name, hardware_interface::HW_IF_VELOCITY, &hw_velocities_[i]));
  }

  return state_interfaces;
}

std::vector<hardware_interface::CommandInterface> DiffDriveArduinoHardware::export_command_interfaces()
{
  std::vector<hardware_interface::CommandInterface> command_interfaces;
  for (auto i = 0u; i < info_.joints.size(); i++)
  {
    command_interfaces.emplace_back(hardware_interface::CommandInterface(
      info_.joints[i].name, hardware_interface::HW_IF_VELOCITY, &hw_commands_[i]));
  }

  return command_interfaces;
}

hardware_interface::CallbackReturn DiffDriveArduinoHardware::on_configure(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(rclcpp::get_logger("DiffDriveArduinoHardware"), "Configuring ...please wait...");
  
  try {
    arduino_.setup(cfg_.device, cfg_.baud_rate, cfg_.timeout_ms);
  } catch (const std::exception& e) {
    RCLCPP_ERROR(rclcpp::get_logger("DiffDriveArduinoHardware"), "Exception during setup: %s", e.what());
    return hardware_interface::CallbackReturn::ERROR;
  }

  RCLCPP_INFO(rclcpp::get_logger("DiffDriveArduinoHardware"), "Successfully configured!");
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn DiffDriveArduinoHardware::on_cleanup(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(rclcpp::get_logger("DiffDriveArduinoHardware"), "Cleaning up ...please wait...");

  RCLCPP_INFO(rclcpp::get_logger("DiffDriveArduinoHardware"), "Successfully cleaned up!");
  return hardware_interface::CallbackReturn::SUCCESS;
}


hardware_interface::CallbackReturn DiffDriveArduinoHardware::on_activate(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(rclcpp::get_logger("DiffDriveArduinoHardware"), "Activating ...please wait...");

  for (size_t i = 0; i < hw_positions_.size(); i++)
  {
    hw_positions_[i] = 0.0;
    hw_velocities_[i] = 0.0;
    hw_commands_[i] = 0.0;
  }

  RCLCPP_INFO(rclcpp::get_logger("DiffDriveArduinoHardware"), "Successfully activated!");
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn DiffDriveArduinoHardware::on_deactivate(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(rclcpp::get_logger("DiffDriveArduinoHardware"), "Deactivating ...please wait...");

  arduino_.sendMsg("m 0 0\r");
  RCLCPP_INFO(rclcpp::get_logger("DiffDriveArduinoHardware"), "Successfully deactivated!");
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::return_type DiffDriveArduinoHardware::read(
  const rclcpp::Time & /*time*/, const rclcpp::Duration & period)
{

  for (std::size_t i = 0; i < hw_velocities_.size(); i++)
  {
    hw_velocities_[i] = hw_commands_[i];
    hw_positions_[i] += hw_commands_[i] * period.seconds();
  }

  return hardware_interface::return_type::OK;
}

hardware_interface::return_type DiffDriveArduinoHardware::write(
  const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/)
{

  double left_rads = hw_commands_[0];
  double right_rads = hw_commands_[1];

  double max_rads = 10.0; 

  int left_pwm = std::round((left_rads / max_rads) * 255.0);
  int right_pwm = std::round((right_rads / max_rads) * 255.0);

  if (left_pwm > 255) left_pwm = 255;
  if (left_pwm < -255) left_pwm = -255;
  if (right_pwm > 255) right_pwm = 255;
  if (right_pwm < -255) right_pwm = -255;

  std::stringstream ss;
  ss << "m " << left_pwm << " " << right_pwm << "\r";
  arduino_.sendMsg(ss.str());

  std_msgs::msg::Int32MultiArray pwm_msg;
  pwm_msg.data = {left_pwm, right_pwm};
  pwm_pub_->publish(pwm_msg);

  return hardware_interface::return_type::OK;
}

}  

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(
  diffdrive_arduino::DiffDriveArduinoHardware, hardware_interface::SystemInterface)