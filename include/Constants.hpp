#pragma once

#include <string_view>

namespace snd3D::constants {

    namespace limits {
        inline constexpr float PROJ_FARPLANE = 2000;
        inline constexpr float PROJ_NEARPLANE = 0.1f;
        inline constexpr float PROJ_FOVY_MAX = 115;
        inline constexpr float PROJ_FOVY_MIN = 45;
        inline constexpr float ZOOM_DISTANCE_MIN = 50;
        inline constexpr float GUI_FONT_SIZE_MIN = 0.75f;
    }

    namespace defaults {
        inline constexpr float PROJ_FOVY = 80;
        inline constexpr bool SHOW_PIVOT = true;

        namespace window {
            inline constexpr int WIDTH = 1280;
            inline constexpr int HEIGHT = 720;
            inline constexpr const char* NAME = "SND 3D Event Display";
            inline constexpr bool VSYNC = true;
        }
    }

    namespace paths {
        inline constexpr std::string_view SHADER_FOLDER = "assets/shaders/";
    }

    namespace factors {
        inline constexpr float GUI_FONT_RESIZE = 1.1f;
        inline constexpr float ZOOM = 0.1f;
        inline constexpr float ROTATION_SPEED = 2;
    }

    namespace sizes {
        inline constexpr float GUI_FONT = 1.5f;
        inline constexpr int ANCHOR = 15;
        inline constexpr float PIVOT = 5;
    }
}
