#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

smooth out vec4 theColor;

uniform mat4 modelToCamera;
uniform mat4 cameraToClip;

void main() {
    gl_Position = cameraToClip * modelToCamera * vec4(position);

    theColor = color;
}