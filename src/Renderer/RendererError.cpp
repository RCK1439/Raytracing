#include "RendererError.hpp"

namespace RTIAW {

std::ostream& operator<<(std::ostream& stream, const RendererError& err)
{
    switch (err.Type)
    {
        case RendererErrorType::FAILED_TO_SAVE_IMAGE:
            stream << "Failed to save image: " << err.OutputPath.string();
            break;
    }

    return stream;
}

}