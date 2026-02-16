set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Config.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Random.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Timer.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/RendererError.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Image.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Renderer.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Scene/Camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene/Scene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene/Sphere.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Scene/Materials/Dielectric.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene/Materials/Lambertian.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene/Materials/Metal.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/EntryPoint.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Buffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Types.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Config.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Random.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Timer.hpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/RendererError.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Image.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Ray.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Renderer.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Scene/Camera.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene/Scene.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene/Sphere.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Scene/Materials/Dielectric.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene/Materials/HitRecord.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene/Materials/Lambertian.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene/Materials/Material.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene/Materials/Metal.hpp
)

add_executable(rtk ${SOURCES} ${HEADERS})

if(WIN32)
    if(MSVC)
        target_compile_options(rtk PRIVATE /W4 /WX)
        target_compile_definitions(rtk PRIVATE _CRT_SECURE_NO_WARNINGS)
    else()
        target_compile_options(rtk PRIVATE -Wall -Wextra -Wpedantic -Werror -fno-exceptions)
    endif()
else()
    target_compile_options(rtk PRIVATE -Wall -Wextra -Wpedantic -Werror -fno-exceptions)
endif()

target_include_directories(rtk PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(rtk PROPERTIES
    OUTPUT_NAME "rtk"
    VERSION ${rtk_VERSION_MAJOR}.${rtk_VERSION_MINOR}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)