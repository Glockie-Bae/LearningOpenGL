#include"Camrea.h"


void Camrea::MouseControlView(float xoffset, float yoffset, GLboolean constrainPitch= true)
{
    xoffset *= this->m_sensitivity;
    yoffset *= this->m_sensitivity;

    this->m_yaw += xoffset;
    this->m_pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (this->m_pitch > 89.0f)
            this->m_pitch = 89.0f;
        if (this->m_pitch < -89.0f)
            this->m_pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    this->updataCamreaVector();
}


void Camrea::updataCamreaVector()
{
	glm::vec3 front(1.0f);
	front.x = cos(glm::radians(this->m_pitch)) * cos(glm::radians(this->m_yaw));
	front.y = cos(glm::radians(this->m_pitch));
	front.z = cos(glm::radians(this->m_pitch)) * sin(glm::radians(this->m_yaw));

	this->m_front = glm::normalize(front);
	this->m_right = glm::normalize(glm::cross(this->m_front, this->m_world_up));
	this->m_up = glm::normalize(glm::cross(this->m_right, this->m_front));
}
