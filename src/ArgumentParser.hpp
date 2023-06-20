/**
 * Ruan C. Keet (2023)
 * ArgumentParser.hpp
*/

#pragma once

#include "Types.hpp"

#include <string>
#include <vector>

struct Arguments
{
    u32         Width           = 1024;
    u32         Height          = 512;
    u32         NumberOfSamples = 32;
    u32         Depth           = 50;
    bool        ShowHelp        = false;
    std::string OutputPath      = "out/raytracing.png";
};

/**
 * Class used for parsing command-line arguments.
*/
class ArgumentParser
{
public: 
    /**
     * Parses the command-line arguments into usable data for the program
     * as parameters to run with.
     * 
     * \param args  Arguments passed from the command-line.
    */
    static Arguments Parse(const std::vector<std::string>& args);

private:
    /**
     * Parses the size flag (-s/-S) arguments and saves the results
     * into the settings.
     * 
     * \param settings  The struct holding the running parameters for the program.
     * \param i         The current index into the argument vector.
     * \param args      The arguments passed from the command-line.
     * 
     * \return true, if anything was parsed.
    */
    static bool ParseSize(Arguments& settings, size_t i, const std::vector<std::string>& args);

    /**
     * Parses the anti-aliasing samples flag (-a/-A) arguments and saves the results
     * into the settings.
     * 
     * \param settings  The struct holding the running parameters for the program.
     * \param i         The current index into the argument vector.
     * \param args      The arguments passed from the command-line.
     * 
     * \return true, if anything was parsed.
    */
    static bool ParseSamples(Arguments& settings, size_t i, const std::vector<std::string>& args);

    /**
     * Parses the ray bounce depth flag (-d/-D) arguments and saves the results
     * into the settings.
     * 
     * \param settings  The struct holding the running parameters for the program.
     * \param i         The current index into the argument vector.
     * \param args      The arguments passed from the command-line.
     * 
     * \return true, if anything was parsed.
    */
    static bool ParseDepth(Arguments& settings, size_t i, const std::vector<std::string>& args);

    /**
     * Parses the output path flag (-o) arguments and saves the results
     * into the settings.
     * 
     * \param settings  The struct holding the running parameters for the program.
     * \param i         The current index into the argument vector.
     * \param args      The arguments passed from the command-line.
     * 
     * \return true, if anything was parsed.
    */
    static bool ParseOutput(Arguments& settings, size_t i, const std::vector<std::string>& args);
};