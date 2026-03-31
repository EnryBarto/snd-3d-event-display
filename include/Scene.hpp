#pragma once

#include <memory>

#include "Camera.hpp"
#include "Projection.hpp"
#include "Object.hpp"
#include "WindowManager.hpp"

namespace snd3D {
	class Scene {

		friend class Callbacks; // Must be able to access the camera

		public:
			Scene(WindowManager& winMan);
			void update();
			void render();

		private:
			WindowManager& windowManager; // Owned by App, keep reference to spped up access
			std::unique_ptr<Camera> camera;
			std::unique_ptr<Projection> projection;
			std::unique_ptr<Object> obj;
	};
}