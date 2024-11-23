#include "Error.hpp"

#include <sstream>

namespace rt
{
    std::string RendererError::What() const
    {
        std::stringstream stream;

        switch (m_Type)
        {
            case Type::FAILED_TO_SAVE_IMAGE:
                stream << "Failed to save image: " << m_Detail;
                break;
        }

        return stream.str();
    }
}
