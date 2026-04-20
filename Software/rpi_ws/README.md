# 🧠 Fego Robot: Raspberry Pi Workspace (Core)

This workspace runs on the Raspberry Pi 5. It is the central nervous system of the Fego Robot, responsible for managing the `ros2_control` lifecycle, communicating with the Arduino motor driver, and publishing sensor data (LiDAR and Camera) to the ROS 2 network.

## 📌 Overview
The `rpi_ws` utilizes ROS 2 Jazzy to bridge high-level navigation commands & Teleop commands (`cmd_vel`) down to physical hardware. It relies heavily on a custom-written hardware interface plugin that bypasses standard motor controllers to talk directly to a "Dumb Arduino" via serial communication.

## 📂 Directory Structure

### 1. `diffdrive_arduino` (Custom Hardware Interface)
A custom C++ `ros2_control` SystemInterface plugin.
- **`src/arduino_interface.cpp`**: Implements the `on_init`, `on_activate`, `read`, and `write` lifecycle nodes. It calculates the necessary PWM values based on incoming `rad/s` commands.
- **`include/diffdrive_arduino/arduino_comms.hpp`**: Handles the low-level, high-speed asynchronous serial communication (115200 baud) using the official ROS 2 `serial_driver`.

### 2. `real_robot` (Robot Configuration & Launch)
Contains the physical description and startup routines for Fego.
- **`urdf/`**: Modular Xacro/URDF files defining the robot's links, joints, and `ros2_control` hardware tags (`robot.urdf.xacro`, `ros2_control.xacro`, `lidar.xacro`, `camera.xacro`).
- **`meshes/`**: Optimized 3D meshes specifically exported for ROS 2 simulation (`RViz`).
    * `lidar.stl`
    * `base_link.stl`
    * `camera.stl`
    * `caster.stl`
    * `wheel.stl`
- **`config/`**: Contains `controllers.yaml` for setting up the `diff_drive_controller` and `joint_state_broadcaster`.
- **`launch/`**:
  - `fego.launch.xml`: The master launch file. Starts the `controller_manager`, spawns controllers, and boots up all sensor nodes (LiDAR & Camera).

## 🛠️ Hardware Requirements & Ports
Before launching, ensure the physical connections match your configuration files:
- **Arduino (Motor Driver):** Connected via USB (Defaults to `/dev/ttyUSB0` or `/dev/ttyACM0`).
- **LD19 LiDAR:** Connected via Serial/USB (Defaults to `/dev/ttyAMA0` at 230400 baud).
- **Webcam:** Connected via USB.
  
(Note: The LD19 LiDAR requires its specific SDK/ROS2 driver ldlidar_stl_ros2 to be built in your workspace).

## 🛜 Network Configuration
For this workspace to communicate with the Fego Robot, both the PC and the Raspberry Pi must be on the same Wi-Fi network and share the same `ROS_DOMAIN_ID`.

Export the domain ID in your terminal (or add it to your `.bashrc`):
```bash
export ROS_DOMAIN_ID=30 # Ensure this matches the Pc!
```
## 📦 Dependencies
Ensure the following ROS 2 Jazzy packages are installed on the Pi:
```bash
sudo apt update
sudo apt install ros-jazzy-ros2-control ros-jazzy-ros2-controllers ros-jazzy-serial-driver ros-jazzy-v4l2-camera
```

## 🚀 Build & Launch Instructions
### 1. Build the workspace:
```bash
cd ~/rpi_ws
colcon build --packages-select diffdrive_arduino real_robot
```
### 2. Source the environment:
```bash
source install/setup.bash
```
### 3. Launch the Robot:
```bash
ros2 launch real_robot fego.launch.xml
```
