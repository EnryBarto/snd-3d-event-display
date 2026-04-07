#pragma once

#include <glm/glm.hpp>

namespace snd3D {
    class Camera {
        public:
            Camera(glm::vec3 position, glm::vec3 target);
            const glm::mat4& getViewMatrix();
            const glm::vec3& getPosition();
            const glm::vec3& getTarget();
            void rotateAroundAxis(glm::vec3 axis, float angle);
            void rotateByAngles(float deltaAngleX, float deltaAngleY);
            void rotateTrackball(glm::vec3 origin, glm::vec3 destination);
            void moveParallel(float deltaX, float deltaY);
            void movePerpendicular(float deltaX, float deltaY);
            void zoom(float offset);
            bool isChanged();
            void reset();

        private:
            glm::vec3 position;  // Camera position in 3D space
            glm::vec3 target;    // Point the camera is looking at
            glm::vec3 upVector;  // Up direction vector for the camera

            // Used to reset to default values
            glm::vec3 startPosition;
            glm::vec3 startTarget;
            glm::vec3 startUpVector;

            glm::mat4 viewMatrix; // Buffered view matrix to not recompute it for each frame, but it has to be kept updated
            bool changed;
            void recomputeMatrix(); // Use it to recompute the buffered matrix, because it updates the changed flag
    };

}