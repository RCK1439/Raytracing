#pragma once

#include <chrono>

namespace RTIAW {

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

}
