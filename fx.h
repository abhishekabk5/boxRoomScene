#include <string>
#include <vector>
#include <glload/gl_3_3.h>

namespace FX {

    GLuint LoadShaderFromFile(GLenum eShaderType, const std::string& path);
    GLuint CreateProgram(const std::vector<GLuint>& shaderList);

}