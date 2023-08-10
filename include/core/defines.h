#pragma once

/** @file */

/**
 * @defgroup UINT uint_t Wrapper
 * Unsigned int types.
 * @{
 */
using u8 = char8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
/** @} */

/**
 * @defgroup INT int_t Wrapper
 * Signed int types.
 * @{
 */
using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;
/** @} */

/**
 * @defgroup FLOATING_POINT Floating point Wrapper
 * Floating poit types.
 * @{
 */
using f32 = float;
using f64 = double;
/** @} */

/**
 * @brief Left shifts the bits of 1, decided by the number of places to shift.
 * @param x Number of places to shift.
*/
#define BIT(x) (1 << x)

namespace nk {
    /**
     * @brief Unique pointer wrapper.
     * @details
     * Usage: Use insted of the standard library unique pointer.
     * @tparam T Class or type.
     */
    template <typename T>
    using Scope = std::unique_ptr<T>;

    /**
     * @brief Shared pointer wrapper.
     * @details
     * Usage: Use instead of the standard library shared pointer.
     * @tparam T Class or type.
     */
    template <typename T>
    using Ref = std::shared_ptr<T>;

    /**
     * @brief Unique pointer creation wrapper.
     * @details
     * Usage: Use insted of the standard library make_unique method.
     * @tparam T Class or type.
     * @tparam Args Arguments for the construction of the class or type.
     */
    template <typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    /**
     * @brief Shared pointer creation wrapper.
     * @details
     * Usage: Use instead of the standard library make_shared method.
     * @tparam T Class or type.
     * @tparam Args Arguments for the construction of the class or type.
     */
    template <typename T, typename ...Args>
    constexpr Ref<T> CreateRef(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}
