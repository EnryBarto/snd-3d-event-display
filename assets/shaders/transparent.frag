#version 330 core
in vec4 color;
in vec3 localPos;
in vec3 barycentric; // The interpolation will fill the correct barycentric coordinates for each fragment

out vec4 FragColor;

void main() {
    vec3 d = fwidth(barycentric); // Calculate the intensity of change (derivative)
    vec3 a3 = smoothstep(vec3(0.0), d * 1.5, barycentric); // Create a smooth gradient based on barycentric distance
    float edgeFactor = min(min(a3.x, a3.y), a3.z); // Find the closest edge to determine the wireframe factor

    float finalAlpha = mix(0.3, 0.1, edgeFactor); // Higher alpha for edges and lower for faces

    FragColor = vec4(vec3(color), finalAlpha); // Output the color replacing the computed transparency
}