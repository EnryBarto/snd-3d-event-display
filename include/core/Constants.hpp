#pragma once

#include <string_view>

namespace snd3D::constants {

    namespace limits {
        inline constexpr float PROJ_FARPLANE = 2000;
        inline constexpr float PROJ_NEARPLANE = 0.1f;
        inline constexpr float PROJ_FOVY_MAX = 115;
        inline constexpr float PROJ_FOVY_MIN = 45;
        inline constexpr float ZOOM_DISTANCE_MIN = 5;
        inline constexpr float GUI_FONT_SIZE_MIN = 0.5f;
        inline constexpr float ALPHA_VALUE_MIN = 0;
        inline constexpr float ALPHA_VALUE_MAX = 1;
        inline constexpr float EDGE_THICKNESS_MIN = 0.5f;
        inline constexpr float EDGE_THICKNESS_MAX = 5;
    }

    namespace defaults {
        inline constexpr float PROJ_FOVY = 80;
        inline constexpr bool SHOW_PIVOT = true;
        inline constexpr bool TRANSPARENCY = true;
        inline constexpr float EDGE_ALPHA_VALUE = 0.3f;
        inline constexpr float FACE_ALPHA_VALUE = 0.1f;
        inline constexpr float EDGE_THICKNESS = 1.5f;

        namespace window {
            inline constexpr int WIDTH = 1280;
            inline constexpr int HEIGHT = 720;
            inline constexpr const char* NAME = "SND 3D Event Display";
            inline constexpr bool VSYNC = true;
        }
    }

    namespace paths {
        inline constexpr std::string_view SHADER = "assets/shaders/";
        inline constexpr std::string_view SCREENSHOT = "output/";
    }

    namespace factors {
        inline constexpr float GUI_FONT_RESIZE = 1.1f;
        inline constexpr float ZOOM = 0.1f;
        inline constexpr float ROTATION_SPEED = 2;
        inline constexpr float PERPENDICULAR_PAN = 20;
    }

    namespace sizes {
        inline constexpr float GUI_FONT = 0.8f;
        inline constexpr float FONT = 30;
        inline constexpr int ANCHOR = 15;
        inline constexpr float PIVOT = 5;
        inline constexpr int PADDING = 10;
    }
}
