/**
 * Ruan C. Keet (2023)
 * Timer.hpp
*/

#pragma once

#include <chrono>

/**
 * A simple timer with start/stop functions.
*/
class Timer
{
public:
    /**
     * Constructs a new timer.
    */
    Timer() = default;

    /**
     * Destroys the timer.
    */
    ~Timer() = default;
    
    /**
     * Starts the timer.
    */
    void Start();

    /**
     * Stops the timer and prints the elapsed time to the terminal.
    */
    void Stop();
    
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_End;
};
