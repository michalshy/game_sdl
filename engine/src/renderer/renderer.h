#pragma once

#include <SDL_render.h>
#include <SDL_video.h>
#include "glm/glm.hpp"

class Renderer
{
public:
    static void DrawQuad(const glm::mat4 transform, const glm::vec4 color);
};