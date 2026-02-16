#include "RendererError.hpp"

namespace rt {

std::ostream& operator<<(std::ostream& stream, const RendererError& err)
{
    switch (err.Type)
    {
        case RendererErrorType::FAILED_TO_SAVE_IMAGE:
            stream << "Failed to save image: " << err.ImagePath;
            break;
    }

    return stream;
}

}