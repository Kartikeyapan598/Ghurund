#pragma once

#include "GenericString.h"

namespace Ghurund::Core {
    template<typename T>
    class GenericStringView {
    protected:
        const T* v;
        size_t size;
        int hash;

        inline void computeHash() {
            hash = hashCode(v, size - 1);
        }

    public:
        GenericStringView(const GenericString<T>& str) {
            v = str.getData();
            size = str.Size;
            hash = str.Hash;
        }

        GenericStringView(const T* str) {
            v = str;
            size = lengthOf(str) + 1;
            computeHash();
        }

        GenericStringView(const T* str, size_t length) {
            v = str;
            size = length + 1;
            computeHash();
        }

        GenericStringView(const GenericStringView<T>& str) {
            v = str.v;
            size = str.size;
            hash = str.hash;
        }

        inline T* begin() {
            return v;
        }

        inline T* begin() const {
            return v;
        }

        inline T* end() {
            return v + size;
        }

        inline T* end() const {
            return v + size;
        }

        inline T get(size_t i)const {
            return v[i];
        }

        inline T& operator[](size_t i) {
            return v[i];
        }

        inline const T& operator[](size_t i) const {
            return v[i];
        }

        bool operator==(const GenericStringView<T>& string) const {
            return hash == string.hash && size == string.size && size != 0 && (v == string.v || memcmp(v, string.v, Length * sizeof(T)) == 0);
        }

        bool operator==(const GenericStringView<T>& string) {
            return hash == string.hash && size == string.size && size != 0 && (v == string.v || memcmp(v, string.v, Length * sizeof(T)) == 0);
        }

        bool operator==(const GenericString<T>& string) const {
            return hash == string.Hash && size == string.Size && size != 0 && (v == string.begin() || memcmp(v, string.begin(), Length * sizeof(T)) == 0);
        }

        bool operator==(const GenericString<T>& string) {
            return hash == string.Hash && size == string.Size && size != 0 && (v == string.begin() || memcmp(v, string.begin(), Length * sizeof(T)) == 0);
        }

        bool operator==(const T* str) const {
            return v == str || (lengthOf(str) == Length && memcmp(v, str, Length * sizeof(T)) == 0);
        }

        bool operator==(const T* str) {
            return v == str || (lengthOf(str) == Length && memcmp(v, str, Length * sizeof(T)) == 0);
        }

        GenericStringView& operator=(const GenericStringView& other) {
            if (this == &other)
                return *this;

            v = other.v;
            size = other.size;

            return *this;
        }

        GenericStringView& operator=(GenericStringView&& other) noexcept {
            if (this == &other)
                return *this;

            v = other.v;
            size = other.size;
            other.v = nullptr;
            other.size = 0;

            return *this;
        }

        size_t find(const T* str, size_t start = 0) const {
            size_t strSize = lengthOf(str);
            for (size_t i = start; i <= size - strSize; i++) {
                if (memcmp(&v[i], str, strSize * sizeof(T)) == 0)
                    return i;
            }
            return size;
        }

        size_t findLast(const T* str) const {
            size_t strSize = lengthOf(str);
            for (size_t i = size - strSize; i > 0; i--) {
                if (memcmp(&v[i], str, strSize * sizeof(T)) == 0)
                    return i;
            }

            if (memcmp(v, str, strSize * sizeof(T)) == 0)
                return 0;
            return size;
        }

        bool startsWith(const T* str) const {
            size_t i = 0;
            while (true) {
                if (str[i] == (T)'\0')
                    return true;
                if (str[i] != v[i])
                    return false;
                i++;
            }
        }

        bool endsWith(const T* str) const {
            size_t l = lengthOf(str);
            if (l > Length)
                return false;
            size_t i = 0;
            while (true) {
                if (str[i] == (T)'\0')
                    return true;
                if (str[i] != v[Length - l + i])
                    return false;
                i++;
            }
        }

        inline const T* getData() const {
            return v;
        }

        inline void setData(const T* data) {
            v = data;
            size = lengthOf(data) + 1;
            computeHash();
        }

        __declspec(property(get = getData, put = setData)) const T* Data;

        inline size_t getLength()const {
            return size - 1;
        }

        __declspec(property(get = getLength)) size_t Length;

        inline const size_t getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) const size_t Size;

        inline bool isEmpty() const {
            return size == 1;
        }

        __declspec(property(get = isEmpty)) bool Empty;

        inline int getHash() const {
            return hash;
        }

        __declspec(property(get = getHash)) int Hash;

        inline GenericStringView<T> substring(size_t start) const {
            return GenericStringView<T>(v + start);
        }

        inline GenericStringView<T> substring(size_t start, size_t length) const {
            return GenericStringView<T>(v + start, length);
        }

        inline GenericStringView<T> trim() const {
            size_t i, j, l = Length;
            for (i = 0; i < l && isSpace<T>(v[i]); i++);
            for (j = l; j > i && isSpace<T>(v[j]); j--);
            return GenericStringView<T>(v + i, j - i);
        }

    };
}