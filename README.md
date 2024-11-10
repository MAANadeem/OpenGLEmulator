# GameBoy Advance Emulator

A high-performance **GameBoy Advance (GBA) emulator** built in **C++** with **OpenGL**, **GLFW**, and **GLEW**. This emulator faithfully replicates the GBA’s hardware, featuring cycle-accurate CPU emulation and a GPU-based rendering pipeline that enhances graphical fidelity through custom shaders.

## Key Features

- **Cycle-Accurate ARM7TDMI CPU Emulation**: Supports over 100 instructions, ensuring high compatibility and accurate performance with real GBA hardware.
- **Enhanced GPU-Based Rendering**: Emulates GBA graphical processing using **OpenGL** and **GLSL shaders** with custom sprite scaling and filtering for improved visuals.
- **Optimized Speed and Memory Management**: Balanced for both speed and memory efficiency, providing smooth gameplay even on resource-limited systems.
- **Cross-Platform Compatibility**: Runs on multiple platforms thanks to **GLFW** and **GLEW**.

## Getting Started

### Prerequisites

- **C++ Compiler** supporting C++11 or later
- **OpenGL 3.3+**
- **GLFW** and **GLEW** libraries

### Installation and Execution

1. Clone the repository:
   ```bash
   git clone https://github.com/MAANadeem/GBA-Emulator.git
   cd GBA-Emulator
2. Install dependencies (GLFW, GLEW) if not already installed.
3. Build the project
4. Run the executable

### Controls
- D-Pad: Arrow keys
- A / B Buttons: Z and X
- Start / Select: Enter and Shift
- L / R Buttons: A and S

## Technical Overview
### Architecture
This emulator emulates GBA hardware at a low level, featuring:
- ARM7TDMI CPU Emulation: Cycle-accurate emulation of the ARM7TDMI processor, implementing over 100 unique instructions.
- GPU Rendering Pipeline: A custom GPU pipeline using OpenGL and GLSL shaders for sprite scaling, texture filtering, and color correction, emulating GBA graphics hardware.

### Performance Optimization
The emulator is optimized for efficient memory usage and high-speed execution, balancing CPU and GPU load to maintain smooth gameplay. Cycle-accurate execution ensures compatibility across a wide range of GBA titles.

## Roadmap
### Planned Features:
- Support for additional GBA hardware features (e.g., audio channels)
- Save states and save file compatibility
- User-configurable controls

## License
This project is licensed under the GNU General Public License. See LICENSE for more details.
