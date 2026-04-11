#ifndef DIFFDRIVE_ARDUINO__DIFFDRIVE_ARDUINO_HPP_
#define DIFFDRIVE_ARDUINO__DIFFDRIVE_ARDUINO_HPP_

#include <string>
#include <vector>

#include "hardware_interface/system_interface.hpp"
#include "hardware_interface/handle.hpp"
#include "hardware_interface/hardware_info.hpp"
#include "hardware_interface/types/hardware_interface_return_values.hpp"
#include "rclcpp_lifecycle/state.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32_multi_array.hpp"
#include "diffdrive_arduino/arduino_comms.hpp"

namespace diffdrive_arduino
{

class DiffDriveArduinoHardware : public hardware_interface::SystemInterface
{
public:
  RCLCPP_SHARED_PTR_DEFINITIONS(DiffDriveArduinoHardware)

  hardware_interface::CallbackReturn on_init(
    const hardware_interface::HardwareInfo & info) override;

  std::vector<hardware_interface::StateInterface> export_state_interfaces() override;

  std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;

  hardware_interface::CallbackReturn on_configure(
    const rclcpp_lifecycle::State & previous_state) override;

  hardware_interface::CallbackReturn on_cleanup(
    const rclcpp_lifecycle::State & previous_state) override;

  hardware_interface::CallbackReturn on_activate(
    const rclcpp_lifecycle::State & previous_state) override;

  hardware_interface::CallbackReturn on_deactivate(
    const rclcpp_lifecycle::State & previous_state) override;

  hardware_interface::return_type read(
    const rclcpp::Time & time, const rclcpp::Duration & period) override;

  hardware_interface::return_type write(
    const rclcpp::Time & time, const rclcpp::Duration & period) override;

private:

  ArduinoComms arduino_;

  struct Config {
    std::string left_wheel_name = "";
    std::string right_wheel_name = "";
    float loop_rate = 0.0;
    std::string device = "";
    int baud_rate = 0;
    int timeout_ms = 0;
    int enc_counts_per_rev = 0;
  } cfg_;


  std::vector<double> hw_commands_;
  std::vector<double> hw_positions_;
  std::vector<double> hw_velocities_;

  rclcpp::Node::SharedPtr debug_node_;
  rclcpp::Publisher<std_msgs::msg::Int32MultiArray>::SharedPtr pwm_pub_;

};

}  

#endif  