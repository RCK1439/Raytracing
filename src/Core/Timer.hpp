#pragma once

#include "Types.hpp"

#include <chrono>

namespace RTIAW::Time {

class Timer final
{
public:
    using Clock     = std::chrono::high_resolution_clock;
    using Duration  = std::chrono::duration<float>;
    using TimePoint = std::chrono::time_point<Clock, Duration>;

public:
    void Start() noexcept;
    void Stop() noexcept;
    
private:
    TimePoint m_Start{};
    TimePoint m_End{};
};

class ScopedTimer final
{
public:
    inline ScopedTimer() noexcept { m_Timer.Start(); }
    inline ~ScopedTimer() noexcept { m_Timer.Stop(); }
    
private:
    Timer m_Timer{};
};

u32 SinceEpoch() noexcept;

}
