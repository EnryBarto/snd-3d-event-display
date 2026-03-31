#pragma once

#include <glm/glm.hpp>

namespace snd3D {
	class Camera {
		public:
			Camera(glm::vec3 position, glm::vec3 target);
			const glm::mat4& getViewMatrix();
			const glm::vec3& getPosition();
			void rotateAroundCameraTarget(glm::vec3 axis, float angle);

		private:
			glm::vec3 position;  // Camera position in 3D space
			glm::vec3 target;    // Point the camera is looking at
			glm::vec3 upVector;  // Up direction vector for the camera

			glm::mat4 viewMatrix; // Buffered view matrix to not recompute it for each frame, but it has to be kept updated
	};

}