#include <string>
#include <vector>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace FX {
    
    GLuint LoadShaderFromFile(GLenum eShaderType, const std::string& path);
    GLuint CreateProgram(const std::vector<GLuint>& shaderList);
    
    
    class Timer {
    public:
        Timer(float loopDuration): m_currTime(glutGet(GLUT_ELAPSED_TIME) / 1000.0f),
                m_accuTime(0.0f), m_secDuration(loopDuration), m_isPaused(false) {};

        void Update();

        float getAlpha();

    private:
        float m_currTime;
        float m_accuTime;
        float m_secDuration;

        bool m_isPaused;
    };


    inline float DegToRad(float fAngDeg) {
        const static float fDegToRad = 3.14159f * 2.0f / 360.0f;
        return fAngDeg * fDegToRad;
    }

    inline float Clamp(float fValue, float fMinValue, float fMaxValue) {
        if(fValue < fMinValue)
            return fMinValue;

        if(fValue > fMaxValue)
            return fMaxValue;

        return fValue;
    }

    glm::mat4 RotateX(float fAngDeg);
    glm::mat4 RotateY(float fAngDeg);
    glm::mat4 RotateZ(float fAngDeg);

    glm::mat4 Translate(const glm::vec3 &translateVec);
    
    glm::mat4 Scale(const glm::vec3 &scaleVec);

    inline float CalcFrustumScale(float FOVdeg) {
        float FOVrad = DegToRad(FOVdeg);
        return 1.0f / tan(FOVrad / 2.0f);
    }

}