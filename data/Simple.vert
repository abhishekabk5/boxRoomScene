#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec4 normal;

smooth out vec4 theColor;

uniform vec4 lightPos;

uniform mat4 modelToCamera;
uniform mat4 cameraToClip;

void main() {
    vec4 position_Model = modelToCamera * vec4(position);
    gl_Position = cameraToClip * position_Model;

    float costheta = dot(normalize(lightPos - position_Model), normal);
    costheta = clamp(costheta, 0.0, 1.0);
    theColor = color * costheta;
}