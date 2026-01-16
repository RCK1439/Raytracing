#pragma once

#include <cstdint>
#include <cstddef>
#include <expected>
#include <optional>

namespace rt {

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

static_assert(sizeof(float) == 4);
using f32 = float;
static_assert(sizeof(double) == 8);
using f64 = double;

template<typename T>
using Option = std::optional<T>;

template<typename T, typename E>
using Result = std::expected<T, E>;
template<typename E>
using Err = std::unexpected<E>;

}