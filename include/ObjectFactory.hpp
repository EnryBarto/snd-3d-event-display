#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Object.hpp"

namespace snd3D {
    class ObjectFactory {
        public:
            ObjectFactory();
            Object* getSphere(glm::vec4 baseColor = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f));

        private:
            static Mesh* createSphere(glm::vec4 baseColor = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f));
            std::shared_ptr<Mesh> sphere;
    };
}