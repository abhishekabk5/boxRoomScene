
#include <vector>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <../../framework/framework.h>

GLuint theProgram;

void InitializeProgram() {
    std::vector<GLuint> shaderList;

    shaderList.push_back(Framework::CreateShader(GL_VERTEX_SHADER, "Simple.vert"));
    shaderList.push_back(Framework::CreateShader(GL_FRAGMENT_SHADER, "Simple.frag"));

    theProgram = Framework::CreateProgram(shaderList);
}

GLuint g_vertexArrayBuffer;
GLuint g_vertexIndexBuffer;
GLuint g_vertexArrayObject;

const GLfloat g_fVertices[16] = {
    0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, 1.5f, 1.0f, 1.0f,
    1.5f, 0.5f, 1.0f, 1.0f,
    1.5f, 1.5f, 1.0f, 1.0f,
};

const GLshort g_sIndices[6] = {
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
}

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(theProgram);
    glBindVertexArray(g_vertexArrayObject);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(0);
    glUseProgram(0);

    glutSwapBuffers();
}

void reshape(int w, int h) {
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