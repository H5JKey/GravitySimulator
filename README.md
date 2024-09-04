# Gravity Simulator

Its a simple gravity and collision simulation program based on Newton's law of gravity and law of conservation of momentum and energy written in c++ with ImGui and SFML.
In this program you can:
  1. Add and delete objects
  2. Focus on objects and change it's properties
  3. Watch orbits and center of gravity
  4. Saving and loading configures
  5. Slow down and speed up global time
Also there is a console (F1 to use) with following commands:
  1. /fill {x1} {y1} {x2} {y2} {dx} {dy} - fill from (x1,y1) to (x2,y2) every (dx,dy) with copied object
  2. /add {x} {y} - add new object from copied
  3. /force
     3.1. /force add {x} {y} {value} - add new constant force for all objects with direction (x,y)
     3.2. /force add {x} {y} {value}m - add new constant acceleration for all objects with direction (x,y)
     3.3. /force pop - delete last added force
     3.4. /force clear - clear all added forces
# Preview
![image](https://github.com/H5JKey/GravitySimulator/blob/master/Preview.png "Preview")
