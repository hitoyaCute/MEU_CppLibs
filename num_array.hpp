#pragma once
/* USAGE:
 * num_array<int> nums = {};
 * nums.swap(1,30);
 * int n = nums[41];
 * */

#include <cstddef>
#include <cstring>
#include <cstdlib>


/////////////////////////////////////////////////////////////////////////////
/// struct template thar contains an array of numbers or any numeric raw type
/// this type simulate an infinite number array that you can use and swap the
/// item around (use smaller type to save memory) this type grows when you
/// index a large index starts at 0 to what ever the max of the type youre using
/////////////////////////////////////////////////////////////////////////////
template <typename T = std::size_t>
struct num_array {
    T* nums = nullptr;
    T  len  = 0;

    T operator[](const T i) {
        // check if needs to expand
        if (i >= this->len) {
            T* temp = (T*)malloc(sizeof(T) * (i + 1));
            // copy the original array to the the new location
            if (this->nums) {
                memcpy(temp, this->nums, sizeof(T) * this->len);

                // deallocate the old memory
                free(this->nums);
            }
            // adds new
            for (T j = this->len; j <= i; j++)
                temp[j] = j;
            // use the new memory
            this->nums = temp;
            // update the length
            this->len = i + 1;
        }
        return this->nums[i];
    }

    void reserve(const T size){
        (*this)[size - 1];
    }

    num_array& swap(const T a, const T b) {
        T va = (*this)[a];
        T vb = (*this)[b];
        this->nums[a] = vb;
        this->nums[b] = va;
        return *this;
    }

    num_array& reset() {
        if (this->nums != 0) {
            free(this->nums);
            this->nums = 0;
            this->len = 0;
        }

        return *this;
    }

    num_array() = default;
    ~num_array() { reset(); }

    num_array(const num_array& other)
        : len(other.len) {
        if (other.nums) {
            nums = (T*)malloc(sizeof(T) * len);
            memcpy(nums, other.nums, sizeof(T) * len);
        }
    }

    num_array& operator=(const num_array& other) {
        if (this != &other) {
            T* temp = nullptr;
            if (other.nums) {
                temp = (T*)malloc(sizeof(T) * other.len);
                memcpy(temp, other.nums, sizeof(T) * other.len);
            }
            free(nums);
            nums = temp;
            len  = other.len;
        }
        return *this;
    }

    num_array(num_array&& other) noexcept
        : nums(other.nums), len(other.len) {
        other.nums = nullptr;
        other.len  = 0;
    }

    num_array& operator=(num_array&& other) noexcept {
        if (this != &other) {
            free(nums);
            nums = other.nums;
            len  = other.len;
            other.nums = nullptr;
            other.len  = 0;
        }
        return *this;
    } 
};

