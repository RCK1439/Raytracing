#pragma once

#include <cassert>

namespace RTIAW {

template<typename T>
class Buffer final
{
public:
    constexpr Buffer() noexcept = default;
    constexpr explicit Buffer(size_t size) noexcept :
        m_Buffer(new T[size]), m_Size(size) {}
    Buffer(const Buffer<T>&) = delete;
    Buffer(Buffer<T>&&) = delete;

    inline constexpr ~Buffer() noexcept
    {
        delete[] m_Buffer;
    }

    inline constexpr void Resize(size_t newSize) noexcept
    {
        delete[] m_Buffer;
        m_Buffer = new T[newSize];
    }

    inline constexpr T& operator[](size_t idx) noexcept
    {
        assert(idx < m_Size);
        return m_Buffer[idx];
    }

    inline constexpr const T& operator[](size_t idx) const noexcept
    {
        assert(idx < m_Size);
        return m_Buffer[idx];
    }

    inline constexpr const T* GetRaw() const noexcept { return m_Buffer; }
    inline constexpr size_t GetSize() const noexcept { return m_Size; }

private:
    T*     m_Buffer{};
    size_t m_Size{};
};

}