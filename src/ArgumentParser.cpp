#include "ArgumentParser.hpp"

#include <regex>

static bool IsNumeric(const std::string& val)
{
    return std::regex_match(val, std::regex("-?[0-9]+"));
}

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

        if (IsFlag(arg, "-[sS]"))
        {
            i += ParseSize(settings, i, args) ? 2 : 0;
        }
        else if (IsFlag(arg, "-[aA]"))
        {
            i += static_cast<u32>(ParseSamples(settings, i, args));
        }
        else if (IsFlag(arg, "-[dD]"))
        {
            i += static_cast<u32>(ParseDepth(settings, i, args));
        }
        else if (arg == "-o")
        {
            i += static_cast<u32>(ParseOutput(settings, i, args));
        }
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
        settings.Width  = static_cast<u32>(std::stoul(args[i + 1]));
        settings.Height = static_cast<u32>(std::stoul(args[i + 2]));

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
        settings.NumberOfSamples = static_cast<u32>(std::stoul(args[i + 1]));
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
        settings.Depth = static_cast<u32>(std::stoul(args[i + 1]));
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
