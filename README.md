# Path Finder Visualizer
'Path Finder Visualizer' is a desktop application written in C++ language that animates path-finding algorithms, where the user can choose between different algorithms and define obstacles on a 2D matrix.

## How To Build
The project uses CMake to build. The dependencies already included in the folder named 'deps' for Windows and Unix systems. MinGW-w64 is used for Windows system and GCC/G++ is used for Unix system.
```
:: At the project root directory
mkdir build
cd build
cmake ..
make
```
There will be executable file named 'PathFinderVisualizer' in the 'build' folder.

## Usage
### Controls
<pre>
S           : Switch between pens. (Obstacle - Start - Final)
C           : Clear cell matrix.
P           : Start simulation.
Left Mouse  : Paint cell with active pen.
Right Mouse : Clear cell when active pen is obstacle.
</pre>

## Demo
![](https://github.com/bahadirmaktav/Path-Finder-Visualizer/blob/main/demo/PathF%C4%B0nderDemo.gif)

## License
Created by Mehmet Bahadır Maktav on 03/12/22.<br/>
Copyright © 2022 Mehmet Bahadır Maktav. All rights reserved.