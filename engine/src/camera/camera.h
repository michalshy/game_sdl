#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//Defines possible options for camera movement. Used as an abstraction
enum Camera_Movement {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Camera 
{
	glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    glm::vec3 m_Position = {0.0f, 0.0f, 0.0f}; // Keep Z=0 for depth/sorting
    float m_Zoom = 1.0f; 
    float m_MovementSpeed = 5.0f; 
    
    glm::vec3 m_WorldUp = {0.0f, 1.0f, 0.0f}; // Up is fixed
    glm::vec3 m_Right = {1.0f, 0.0f, 0.0f};   // Right is fixed
public:
    // New constructor for 2D Orthographic Camera
    Camera(float width, float height); 
    
    // Core 2D movement methods
    void ProcessKeyboard(Camera_Movement direction, float delta_time);
    void ProcessMouseScroll(float yoffset, float mouse_x, float mouse_y);
    
    const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
    
    // Update the projection matrix (for window resize)
    void SetViewportSize(float width, float height);

    glm::mat4 GetViewMatrix();

private:
    void RecalculateViewProjectionMatrix();
    glm::vec3 ScreenToWorld(float screenX, float screenY);

};
