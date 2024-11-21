#include "Timer.hpp"

#include <cstdint>
#include <print>

static constexpr float SEC_TO_HRS = 0.00027777777f;
static constexpr float HRS_TO_MIN = 60.0f;
static constexpr float MIN_TO_SEC = 60.0f;
static constexpr float SEC_TO_MS = 1000.0f;

void Timer::Start()
{
    m_Start = std::chrono::high_resolution_clock::now();
}

void Timer::Stop()
{
    m_End = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<float> duration = m_End - m_Start;
        
    float remainder;

    const float pHours = duration.count() * SEC_TO_HRS;
    const uint32_t rHours = static_cast<uint32_t>(pHours);
    remainder = pHours - static_cast<float>(rHours);

    const float pMinutes = remainder * HRS_TO_MIN;
    const uint32_t rMinutes = static_cast<uint32_t>(pMinutes);
    remainder = pMinutes - static_cast<float>(rMinutes);

    const float pSeconds = remainder * MIN_TO_SEC;
    const uint32_t rSeconds = static_cast<uint32_t>(pSeconds);
    remainder = pSeconds - static_cast<float>(rSeconds);

    const uint32_t ms = static_cast<uint32_t>(remainder * SEC_TO_MS);

    std::println("Time elapsed: {:02}h{:02}m{:02}s{:03}ms", rHours, rMinutes, rSeconds, ms);
}
