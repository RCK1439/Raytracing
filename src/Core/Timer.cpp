#include "Timer.hpp"

#include "Core/Types.hpp"

#include <print>

namespace RTIAW {

void Timer::Start() noexcept
{
    m_Start = Clock::now();
}

void Timer::Stop() noexcept
{
    m_End = Clock::now();

    const Duration duration = m_End - m_Start;
    const f32 elapsed = duration.count();

    std::println("Time elapsed: {:.3f}s", elapsed);
}

}
