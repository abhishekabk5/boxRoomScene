#include "fx.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <exception>
#include <glload/gl_3_3.h>
#include <glutil/Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    void Timer::Update() {
        float fTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        
        if(m_isPaused) {
            m_currTime = fTime;
            return;
        }

        m_accuTime += m_currTime - fTime;
        m_currTime = fTime;

        return;
    }

    float Timer::getAlpha() {
        return fmodf(m_accuTime, m_secDuration) / m_secDuration;
    }

    glm::mat4 RotateX(float fAngDeg) {
        float fAngRad = DegToRad(fAngDeg);
        float fCos = cosf(fAngRad);
        float fSin = sinf(fAngRad);

        glm::mat3 theMat(1.0f);
        theMat[1].y = fCos; theMat[2].y = -fSin;
        theMat[1].z = fSin; theMat[2].z = fCos;

        return glm::mat4(theMat);
    }

    glm::mat4 RotateY(float fAngDeg) {
        float fAngRad = DegToRad(fAngDeg);
        float fCos = cosf(fAngRad);
        float fSin = sinf(fAngRad);

        glm::mat3 theMat(1.0f);
        theMat[0].x = fCos; theMat[2].x = fSin;
        theMat[0].z = -fSin; theMat[2].z = fCos;

        return glm::mat4(theMat);
    }

    glm::mat4 RotateZ(float fAngDeg) {
        float fAngRad = DegToRad(fAngDeg);
        float fCos = cosf(fAngRad);
        float fSin = sinf(fAngRad);

        glm::mat3 theMat(1.0f);
        theMat[0].x = fCos; theMat[1].x = -fSin;
        theMat[0].y = fSin; theMat[1].y = fCos;

        return glm::mat4(theMat);
    }

    glm::mat4 Translate(const glm::vec3 &translateVec) {
        glm::mat4 translateMat(1.0f);
        translateMat[3] = glm::vec4(translateVec, 1.0f);

        return translateMat;
    }

    glm::mat4 Scale(const glm::vec3 &scaleVec) {
        glm::mat4 scaleMat(1.0f);
        scaleMat[0].x = scaleVec.x;
        scaleMat[1].y = scaleVec.y;
        scaleMat[2].z = scaleVec.z;

        return scaleMat;
    }

}