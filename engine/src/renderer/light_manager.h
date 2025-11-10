#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "scene/scene.h"

struct Light
{
    glm::vec2 Position;
    glm::vec3 Color;
    float Radius;
    float Intensity;
};

class LightManager
{
public:
    static bool Init();
    static void Shutdown();

    static void BeginFrame(Scene* scene);
    static void EndFrame();

    static void AddLight(const glm::vec2& position, const glm::vec3& color, float radius, float intensity = 1.0f);
    static void ClearLights();

    // Accessor for Renderer
    static const std::vector<Light>& GetLights();

private:
    struct LightererData
    {
        std::vector<Light> Lights;
    };
    static std::unique_ptr<LightererData> s_Data;
};
