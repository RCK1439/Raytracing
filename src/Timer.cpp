#include "Timer.hpp"

#include "Types.hpp"

#include <print>

static constexpr f32 SEC_TO_HRS = 0.00027777777f;
static constexpr f32 HRS_TO_MIN = 60.0f;
static constexpr f32 MIN_TO_SEC = 60.0f;
static constexpr f32 SEC_TO_MS = 1000.0f;

void Timer::Start()
{
    m_Start = std::chrono::high_resolution_clock::now();
}

void Timer::Stop()
{
    m_End = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<f32> duration = m_End - m_Start;
        
    f32 remainder;

    const f32 pHours = duration.count() * SEC_TO_HRS;
    const u32 rHours = (u32)pHours;
    remainder = pHours - static_cast<f32>(rHours);

    const f32 pMinutes = remainder * HRS_TO_MIN;
    const u32 rMinutes = static_cast<u32>(pMinutes);
    remainder = pMinutes - static_cast<f32>(rMinutes);

    const f32 pSeconds = remainder * MIN_TO_SEC;
    const u32 rSeconds = static_cast<u32>(pSeconds);
    remainder = pSeconds - static_cast<f32>(rSeconds);

    u32 ms = static_cast<u32>(remainder * SEC_TO_MS);

    std::println("Time elapsed: {:02}h{:02}m{:02}s{:03}ms", rHours, rMinutes, rSeconds, ms);
}
