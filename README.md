# Shape Detection with OpenCV

This is a simple C++ program that detects basic geometric shapes (triangles, rectangles, squares, pentagons, circles) in an image using **OpenCV**.  
It uses **Canny edge detection**, **contour approximation**, and **Hough Circle Transform** for detection.

## Features
- Detects:
  - Triangle
  - Square
  - Rectangle
  - Pentagon
  - Circle
- Uses both **contour approximation** and **Hough Circle Transform** for better circle detection
- Displays:
  - Edges
  - Contours
  - Final labeled shapes

## Requirements
- OpenCV 4.x
- C++17 (or later)
- CMake (if you want to build cross-platform)

## How to Build & Run

```bash
# Clone repository
git clone https://github.com/yourusername/shape-detection
cd shape-detection

# Build with CMake
mkdir build && cd build
cmake ..
make

# Run
./shape_detection
```

Or compile manually:

```bash
g++ main.cpp -o shape_detection `pkg-config --cflags --libs opencv4`
./shape_detection
```

## Usage
1. Place your test image in the project folder.
2. Update the `imread` path in `main.cpp` to your image file.
3. Run the program to see detected shapes.

## Example Output
![Example Detected Shapes](example.png)

```
Detected Shapes:  
- Green contours drawn around shapes  
- Labels like "Square", "Triangle", "Circle" on detected objects
```
