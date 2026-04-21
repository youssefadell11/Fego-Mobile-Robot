# Fego Mobile Robot

**Author:** Youssef Adel Wahba Boutros

## Project Overview
The Fego Robot is a custom-built differential drive mobile platform. Powered by a Raspberry Pi 5 and utilizing `ros2_control`, this project bridges the gap between hardware assembly and advanced ROS 2 robotics software. This documentation covers the 3D design, physical hardware build, software visualization, and real-world testing.

---

## 1. 3D CAD Design (Fusion 360)
The chassis and component placements were initially modeled in Autodesk Fusion 360 to ensure optimal weight distribution and sensor mounting.

<p align="center">
  <img src="Images/Fusion360/Fusion360_Fego_Mobile_Robot.jpg" width="800" alt="Fusion 360 Overall Model">
</p>

<p align="center">
  <img src="Images/Fusion360/Fego_Mobile_Robot_Home_View.jpg" width="400" alt="Home View">
  <img src="Images/Fusion360/Fego_Mobile_Robot_Side_View.jpg" width="400" alt="Side View">
</p>

---

## 2. Hardware Assembly & Real Robot
The physical build incorporates DC motors, an L298N motor driver, LiDAR, and a camera module. 

### Electronics & Wiring
<p align="center">
  <img src="Images/Real_Robot/1_DC_Motors_Connected_to_L298N_Module.jpg" width="400" alt="DC Motors Wiring">
  <img src="Images/Real_Robot/2_Motor_Driver_Close-Up.jpg" width="400" alt="Motor Driver">
</p>

### Chassis & Assembly Layout
<p align="center">
  <img src="Images/Real_Robot/3_Chassis_Underside_-_Electronics_Layout.jpg" width="288" alt="Underside Electronics">
  <img src="Images/Real_Robot/5_Fego_Robot_-_Top-Down_View.jpg" width="512" alt="Top-Down View">
</p>

### Final Assembled Platform
<p align="center">
  <img src="Images/Real_Robot/4_Fego_Robot_Assembled_-_Isometric_View.jpg" width="800" alt="Fully Assembled Fego Robot">
</p>

---

## 3. Software & Visualization
The robot's URDF, sensor data, and odometry are visualized in real-time using RViz.

<p align="center">
  <img src="Images/Rviz/rviz_screenshot.jpg" width="800" alt="RViz Visualization">
</p>

---

## 4. Real-World Testing
Watch the Fego mobile base navigating and demonstrating its differential drive system and `ros2_control` integration.

<p align="center">
  <em>Please hit the image to see the YouTube video!</em><br>
</p>
<p align="center">
  <a href="https://youtu.be/x8awXbyMQPw">
    <img src="Images/Real_Robot/6_Thumbnail_image.jpg" width="800" alt="Click to watch the Fego Robot video">
  </a>
</p>