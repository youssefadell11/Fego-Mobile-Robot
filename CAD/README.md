\# Fego Mobile Robot CAD



Welcome to the open-source CAD folder for the \*\*Fego Mobile Robot\*\*! This is a 2-Wheel Drive (2WD) differential mobile robot designed from the bottom-up using \*\*`Fusion 360`\*\*. 



This folder contains all the mechanical CAD files, manufacturing 2D profiles, and 3D meshes required to build the physical robot or simulate it in ROS 2 (RViz/Gazebo).



\## 🗂️ CAD Folder Structure

The hardware files in this repository are organized to help you find exactly what you need, whether you want to 3D print the whole robot, cut the chassis, or just borrow a sensor model.



\---

\### \*\*`1\_Full\_Assembly/`\*\*: 

\#### Contains the complete robot model.

&#x20; \* `.step` - Universal 3D CAD file (Open in SolidWorks, Inventor, etc.)

&#x20; \* `.f3d` - Native Fusion 360 archive with complete design timeline and linked components.

\---

\### \*\*`2\_Components/`\*\*: 

\#### Individual `.step` files for standard third-party hardware. You can use these files for your own custom robot designs!

&#x20; \* Inter Profile

&#x20; \* Outer Profile

&#x20; \* Bracket 25mm

&#x20; \* RPLidar A1M8

&#x20; \* JGA25-370 TT Geared Motors

&#x20; \* 65mm Robot Wheels

&#x20; \* Caster Ball Wheel

&#x20; \* Webcam Module

\---

\### \*\*`3\_Manufacture\_Files/`\*\*: 

\#### 2D profiles for fabricating the custom parts.

&#x20; \* `.dxf` files for laser cutting or CNC routing the acrylic top and bottom plates.

&#x20; \* `.stl` file for 3D print the Bracket 25mm.

\---

\### \*\*`4\_Meshes/`\*\*:

\#### 3D meshes required to build the physical robot or simulate it in ROS 2 (RViz/Gazebo)

\* lidar.stl

\* base\_link.stl

\* camera.stl

\* caster.stl

\* wheel.stl

\---

\### \*\*`4\_Renders/`\*\*: 

\#### High-quality photorealistic images of the final assembly.

\---

\## 🤖 Main Components List

To build the electrical and sensor stack of this robot, the following major components are used:

\* \*\*Controller:\*\* Arduino Mega (or Uno) \& H-Bridge Motor Driver

\* \*\*Actuators:\*\* 2x JGA25-370 TT Geared DC Motors with encoders

\* \*\*Wheels:\*\* 2x 65mm Rubber Tires with plastic rims, 1x Front Caster Ball Wheel

\* \*\*Vision / LiDAR:\*\* RPLIDAR A1M8 \& Forward-facing USB Webcam

\* \*\*Chassis:\*\* 2x Custom Acrylic Plates (Top and Bottom)



\## 🔩 Hardware \& Fasteners Bill of Materials

Below is the required hardware matrix for assembling the chassis and mounting the electronics.



| Subsystem / Assembly | Screws Required | Nuts Required | Spacers / Extras |

| :--- | :--- | :--- | :--- |

| \*\*Main Chassis (Plates 1 \& 2)\*\* | 4x M3x50 | 12x M3 | - |

| \*\*Motor Brackets\*\* | 8x M4 | 8x M4 | - |

| \*\*TT Motors\*\* | 4x M3 | - | - |

| \*\*Caster Wheel\*\* | 2x M3 | 2x M3 | - |

| \*\*Arduino \& H-Bridge\*\* | 8x M3 | 8x M3 | 8x M3 Spacers |

