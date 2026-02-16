#pragma once

#include <cassert>

namespace RTIAW {

template<typename T>
class Buffer
{
public:
    constexpr Buffer() = default;
    constexpr explicit Buffer(size_t size) :
        m_Buffer(new T[size]), m_Size(size) {}
    Buffer(const Buffer<T>&) = delete;
    Buffer(Buffer<T>&&) = delete;

    inline constexpr ~Buffer()
    {
        delete[] m_Buffer;
    }

    inline constexpr void Resize(size_t newSize)
    {
        delete[] m_Buffer;
        m_Buffer = new T[newSize];
    }

    inline constexpr T& operator[](size_t idx)
    {
        assert(idx < m_Size);
        return m_Buffer[idx];
    }

    inline constexpr const T& operator[](size_t idx) const
    {
        assert(idx < m_Size);
        return m_Buffer[idx];
    }

    inline constexpr const T* GetRaw() const { return m_Buffer; }
    inline constexpr size_t GetSize() const { return m_Size; }

private:
    T*     m_Buffer{};
    size_t m_Size{};
};

}