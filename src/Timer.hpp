#pragma once

#include <chrono>

class Timer
{
public:
    Timer() = default;
    ~Timer() = default;
    
    void Start();
    void Stop();
    
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_End;
};