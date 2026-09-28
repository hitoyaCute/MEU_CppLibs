#pragma once
/* USAGE:
 * num_array<int> nums = {};
 * nums.swap(1,30);
 * int n = nums[41];
 * */

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <unordered_map>


/////////////////////////////////////////////////////////////////////////////
/// struct template thar contains an array of numbers or any numeric raw type
/// this type simulate an infinite number array that you can use and swap the
/// item around (use smaller type to save memory) this type grows when you
/// index a large index starts at 0 to what ever the max of the type youre using
/////////////////////////////////////////////////////////////////////////////
template <typename T = std::size_t>
  requires std::integral<T> || std::floating_point<T>
struct num_array {
    std::unordered_map<std::size_t, T> m_swaps{};
    std::size_t m_size{};

  public:
    [[nodiscard]] constexpr T operator[] (const std::size_t idx) noexcept
    {
        if (m_swaps.contains(idx))
        {
            return m_swaps.at(idx);
        }
        m_size = std::max(m_size, idx);
        return static_cast<T>(idx);
    }

    constexpr void reserve([[maybe_unused]] const std::size_t size) noexcept
    {
        m_size = size;
    }

    constexpr num_array& swap(const std::size_t idx_a, const std::size_t idx_b)
    {
        T tmp = (*this)[idx_a];
        m_swaps[idx_a] = (*this)[idx_b];
        m_swaps[idx_b] = tmp;
        return *this;
    }

    constexpr num_array& reset() noexcept {
        m_swaps.clear();
        m_size = 0;
        return *this;
    }

    [[nodiscard]] constexpr std::size_t size() const noexcept
    {
        return m_size;
    }
};

