#pragma once

#include <cmath>
#include <cstdint>
#include <vector>

namespace raycast {

struct Vec2 {
    double x;
    double y;
};

struct RayHit {
    double distance;
    int map_x;
    int map_y;
    int side; // 0 = NS wall, 1 = EW wall
    double wall_x;
};

class Engine {
public:
    Engine(int screen_w, int screen_h);

    void set_map(const std::vector<std::vector<int>>& map_data);
    RayHit cast_ray(Vec2 pos, Vec2 dir, Vec2 plane, double camera_x) const;
    void render_frame(Vec2 pos, Vec2 dir, Vec2 plane, std::vector<uint32_t>& buffer) const;

private:
    int width_;
    int height_;
    std::vector<std::vector<int>> map_;
};

} // namespace raycast
