# 💻 Fego Robot: Laptop Workspace (Ground Control)

This workspace is designed to run on the remote PC (host laptop). It handles all graphical interfaces, visualization, and remote monitoring for the Fego Robot, ensuring the Raspberry Pi 5 reserves its processing power for hardware control and autonomous navigation algorithms.

## 📌 Overview
The `laptop_ws` contains the packages necessary to visualize the robot's physical state, sensor data, and environment mapping in real-time using RViz2. 

## 📂 Directory Structure
- **`src/real_robot/launch/`**
  - `display_real.launch.xml`: The primary launch file for the PC. It connects to the ROS 2 network and boots up the visualization tools without attempting to spawn hardware controllers.
- **`src/real_robot/rviz/`**
  - `urdf_config.rviz`: A pre-configured RViz2 layout tailored for Fego. It includes displays for the robot model (URDF), the LD19 LiDAR `/scan` data, and the USB Camera feed.

## 🛜 Network Configuration
For this workspace to communicate with the Fego Robot, both the PC and the Raspberry Pi must be on the same Wi-Fi network and share the same `ROS_DOMAIN_ID`.

Export the domain ID in your terminal (or add it to your `.bashrc`):
```bash
export ROS_DOMAIN_ID=30 # Ensure this matches the Pi!
```
## 🛠️ USEFUL COMMANDS & SETUP

### 1. Create the 'drive' alias in your .bashrc (Run this once on the Pc)

```bash
echo 'alias drive="ros2 run teleop_twist_keyboard teleop_twist_keyboard --ros-args -p stamped:=true -p frame_id:=base_footprint -r cmd_vel:=/diff_drive_controller/cmd_vel"' >> ~/.bashrc
source ~/.bashrc
```
### 2. Build the workspace and source it
```bash
cd ~/laptop_ws
colcon build --packages-select real_robot
source install/setup.bash
```

### 3. Launch the main robot stack
```bash
ros2 launch real_robot display_real.launch.xml
```
### 4. Teleoperate the robot (Open a new terminal)
Since we added the alias in step 1, you simply type:
```bash
drive
```
### 5. Debugging & Verification (Open a new terminal)
List all active topics:
```bash
ros2 topic list
```
See the target velocity from the keyboard:
```bash
ros2 topic echo /cmd_vel
```
See the actual PWM values being sent to the Arduino:
```bash
ros2 topic echo /cmd_vel_pwm
```