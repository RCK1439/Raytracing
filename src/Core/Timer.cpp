#include "Timer.hpp"

#include "Core/Types.hpp"

#include <print>

namespace RTIAW::Time {

void Timer::Start()
{
    m_Start = Clock::now();
}

void Timer::Stop()
{
    m_End = Clock::now();

    const Duration duration = m_End - m_Start;
    const f32 elapsed = duration.count();

    std::println("Time elapsed: {:.3f}s", elapsed);
}

u32 SinceEpoch()
{
    return static_cast<u32>(std::chrono::system_clock::now()
        .time_since_epoch()
        .count());
}

}
