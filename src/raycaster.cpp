#include "raycast/raycaster.hpp"

namespace raycast {

Engine::Engine(int screen_w, int screen_h) : width_(screen_w), height_(screen_h) {}

void Engine::set_map(const std::vector<std::vector<int>>& map_data) {
    map_ = map_data;
}

RayHit Engine::cast_ray(Vec2 pos, Vec2 dir, Vec2 plane, double camera_x) const {
    double ray_dir_x = dir.x + plane.x * camera_x;
    double ray_dir_y = dir.y + plane.y * camera_x;

    int map_x = static_cast<int>(pos.x);
    int map_y = static_cast<int>(pos.y);

    double delta_dist_x = (ray_dir_x == 0) ? 1e30 : std::abs(1.0 / ray_dir_x);
    double delta_dist_y = (ray_dir_y == 0) ? 1e30 : std::abs(1.0 / ray_dir_y);

    double side_dist_x;
    double side_dist_y;
    int step_x;
    int step_y;

    if (ray_dir_x < 0) {
        step_x = -1;
        side_dist_x = (pos.x - map_x) * delta_dist_x;
    } else {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - pos.x) * delta_dist_x;
    }

    if (ray_dir_y < 0) {
        step_y = -1;
        side_dist_y = (pos.y - map_y) * delta_dist_y;
    } else {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - pos.y) * delta_dist_y;
    }

    int hit = 0;
    int side = 0;
    int max_steps = 64;

    while (hit == 0 && max_steps-- > 0) {
        if (side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;
        } else {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;
        }

        if (map_x >= 0 && map_x < static_cast<int>(map_.size()) &&
            map_y >= 0 && map_y < static_cast<int>(map_[0].size())) {
            if (map_[map_x][map_y] > 0) {
                hit = 1;
            }
        }
    }

    double perp_wall_dist;
    if (side == 0) {
        perp_wall_dist = (side_dist_x - delta_dist_x);
    } else {
        perp_wall_dist = (side_dist_y - delta_dist_y);
    }

    double wall_x;
    if (side == 0) {
        wall_x = pos.y + perp_wall_dist * ray_dir_y;
    } else {
        wall_x = pos.x + perp_wall_dist * ray_dir_x;
    }
    wall_x -= std::floor(wall_x);

    return RayHit{perp_wall_dist, map_x, map_y, side, wall_x};
}

void Engine::render_frame(Vec2 pos, Vec2 dir, Vec2 plane, std::vector<uint32_t>& buffer) const {
    buffer.resize(width_ * height_, 0);
    for (int x = 0; x < width_; ++x) {
        double camera_x = 2.0 * x / static_cast<double>(width_) - 1.0;
        RayHit hit = cast_ray(pos, dir, plane, camera_x);

        int line_height = static_cast<int>(height_ / (hit.distance <= 0 ? 0.1 : hit.distance));
        int draw_start = -line_height / 2 + height_ / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + height_ / 2;
        if (draw_end >= height_) draw_end = height_ - 1;

        uint32_t color = (hit.side == 1) ? 0x00888888 : 0x00CCCCCC;
        for (int y = draw_start; y <= draw_end; ++y) {
            buffer[y * width_ + x] = color;
        }
    }
}

} // namespace raycast
