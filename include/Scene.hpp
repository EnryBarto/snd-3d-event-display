#pragma once

#include <memory>

#include "Camera.hpp"
#include "Projection.hpp"
#include "Object.hpp"

namespace snd3D {
	class Scene {
		public:
			Scene();
			void render();

		private:
			std::unique_ptr<Camera> camera;
			std::unique_ptr<Projection> projection;
			std::unique_ptr<Object> obj;
	};
}