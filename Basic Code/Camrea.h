#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class Camrea_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float CAMREA_SPEED = 2.5f;
const float SENSITIVITY = 0.01f;

class Camrea {
public:

    Camrea(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
        :  m_speed(CAMREA_SPEED), m_sensitivity(SENSITIVITY) {
       
        m_position = position;
        m_world_up = up;
        m_front = glm::vec3(0.0f, 0.0f, -1.0f);
        m_yaw = yaw;
        m_pitch = pitch;
        updataCamreaVector();
    }

    Camrea(float posX, float posY, float posZ, float upX, float upY, float upZ, float pitch, float yaw) 
        :m_speed(CAMREA_SPEED), m_sensitivity(SENSITIVITY){
        m_position = glm::vec3(posX, posY, posZ);
        m_world_up = glm::vec3(upX, upY, upZ);
        m_pitch = pitch;
        m_yaw = yaw;
        updataCamreaVector();
    }

    glm::mat4 GetViewMatrix() {
        return glm::lookAt(m_position, m_position + this->m_front, m_up);
    }



    void MouseControlView(float xoffset, float yoffset, GLboolean constrainPitch);
        
private:
    glm::vec3 m_position;
    glm::vec3 m_up;
    glm::vec3 m_world_up;
    glm::vec3 m_front;
    glm::vec3 m_right;
    float m_speed;
    float m_yaw;
    float m_pitch;
    float m_sensitivity;
    void updataCamreaVector();
};