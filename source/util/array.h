#pragma once

#include <assert.h>

#include <initializer_list>
#include <iostream>
#include <memory>

namespace GAT {
    template <typename T>
    void fill(T *_Dst, T _Val, size_t _Size) {
        if (_Size < 4) {
            for (size_t i = 0; i < _Size; i++) *(_Dst + i) = _Val;
            return;
        }
        size_t quad = _Size / 4;
        for (size_t i = 0; i < quad; i++) *(_Dst + i) = _Val;
        memcpy(_Dst + quad, _Dst, quad * sizeof(T));
        quad *= 2;
        memcpy(_Dst + quad, _Dst, quad * sizeof(T));
        quad *= 2;
        memcpy(_Dst + quad, _Dst, (_Size - quad) * sizeof(T));
    }

    template <typename T>
    struct Array {
        size_t size;
        std::unique_ptr<T> data;

        Array() = default;
        Array(const Array<T> &arr) {
            this->size = arr.size;
            data = std::unique_ptr<T>(
                static_cast<T *>(malloc(this->size * sizeof(T))));
            memcpy(data.get(), arr.data.get(), this->size * sizeof(T));
        }
        Array(std::initializer_list<T> values) {
            this->size = values.size();
            data = std::unique_ptr<T>(
                static_cast<T *>(malloc(this->size * sizeof(T))));
            memcpy(data.get(), values.begin(), this->size * sizeof(T));
        }
        Array(T *values, size_t size) {
            this->size = size;
            data = std::unique_ptr<T>(
                static_cast<T *>(malloc(this->size * sizeof(T))));
            memcpy(data.get(), values, this->size * sizeof(T));
        }
        Array(T value, size_t size) {
            this->size = size;
            data = std::unique_ptr<T>(
                static_cast<T *>(malloc(this->size * sizeof(T))));
            fill(data.get(), value, size);
        }
        ~Array() {
            free(data.get());
            data.release();
        }

        T &operator[](size_t index) {
            assert(index < size);
            return *(data.get() + index);
        }
        Array<T> slice(size_t index, size_t length) const {
            assert((index + length) <= size);
            return Array<T>(data.get() + index, length);
        }
        friend std::ostream &operator<<(std::ostream &os, Array<T> arr) {
            // Print values neatly
            os << "[" << std::to_string(arr[0]);
            for (size_t i = 1; i < arr.size; i++)
                os << ", " << std::to_string(arr[i]);
            os << "]";
            return os;
        }
    };
}  // namespace GAT