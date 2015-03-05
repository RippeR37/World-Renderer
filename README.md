# World-Renderer

World renderer capable of rendering both 2D and 3D maps form loaded elevation data (.hgt files from SRTM). 
Written in C++11 and OpenGL 3.3 Core Profile. 3D rendering uses dynamic LoD to render fast and accurate. Automatic mode for LoD (keeps >100fps at all time) implemented.


Requirements
------------

- C++11 supporting compiler (Visual Studio 2012 project provided)
- GLFW library (tested on version 3.0.4)
- GLEW library (tested on version 1.11.0)
- GLM  library (testen on version 0.9.5.4)
- [Utility Library](https://github.com/RippeR37/Utility-Library)


Controls
--------

- Tab - switch between 2D and 3D
- W/S - (3D) move forward/backward
- A/D - (3D) strafe left/right
- LCtrl / Space - (3D) move down/up
- Arrows - (2D) move map up/down/left/right
- Mouse wheel - (2D) zoom in/out
- Mouse drag - (2D) move map
- [1]-[9] - (3D) switching LoD factor to const value
- [0] - (3D) enabling automatic LoD


Usage
-----
Application supports loading data from files given as arguments. Heightmaps (.hgt files) should be placed in /bin/assets/heightmaps/ folder.
Supported arguments:

- single-file arguments (fileNames without extension)
- range arguments (-r startX startY endX endY)

Example:
Project.exe N10E010 N15W040 -r 20 20 21 22  
  
will load files:  
* N10E010.hgt
* N15W040.hgt
* N20E020.hgt
* N20E021.hgt
* N 21E020.hgt
* N21E021.hgt
* N22E020.hgt
* N22E021.hgt
