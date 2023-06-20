/**
 * Ruan C. Keet (2023)
 * ArgumentParser.cpp
*/

#include "ArgumentParser.hpp"

#include <regex>

/**
 * Checks if the input string consists of numeric characters.
 * 
 * \param val   The string to check for.
 * 
 * \return true, if the input string consists of numeric characters.
*/
static bool IsNumeric(const std::string& val)
{
    return std::regex_match(val, std::regex("-?[0-9]+"));
}

/**
 * Checks if the given string is an acceptable flag.
 * 
 * \param arg   The argument to check for.
 * \param expr  The regular expression defining a valid argument.
 * 
 * \return true, if the argument matches the regex.
*/
static bool IsFlag(const std::string& arg, const std::string& expr)
{
    return std::regex_match(arg, std::regex(expr));
}

Arguments ArgumentParser::Parse(const std::vector<std::string>& args)
{
    const size_t size = args.size();

    Arguments settings;
    if (size == 0)
        return settings;

    for (size_t i = 0; i < size; i++)
    {
        const std::string& arg = args[i];

        if      (IsFlag(arg, "-[sS]")) i += ParseSize(settings, i, args) ? 2 : 0;
        else if (IsFlag(arg, "-[aA]")) i += (u32)ParseSamples(settings, i, args);
        else if (IsFlag(arg, "-[dD]")) i += (u32)ParseDepth(settings, i, args);
        else if (arg == "-o")          i += (u32)ParseOutput(settings, i, args);
        else if (arg == "-help")
        {
            settings.ShowHelp = true;
            return settings;
        }
    }

    return settings;
}

bool ArgumentParser::ParseSize(Arguments& settings, size_t i, const std::vector<std::string>& args)
{
    if (i + 2 >= args.size())
        return false;

    if (IsNumeric(args[i + 1]) && IsNumeric(args[i + 2]))
    {
        settings.Width  = (u32)std::stoul(args[i + 1]);
        settings.Height = (u32)std::stoul(args[i + 2]);

        return true;
    }

    return false;
}

bool ArgumentParser::ParseSamples(Arguments& settings, size_t i, const std::vector<std::string>& args)
{
    if (i + 1 >= args.size())
        return false;

    if (IsNumeric(args[i + 1]))
    {
        settings.NumberOfSamples = (u32)std::stoul(args[i + 1]);
        return true;
    }

    return false;
}

bool ArgumentParser::ParseDepth(Arguments& settings, size_t i, const std::vector<std::string>& args)
{
    if (i + 1 >= args.size())
        return false;

    if (IsNumeric(args[i + 1]))
    {
        settings.Depth = (u32)std::stoul(args[i + 1]);
        return true;
    }

    return false;
}

bool ArgumentParser::ParseOutput(Arguments& settings, size_t i, const std::vector<std::string>& args)
{
    if (i + 1 >= args.size())
        return false;

    settings.OutputPath = args[i + 1];
    return true;
}