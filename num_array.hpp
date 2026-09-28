#pragma once
/* USAGE:
 * num_array<int> nums = {};
 * nums.swap(1,30);
 * int n = nums[41];
 * */

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
  requires std::integral<T>
struct num_array {
    std::unordered_map<std::size_t, T> swaps;

  public:
    [[nodsicard]] constexpr T operator[] (const std::size_t idx) const noexcept
    {
        if (swaps.contains(idx))
        {
            return swaps.at(idx);
        }
        return T{idx};
    }

    [[deprecated("This does nothing. You should remove this function call. This function may be removed in the future.")]]
    constexpr void reserve(const std::size_t) noexcept
    {
        // NOOP
    }

    constexpr num_array& swap(const std::size_t a, const std::size_t b)
    {
        T tmp = (*this)[a];
        swaps[a] = (*this)[b];
        swaps[b] = tmp;
        return *this;
    }

    constexpr num_array& reset() noexcept {
        swaps.clear();
        return *this;
    }
};

