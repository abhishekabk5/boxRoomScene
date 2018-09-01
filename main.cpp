

#include <glload/gl_3_3.h>

GLuint theProgram;

void InitializePrograms() {
    

}

GLfloat g_fVertices[16] = {
    0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, 1.0f, 1.0f,
};

GLshort g_iIndices[6] = {
    0, 1, 2,
    2, 1, 3
};

void init() {
    InitializePrograms();


}

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(theProgram);
}

void reshape(int w, int h) {

}

void keyboard(unsigned char key, int x, int y) {

}

unsigned int defaults(unsigned int displayMode, int &width, int &height) { return displayMode; }