#pragma once

#include <string_view>

namespace snd3D::constants {

    namespace window {
        inline constexpr int DEFAULT_WIDTH = 1280;
        inline constexpr int DEFAULT_HEIGHT = 720;
        inline constexpr const char* NAME = "SND 3D Event Display";
        inline constexpr bool DEFAULT_VSYNC = true;
    }

    namespace limits {
        inline constexpr float PROJ_FARPLANE = 2000;
        inline constexpr float PROJ_NEARPLANE = 0.1f;
        inline constexpr float PROJ_FOVY_DEFAULT = 80;
        inline constexpr float PROJ_FOVY_MAX = 115;
        inline constexpr float PROJ_FOVY_MIN = 45;
        inline constexpr float ZOOM_DISTANCE_MIN = 50;
    }

    namespace paths {
        inline constexpr std::string_view SHADER_FOLDER = "assets/shaders/";
    }

    inline constexpr int ANCHOR_SIZE = 15;
    inline constexpr float ZOOM_FACTOR = 0.1f;
}
