#pragma once

#include <glm/glm.hpp>

namespace snd3D {
    class Projection {
        public:
            Projection(float aspectRatio, float fov);
            void changeAspectRatio(float newAspectRatio);
            void changeFov(float newFov);
            const glm::mat4& getProjectionMatrix();

        private:
            float fovY;         // Vertical field of view in degrees
            float aspectRatio;  // Aspect ratio (width/height) of the viewport
            float nearPlane;    // Distance to the near clipping plane
            float farPlane;     // Distance to the far clipping plane
            glm::mat4 matrix;

            void computeProjectionMatrix();
    };
}