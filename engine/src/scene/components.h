#pragma once

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
};

enum class ColliderType
{
    CIRCLE,
    BOX,
};

struct CoCollider
{
    ColliderType type;
    int size;
};

