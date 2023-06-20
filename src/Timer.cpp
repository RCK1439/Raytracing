/**
 * Ruan C. Keet (2023)
 * Timer.cpp
*/

#include "Timer.hpp"

#include "Types.hpp"

#include <stdio.h>

#define SEC_TO_HRS 0.00027777777f
#define HRS_TO_MIN 60.0f
#define MIN_TO_SEC 60.0f;
#define SEC_TO_MS  1000.0f

void Timer::Start()
{
    m_Start = std::chrono::high_resolution_clock::now();
}

void Timer::Stop()
{
    m_End = std::chrono::high_resolution_clock::now();

    std::chrono::duration<f32> duration = m_End - m_Start;
        
    f32 remainder;

    f32 pHours = duration.count() * SEC_TO_HRS;
    u32 rHours = (u32)pHours;
    remainder  = pHours - (f32)rHours;

    f32 pMinutes = remainder * HRS_TO_MIN;
    u32 rMinutes = (u32)pMinutes;
    remainder    = pMinutes - (f32)rMinutes;

    f32 pSeconds = remainder * MIN_TO_SEC;
    u32 rSeconds = (u32)pSeconds;
    remainder    = pSeconds - (f32)rSeconds;

    u32 ms = u32(remainder * SEC_TO_MS);

    printf("Time elapsed: %02dh%02dm%02ds%03dms\n", rHours, rMinutes, rSeconds, ms);
}
