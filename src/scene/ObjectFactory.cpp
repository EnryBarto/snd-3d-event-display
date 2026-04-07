#include "scene/ObjectFactory.hpp"

#include <vector>

#include <glm/gtc/constants.hpp>

#include "scene/Mesh.hpp"
#include "scene/Node.hpp"

using namespace std;
using namespace glm;

namespace snd3D {
    ObjectFactory::ObjectFactory() {
        this->sphere = shared_ptr<Mesh>(ObjectFactory::createSphere());
    }

    Object* ObjectFactory::getSphere() {
        vector<shared_ptr<Mesh>> meshes;
        meshes.push_back(this->sphere);
        Node* node = new Node("Sphere", meshes);
        return new Object(node);
    }

    Mesh* ObjectFactory::createSphere(vec4 baseColor) {
        vector<vec3> vertices;
        vector<vec4> colors;
        vector<GLuint> indices;
        vector<vec3> normals;

        vec3 center = vec3(0.0, 0.0, 0.0);
        vec3 radius = vec3(1.0, 1.0, 1.0);

        int stacks = 10;  // Number of subdivisions along the Y axis
        int slices = 10;  // Number of subdivisions along the X axis

        // Calc The Vertices
        for (int i = 0; i <= stacks; ++i) {
            float V = i / (float)stacks;
            float phi = V * glm::pi<float>();

            for (int j = 0; j <= slices; ++j) {
                float U = j / (float)slices;
                float theta = U * (2.0f * glm::pi<float>());

                // Spherical coordinates
                float x = center.x + radius.x * (cosf(theta) * sinf(phi));
                float y = center.y + radius.y * cosf(phi);
                float z = center.z + radius.z * (sinf(theta) * sinf(phi));

                vertices.push_back(vec3(x, y, z));
                colors.push_back(baseColor);

                // Normal (for unit sphere normal == position) normalized for safety
                normals.push_back(normalize(vec3(x, y, z)));
            }
        }

        // Calc The Index Positions (two triangles per quad)
        for (int i = 0; i < stacks; ++i) {
            for (int j = 0; j < slices; ++j) {
                int first = (i * (slices + 1)) + j;
                int second = first + slices + 1;

                indices.push_back(first);
                indices.push_back(second);
                indices.push_back(first + 1);

                indices.push_back(second);
                indices.push_back(second + 1);
                indices.push_back(first + 1);
            }
        }

        return new Mesh("SphereGeometry", vertices, colors, normals, indices, baseColor);
    }
}
