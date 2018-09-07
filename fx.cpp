#include "fx.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <exception>
#include <glload/gl_3_3.h>
#include <glutil/Shader.h>

namespace FX {

    GLuint LoadShaderFromFile(GLenum eShaderType, const std::string& path) {
        std::ifstream shaderFile(path.c_str());
        if(shaderFile.is_open()) {
            std::stringstream shaderData;
            shaderData << shaderFile.rdbuf();
            shaderFile.close();
            try {
                return glutil::CompileShader(eShaderType, shaderData.str());
            } catch (std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                throw;
            }
        } else {
            throw std::runtime_error("Couldn't open file " + path + "\n");
        }
    }

    GLuint CreateProgram(const std::vector<GLuint>& shaderList) {
        try {
            GLuint prog = glutil::LinkProgram(shaderList);
            std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
            return prog;
        } catch(std::exception& e) {
            std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
            std::cerr << e.what() << std::endl;
            throw;
        }
    }

}