#include "camera.h"

constexpr float SPEED = 10.0f;

Camera::Camera(float width, float height)
    : m_Zoom(1.0f), m_MovementSpeed(SPEED) 
{ 
    m_ProjectionMatrix = glm::ortho(
        0.0f, width * m_Zoom, 
        0.0f, height * m_Zoom, 
        -1.0f, 1.0f
    );
    m_ViewMatrix = glm::mat4(1.0f);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Camera::SetViewportSize(float width, float height)
{
    m_ProjectionMatrix = glm::ortho(
        0.0f, width * m_Zoom, 
        0.0f, height * m_Zoom, 
        -1.0f, 1.0f
    );
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Camera::RecalculateViewProjectionMatrix()
{
    // Create a matrix: Translate by position, Scale by zoom
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
                          glm::scale(glm::mat4(1.0f), glm::vec3(m_Zoom, m_Zoom, 1.0f));

    // the View Matrix is the inverse of the camera's world transform
    m_ViewMatrix = glm::inverse(transform); 
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

glm::mat4 Camera::GetViewMatrix()
{
    RecalculateViewProjectionMatrix();
    return m_ViewMatrix;
}

void Camera::ProcessKeyboard(Camera_Movement direction, float delta_time)
{
    float velocity = m_MovementSpeed * delta_time * m_Zoom;
    
    if (direction == UP)
        m_Position.y += velocity;
    if (direction == DOWN)
        m_Position.y -= velocity;
    if (direction == LEFT)
        m_Position.x -= velocity;
    if (direction == RIGHT)
        m_Position.x += velocity;
    
    RecalculateViewProjectionMatrix();
}

void Camera::ProcessMouseScroll(float yoffset, float mouse_x, float mouse_y)
{
    glm::vec3 before = ScreenToWorld(mouse_x, mouse_y);
    
    m_Zoom -= yoffset * 0.1f; 
    m_Zoom = glm::clamp(m_Zoom, 0.1f, 2.0f);

    SetViewportSize(1280.0f, 720.0f); // todo: parametrize screen
    glm::vec3 after = ScreenToWorld(mouse_x, mouse_y);
    m_Position += (before - after);
    
    RecalculateViewProjectionMatrix();
}

glm::vec3 Camera::ScreenToWorld(float screenX, float screenY)
{
    glm::mat4 inverseVP = glm::inverse(m_ViewProjectionMatrix);
    glm::vec4 ndc = glm::vec4(
        (screenX / 1280.0f) * 2.0f - 1.0f,
        (screenY / 720.0f) * 2.0f - 1.0f,
        0.0f, 1.0f
    );
    glm::vec4 world = inverseVP * ndc;
    return glm::vec3(world);
}