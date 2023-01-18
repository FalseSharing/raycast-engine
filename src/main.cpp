#include "raycast/raycaster.hpp"
#include <iostream>
#include <vector>

int main() {
    std::cout << "[raycast-engine v0.9.2] Initializing DDA core...\n";

    raycast::Engine engine(80, 24);
    std::vector<std::vector<int>> sample_map = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };
    engine.set_map(sample_map);

    raycast::Vec2 pos{2.5, 2.5};
    raycast::Vec2 dir{-1.0, 0.0};
    raycast::Vec2 plane{0.0, 0.66};

    std::vector<uint32_t> framebuffer;
    engine.render_frame(pos, dir, plane, framebuffer);

    std::cout << "Rendered frame successfully (" << framebuffer.size() << " pixels).\n";
    return 0;
}
