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
struct num_array
{
  public:
    // Iterator
    class iterator {
      public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = T; // Returned by value since elements are generated on the fly

        constexpr iterator(num_array* arr, std::size_t idx) noexcept : m_arr(arr), m_idx(idx) {}

        constexpr T operator*() const {
            return (*m_arr)[m_idx];
        }

        constexpr iterator& operator++() noexcept {
            ++m_idx;
            return *this;
        }

        constexpr iterator operator++(int) noexcept {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        constexpr iterator& operator--() noexcept {
            --m_idx;
            return *this;
        }

        constexpr iterator operator--(int) noexcept {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        constexpr iterator& operator+=(difference_type n) noexcept {
            m_idx += n;
            return *this;
        }

        constexpr iterator& operator-=(difference_type n) noexcept {
            m_idx -= n;
            return *this;
        }

        friend constexpr iterator operator+(iterator it, difference_type n) noexcept {
            return iterator(it.m_arr, it.m_idx + n);
        }

        friend constexpr iterator operator+(difference_type n, iterator it) noexcept {
            return iterator(it.m_arr, it.m_idx + n);
        }

        friend constexpr iterator operator-(iterator it, difference_type n) noexcept {
            return iterator(it.m_arr, it.m_idx - n);
        }

        friend constexpr difference_type operator-(iterator a, iterator b) noexcept {
            return static_cast<difference_type>(a.m_idx) - static_cast<difference_type>(b.m_idx);
        }

        constexpr T operator[](difference_type n) const {
            return *(*this + n);
        }

        friend constexpr bool operator==(const iterator& a, const iterator& b) noexcept {
            return a.m_arr == b.m_arr && a.m_idx == b.m_idx;
        }

        friend constexpr bool operator!=(const iterator& a, const iterator& b) noexcept {
            return !(a == b);
        }

        friend constexpr bool operator<(const iterator& a, const iterator& b) noexcept {
            return a.m_idx < b.m_idx;
        }

        friend constexpr bool operator<=(const iterator& a, const iterator& b) noexcept {
            return a.m_idx <= b.m_idx;
        }

        friend constexpr bool operator>(const iterator& a, const iterator& b) noexcept {
            return a.m_idx > b.m_idx;
        }

        friend constexpr bool operator>=(const iterator& a, const iterator& b) noexcept {
            return a.m_idx >= b.m_idx;
        }

      private:
        num_array* m_arr;
        std::size_t m_idx;
    };
  private:
    std::unordered_map<std::size_t, T> m_swaps{};
    std::size_t m_size{};

  public:
    [[nodiscard]] constexpr T operator[] (const std::size_t idx) noexcept
    {
        if (m_swaps.contains(idx))
        {
            return m_swaps.at(idx);
        }
        m_size = std::max(m_size, idx + 1);
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

    [[nodiscard]] constexpr iterator begin() noexcept {
        return iterator(this, 0);
    }

    [[nodiscard]] constexpr iterator end() noexcept {
        return iterator(this, m_size);
    }
};

