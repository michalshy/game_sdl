#pragma once

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

struct CoTransform
{
    glm::mat4 transform{1.0};

    void Translate(const glm::vec3& offset)
    {
        transform = glm::translate(transform, offset);
    }
};

struct CoSprite
{
    glm::vec4 color{1.0f, 1.0f, 1.0f, 1.0f};

    void UpdateColor(const glm::vec4& vec)
    {
        color = vec;
    }
};

enum class ColliderType
{
    CIRCLE,
    BOX,
};

struct CoCollider
{
    bool on;
    ColliderType type;
    int size;
};
