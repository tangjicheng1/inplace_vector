#pragma once

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <memory>

template<typename T, std::size_t N>
class inplace_vector
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using allocator_type = std::allocator<T>;

    class const_iterator;

    class iterator
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(pointer ptr) :
            ptr_(ptr) {}

        reference operator*() const { return *ptr_; }
        pointer operator->() { return ptr_; }
        iterator& operator++()
        {
            ++ptr_;
            return *this;
        }
        iterator operator++(int)
        {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        iterator& operator--()
        {
            --ptr_;
            return *this;
        }
        iterator operator--(int)
        {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }
        iterator operator+(difference_type offset) const
        {
            return iterator(ptr_ + offset);
        }
        iterator operator-(difference_type offset) const
        {
            return iterator(ptr_ - offset);
        }
        difference_type operator-(const iterator& other) const
        {
            return ptr_ - other.ptr_;
        }
        bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }
        bool operator<(const iterator& other) const { return ptr_ < other.ptr_; }
        bool operator>(const iterator& other) const { return ptr_ > other.ptr_; }
        bool operator<=(const iterator& other) const { return ptr_ <= other.ptr_; }
        bool operator>=(const iterator& other) const { return ptr_ >= other.ptr_; }

        inline operator const_iterator() const { return const_iterator(ptr_); }

    private:
        pointer ptr_;
    };

    class const_iterator
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator(pointer ptr) :
            ptr_(ptr) {}

        reference operator*() const { return *ptr_; }
        pointer operator->() const { return ptr_; }
        const_iterator& operator++()
        {
            ++ptr_;
            return *this;
        }
        const_iterator operator++(int)
        {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        const_iterator& operator--()
        {
            --ptr_;
            return *this;
        }
        const_iterator operator--(int)
        {
            const_iterator tmp = *this;
            --(*this);
            return tmp;
        }
        const_iterator operator+(difference_type offset) const
        {
            return const_iterator(ptr_ + offset);
        }
        const_iterator operator-(difference_type offset) const
        {
            return const_iterator(ptr_ - offset);
        }
        difference_type operator-(const const_iterator& other) const
        {
            return ptr_ - other.ptr_;
        }
        bool operator==(const const_iterator& other) const
        {
            return ptr_ == other.ptr_;
        }
        bool operator!=(const const_iterator& other) const
        {
            return ptr_ != other.ptr_;
        }
        bool operator<(const const_iterator& other) const
        {
            return ptr_ < other.ptr_;
        }
        bool operator>(const const_iterator& other) const
        {
            return ptr_ > other.ptr_;
        }
        bool operator<=(const const_iterator& other) const
        {
            return ptr_ <= other.ptr_;
        }
        bool operator>=(const const_iterator& other) const
        {
            return ptr_ >= other.ptr_;
        }

    private:
        pointer ptr_;
    };

    constexpr inplace_vector() noexcept :
        size_(0) {}

    constexpr inplace_vector(const inplace_vector& other)
    {
        size_ = 0;
        for (const auto& elem : other)
        {
            push_back(elem);
        }
    }

    constexpr inplace_vector(inplace_vector&& other) noexcept
        :
        size_(other.size_)
    {
        for (size_type i = 0; i < size_; ++i)
        {
            new (&data_[i]) T(std::move(*reinterpret_cast<T*>(&other.data_[i])));
        }
        other.size_ = 0;
    }

    ~inplace_vector() { clear(); }

    inplace_vector& operator=(const inplace_vector& other)
    {
        if (this != &other)
        {
            clear();
            for (const auto& elem : other)
            {
                push_back(elem);
            }
        }
        return *this;
    }

    inplace_vector& operator=(inplace_vector&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            size_ = other.size_;
            for (size_type i = 0; i < size_; ++i)
            {
                new (&data_[i]) T(std::move(*reinterpret_cast<T*>(&other.data_[i])));
            }
            other.size_ = 0;
        }
        return *this;
    }

    void assign(size_type count, const T& value)
    {
        clear();
        for (size_type i = 0; i < count; ++i)
        {
            push_back(value);
        }
    }

    template<class InputIt>
    void assign(InputIt first, InputIt last)
    {
        clear();
        for (auto it = first; it != last; ++it)
        {
            push_back(*it);
        }
    }

    reference operator[](size_type n)
    {
        return reinterpret_cast<reference>(data_[n]);
    }

    const_reference operator[](size_type n) const
    {
        return reinterpret_cast<const_reference>(data_[n]);
    }

    reference at(size_type n)
    {
        if (n >= size_)
        {
            throw std::out_of_range("inplace_vector out of range");
        }
        return (*this)[n];
    }

    const_reference at(size_type n) const
    {
        if (n >= size_)
        {
            throw std::out_of_range("inplace_vector out of range");
        }
        return (*this)[n];
    }

    reference front() { return (*this)[0]; }

    const_reference front() const { return (*this)[0]; }

    reference back() { return (*this)[size_ - 1]; }

    const_reference back() const { return (*this)[size_ - 1]; }

    T* data() noexcept { return reinterpret_cast<T*>(data_); }

    const T* data() const noexcept { return reinterpret_cast<const T*>(data_); }

    constexpr size_type size() const noexcept { return size_; }

    static constexpr size_type capacity() noexcept { return N; }

    constexpr bool empty() const noexcept { return size_ == 0; }

    static constexpr size_type max_size() noexcept { return N; }

    void reserve(size_type new_cap)
    {
        if (new_cap > N)
        {
            throw std::length_error("inplace_vector cannot exceed its fixed capacity");
        }
    }

    void shrink_to_fit() noexcept
    {
        // Do nothing since this is a fixed capacity container
    }

    void clear()
    {
        while (size_ > 0)
        {
            pop_back();
        }
    }

    T& push_back(const T& value)
    {
        if (size_ >= N)
        {
            throw std::overflow_error("inplace_vector overflow");
        }
        new (&data_[size_]) T(value);
        ++size_;
        return back();
    }

    T& push_back(T&& value)
    {
        if (size_ >= N)
        {
            throw std::overflow_error("inplace_vector overflow");
        }
        new (&data_[size_]) T(std::move(value));
        ++size_;
        return back();
    }

    T* try_push_back(const T& value)
    {
        if (size_ >= N)
        {
            return nullptr;
        }
        new (&data_[size_]) T(value);
        ++size_;
        return &back();
    }

    T* try_push_back(T&& value)
    {
        if (size_ >= N)
        {
            return nullptr;
        }
        new (&data_[size_]) T(std::move(value));
        ++size_;
        return &back();
    }

    template<class... Args>
    reference emplace_back(Args&&... args)
    {
        if (size_ >= N)
        {
            throw std::overflow_error("inplace_vector overflow");
        }
        new (&data_[size_]) T(std::forward<Args>(args)...);
        ++size_;
        return back();
    }

    template<class... Args>
    T* try_emplace_back(Args&&... args)
    {
        if (size_ >= N)
        {
            return nullptr;
        }
        new (&data_[size_]) T(std::forward<Args>(args)...);
        ++size_;
        return &back();
    }

    void pop_back()
    {
        if (size_ > 0)
        {
            --size_;
            reinterpret_cast<T*>(&data_[size_])->~T();
        }
    }

    void swap(inplace_vector& other) noexcept
    {
        std::swap_ranges(data_, data_ + std::min(size_, other.size_), other.data_);
        if (size_ > other.size_)
        {
            for (size_type i = other.size_; i < size_; ++i)
            {
                new (&other.data_[i]) T(std::move(*reinterpret_cast<T*>(&data_[i])));
                reinterpret_cast<T*>(&data_[i])->~T();
            }
        }
        else
        {
            for (size_type i = size_; i < other.size_; ++i)
            {
                new (&data_[i]) T(std::move(*reinterpret_cast<T*>(&other.data_[i])));
                reinterpret_cast<T*>(&other.data_[i])->~T();
            }
        }
        std::swap(size_, other.size_);
    }

    iterator begin() noexcept
    {
        return iterator(reinterpret_cast<T*>(&data_[0]));
    }

    const_iterator begin() const noexcept
    {
        return const_iterator(reinterpret_cast<const T*>(&data_[0]));
    }

    iterator end() noexcept
    {
        return iterator(reinterpret_cast<T*>(&data_[size_]));
    }

    const_iterator end() const noexcept
    {
        return const_iterator(reinterpret_cast<const T*>(&data_[size_]));
    }

    const_iterator cbegin() const noexcept
    {
        return const_iterator(reinterpret_cast<const T*>(&data_[0]));
    }

    const_iterator cend() const noexcept
    {
        return const_iterator(reinterpret_cast<const T*>(&data_[size_]));
    }

    iterator insert(const_iterator pos, const T& value)
    {
        size_type index = pos - cbegin();
        if (size_ >= N)
        {
            throw std::overflow_error("inplace_vector overflow");
        }
        for (size_type i = size_; i > index; --i)
        {
            new (&data_[i]) T(std::move(*reinterpret_cast<T*>(&data_[i - 1])));
            reinterpret_cast<T*>(&data_[i - 1])->~T();
        }
        new (&data_[index]) T(value);
        ++size_;
        return iterator(reinterpret_cast<T*>(&data_[index]));
    }

    iterator insert(const_iterator pos, T&& value)
    {
        size_type index = pos - cbegin();
        if (size_ >= N)
        {
            throw std::overflow_error("inplace_vector overflow");
        }
        for (size_type i = size_; i > index; --i)
        {
            new (&data_[i]) T(std::move(*reinterpret_cast<T*>(&data_[i - 1])));
            reinterpret_cast<T*>(&data_[i - 1])->~T();
        }
        new (&data_[index]) T(std::move(value));
        ++size_;
        return iterator(reinterpret_cast<T*>(&data_[index]));
    }

    template<class... Args>
    iterator emplace(const_iterator pos, Args&&... args)
    {
        size_type index = pos - cbegin();
        if (size_ >= N)
        {
            throw std::overflow_error("inplace_vector overflow");
        }
        for (size_type i = size_; i > index; --i)
        {
            new (&data_[i]) T(std::move(*reinterpret_cast<T*>(&data_[i - 1])));
            reinterpret_cast<T*>(&data_[i - 1])->~T();
        }
        new (&data_[index]) T(std::forward<Args>(args)...);
        ++size_;
        return iterator(reinterpret_cast<T*>(&data_[index]));
    }

    iterator erase(const_iterator pos)
    {
        size_type index = pos - cbegin();
        if (index < size_)
        {
            reinterpret_cast<T*>(&data_[index])->~T();
            for (size_type i = index; i < size_ - 1; ++i)
            {
                new (&data_[i]) T(std::move(*reinterpret_cast<T*>(&data_[i + 1])));
                reinterpret_cast<T*>(&data_[i + 1])->~T();
            }
            --size_;
        }
        return iterator(reinterpret_cast<T*>(&data_[index]));
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        size_type start_index = first - cbegin();
        size_type end_index = last - cbegin();
        size_type count = end_index - start_index;
        if (count > 0 && start_index < size_)
        {
            for (size_type i = start_index; i < end_index; ++i)
            {
                reinterpret_cast<T*>(&data_[i])->~T();
            }
            for (size_type i = start_index; i < size_ - count; ++i)
            {
                new (&data_[i]) T(std::move(*reinterpret_cast<T*>(&data_[i + count])));
                reinterpret_cast<T*>(&data_[i + count])->~T();
            }
            size_ -= count;
        }
        return iterator(reinterpret_cast<T*>(&data_[start_index]));
    }

    void resize(size_type new_size)
    {
        if (new_size > N)
        {
            throw std::overflow_error("inplace_vector overflow");
        }
        while (size_ > new_size)
        {
            pop_back();
        }
        while (size_ < new_size)
        {
            push_back(T());
        }
    }

    void resize(size_type new_size, const T& value)
    {
        if (new_size > N)
        {
            throw std::overflow_error("inplace_vector overflow");
        }
        while (size_ > new_size)
        {
            pop_back();
        }
        while (size_ < new_size)
        {
            push_back(value);
        }
    }

    allocator_type get_allocator() const noexcept
    {
        return allocator_type();
    }

private:
    std::aligned_storage_t<sizeof(T), alignof(T)> data_[N];
    size_type size_;
};
