#pragma once

#include <glm/glm.hpp>

struct CoTransform
{
    glm::mat4 transform{1.0};
};

struct CoSprite
{
    glm::vec4 color{1.0f, 1.0f, 1.0f, 1.0f};
};

