#include "timer.h"
#include <chrono>

constexpr float MAX_DELTA = 1.0f;
constexpr float MIN_DELTA = 0.0f;

bool Timer::Init()
{
    // init static variables
    Timer::m_DeltaTime = 0.0f;
    Timer::m_LastTime = std::chrono::system_clock::now();
    Timer::m_Running = false;
    return true;
}

void Timer::Start()
{
    m_LastTime = std::chrono::system_clock::now();
}

float Timer::Delta()
{
    auto current_time = std::chrono::system_clock::now();
    float duration = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - m_LastTime).count();
    if(duration > MIN_DELTA)
    {
        if(duration > MAX_DELTA)
            m_DeltaTime = MAX_DELTA;
        else
            m_DeltaTime = duration;
    }
    return m_DeltaTime;
}

float Timer::GetDelta()
{
    return m_DeltaTime;
}