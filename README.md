# raycast-engine

Early-stage development of a modern C++20 DDA (Digital Differential Analyzer) raycasting rendering engine.

### Features

* Fast grid-based DDA ray traversal for 2D spatial layouts.
* Fisheye distortion compensation using perpendicular camera plane projection.
* Sub-pixel wall hit detection and texture coordinate interpolation.
* Headless terminal framebuffer visualizer for continuous integration.

### Build

```bash
mkdir build && cd build
cmake ..
cmake --build .
./raycast_demo
```
