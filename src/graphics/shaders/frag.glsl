#version 330 core

in vec3 vertexColor; // Received color from vertex shader
out vec4 FragColor;  // Final output color

void main() {
    FragColor = vec4(vertexColor, 1.0); // Use vertex color as fragment color
}

