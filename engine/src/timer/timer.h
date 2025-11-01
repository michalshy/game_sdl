#pragma once

#include <chrono>

class Timer
{
    bool m_Running;
    float m_DeltaTime;
    std::chrono::time_point<std::chrono::system_clock> m_LastTime;
public:
    Timer() = default;
    bool Init();
    void Start();
    float Delta();
    float GetDelta();
};