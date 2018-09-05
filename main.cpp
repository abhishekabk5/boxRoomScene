
#include <vector>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <../../framework/framework.h>

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
const float depthZFar = 3.0f;

glm::mat4 cameraToClipMatrix;

void InitializeProgram() {
    std::vector<GLuint> shaderList;

    shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "Simple.vert"));
    shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "Simple.frag"));

    simple.theProgram = Framework::CreateProgram(shaderList);

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

GLuint g_vertexArrayBuffer;
GLuint g_vertexIndexBuffer;
GLuint g_vertexArrayObject;

const GLfloat g_fVertices[] = {
	0.5f, 0.5f, -0.75f, 1.0f,
    0.5f, -0.5f, 0.75f, 1.0f,
    -0.5f, 0.5f, -0.75f, 1.0f,
    -0.5f, -0.5f, 0.75f, 1.0f,
};

const GLshort g_sIndices[] = {
    0, 1, 2,
    2, 1, 3
};

void InitializeVertexBuffer() {
    glGenBuffers(1, &g_vertexArrayBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, g_vertexArrayBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_fVertices), g_fVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &g_vertexIndexBuffer);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_vertexIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_sIndices), g_sIndices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void InitializeVao() {
    glGenVertexArrays(1, &g_vertexArrayObject);
    glBindVertexArray(g_vertexArrayObject);

    glBindBuffer(GL_ARRAY_BUFFER, g_vertexArrayBuffer);
    glBindVertexArray(g_vertexArrayObject);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_vertexIndexBuffer);
    glBindVertexArray(0);
}

void init() {
    InitializeProgram();
    InitializeVertexBuffer();
    InitializeVao();

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
    glClearDepth(3.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(simple.theProgram);
    glBindVertexArray(g_vertexArrayObject);
    {
        glm::mat4 translate(1.0f);
        translate[3].z = -2.0f;
        glUniformMatrix4fv(simple.modelToCameraUniform, 1, GL_FALSE, glm::value_ptr(translate));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    }
    glBindVertexArray(0);
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