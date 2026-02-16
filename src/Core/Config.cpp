#include "Config.hpp"

#include <vector>

namespace rt {

static constexpr Option<u32> ParseNumber(std::string_view arg);
static constexpr bool IsDigit(char ch);

Result<Config, ConfigParseError> ParseConfig(i32 argc, char* argv[])
{
    std::vector<std::string> args{};
    for (i32 i{1}; i < argc; i++)
        args.emplace_back(argv[i]);

    const size_t numArgs = args.size();

    Config cfg{};
    if (numArgs == 0)
        return cfg;

    size_t i{};
    while (i < numArgs)
    {
        if (args[i] == "-s" || args[i] == "-S")
        {
            if (i + 2 >= numArgs)
                return Err(ConfigParseError::INVALID_DIMENSIONS_FORMAT);

            if (const auto width = ParseNumber(args[i+1]))
                cfg.Width = width.value();
            else
                return Err(ConfigParseError::INVALID_WIDTH);

            if (const auto height = ParseNumber(args[i+2]))
                cfg.Height = height.value();
            else
                return Err(ConfigParseError::INVALID_HEIGHT);

            i += 3;
        }
        else if (args[i] == "-a" || args[i] == "-A")
        {
            if (i + 1 >= numArgs)
                return Err(ConfigParseError::INVALID_SAMPLES_FORMAT);

            if (const auto numSamples = ParseNumber(args[i+1]))
                cfg.NumberOfSamples = numSamples.value();
            else
                return Err(ConfigParseError::INVALID_NUM_SAMPLES);

            i += 2;
        }
        else if (args[i] == "-d" || args[i] == "-D")
        {
            if (i + 1 >= numArgs)
                return Err(ConfigParseError::INVALID_DEPTH_FORMAT);

            if (const auto depth = ParseNumber(args[i+1]))
                cfg.Depth = depth.value();
            else
                return Err(ConfigParseError::INVALID_DEPTH);

            i += 2;
        }
        else if (args[i] == "-o")
        {
            if (i + 1 >= numArgs)
                return Err(ConfigParseError::INVALID_OUTPUT_FORMAT);

            cfg.OutputPath = args[i + 1];

            i += 2;
        }
        else if (args[i] == "-help")
        {
            cfg.ShowHelp = true;
            return cfg;
        }
        else
        {
            i++;
        }
    }

    return cfg;
}

std::ostream& operator<<(std::ostream& stream, ConfigParseError err)
{
    switch (err)
    {
        case ConfigParseError::INVALID_DIMENSIONS_FORMAT:
            stream << "dimensions usage: -s (or -S) <width >= 0> <height >= 0>";
            break;
        case ConfigParseError::INVALID_SAMPLES_FORMAT:
            stream << "anti-aliasing samples usage: -a (or -A) <num_samples >= 0>";
            break;
        case ConfigParseError::INVALID_DEPTH_FORMAT:
            stream << "bounce depth usage: -d (or -D) <depth >= 0>";
            break;
        case ConfigParseError::INVALID_OUTPUT_FORMAT:
            stream << "output path usage: -o <filepath>";
            break;
        case ConfigParseError::INVALID_WIDTH:
            stream << "width must be a positive integer";
            break;
        case ConfigParseError::INVALID_HEIGHT:
            stream << "height must be a positive integer";
            break;
        case ConfigParseError::INVALID_NUM_SAMPLES:
            stream << "anti-aliasing samples must be a positive integer";
            break;
        case ConfigParseError::INVALID_DEPTH:
            stream << "bounce depth must be a positive integer";
            break;
    }

    return stream;
}

static constexpr Option<u32> ParseNumber(std::string_view str)
{
    if (str[0] == '-')
        return {};

    uint32_t num = 0;

    size_t i{};
    while (i < str.size())
    {
        if (!IsDigit(str[i]))
            return {};

        num = 10 * num + (str[i++] - '0');
    }

    return num;
}

static constexpr bool IsDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

}
