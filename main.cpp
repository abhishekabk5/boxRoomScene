
#include <iostream>
#include <vector>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <../../framework/mesh.h>
#include "fx.h"

struct programData {
    GLuint theProgram;
    GLuint modelToCameraUniform;
    GLuint cameraToClipUniform;
};

programData simple;

inline float CalcFrustumScale(float FOVdeg) {
    float FOVrad = FOVdeg * 3.14159f / 180.0f;
    return 1.0f / tan(FOVrad / 2.0f);
}

const float frustumScale = CalcFrustumScale(45.0f);

const float depthZNear = 1.0f;
const float depthZFar = 45.0f;

glm::mat4 cameraToClipMatrix;

void InitializeProgram() {
    std::vector<GLuint> shaderList;

    shaderList.push_back(FX::LoadShaderFromFile(GL_VERTEX_SHADER, "data\\Simple.vert"));
    shaderList.push_back(FX::LoadShaderFromFile(GL_FRAGMENT_SHADER, "data\\Simple.frag"));

    simple.theProgram = FX::CreateProgram(shaderList);

    cameraToClipMatrix[0].x = frustumScale;
    cameraToClipMatrix[1].y = frustumScale;
    cameraToClipMatrix[2].z = (depthZNear + depthZFar) / (depthZNear - depthZFar);
    cameraToClipMatrix[2].w = -1.0f;
    cameraToClipMatrix[3].z = (2 * depthZNear * depthZFar) / (depthZNear - depthZFar);
    
    glUseProgram(simple.theProgram);
    simple.modelToCameraUniform = glGetUniformLocation(simple.theProgram, "modelToCamera");
    simple.cameraToClipUniform = glGetUniformLocation(simple.theProgram, "cameraToClip");
    glUniformMatrix4fv(simple.cameraToClipUniform, 1, GL_FALSE, glm::value_ptr(cameraToClipMatrix));
    glUseProgram(0);
}

Framework::Mesh *g_pCubeMesh = NULL;

void init() {
    InitializeProgram();

    try {
        g_pCubeMesh = new Framework::Mesh("UnitCube.xml");
    } catch(std::exception& except) {
        std::cerr << except.what() << std::endl;
        throw;
    }

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(depthZNear, depthZFar);
    glEnable(GL_DEPTH_CLAMP);
}

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(45.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(simple.theProgram);
    {
        glm::mat4 translate(1.0f);
        translate[3].z = -20.0f;
        glUniformMatrix4fv(simple.modelToCameraUniform, 1, GL_FALSE, glm::value_ptr(translate));
        g_pCubeMesh->Render();
    }
    glUseProgram(0);

    glutPostRedisplay();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    cameraToClipMatrix[0].x = frustumScale * (h / (float)w);

    glUseProgram(simple.theProgram);
    glUniformMatrix4fv(simple.cameraToClipUniform, 1, GL_FALSE, glm::value_ptr(cameraToClipMatrix));
    glUseProgram(0);

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
            glutLeaveMainLoop();
            return;
    }
}

unsigned int defaults(unsigned int displayMode, int &width, int &height) { return displayMode; }