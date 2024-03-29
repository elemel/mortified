#ifndef ELEMEL_STRING_PTR_HPP
#define ELEMEL_STRING_PTR_HPP

#include <elemel/raw_allocator.hpp>
#include <elemel/ref_ptr.hpp>
#include <elemel/detail/string_impl.hpp>

#include <algorithm>
#include <cassert>
#include <string>

namespace elemel {
    template <
        class Char,
        class Traits = std::char_traits<Char>,
        class RefCount = int,
        class RawAllocator = raw_new_allocator
    >
    class basic_string_ptr {
    public:
        typedef Char value_type;
        typedef Traits traits_type;
        typedef RefCount ref_count_type;
        typedef RawAllocator raw_allocator_type;
        typedef detail::string_impl<value_type, ref_count_type, raw_allocator_type>
            impl_type;
        typedef std::size_t size_type;
        typedef value_type const *const_pointer;
        typedef value_type const *const_iterator;

        explicit basic_string_ptr(raw_allocator_type const &alloc =
                                  raw_allocator_type()) :
            impl_(impl_type::create(0, 0, alloc))
        { }

        basic_string_ptr(const_pointer str,
                         raw_allocator_type const &alloc =
                         raw_allocator_type()) :
            impl_(impl_type::create(str, Traits::length(str), alloc))
        { }

        basic_string_ptr(const_pointer str, size_type n,
                         raw_allocator_type const &alloc =
                         raw_allocator_type()) :
            impl_(impl_type::create(str, n, alloc))
        { }

        basic_string_ptr(const_pointer first, const_pointer last,
                         raw_allocator_type const &alloc =
                         raw_allocator_type()) :
            impl_(impl_type::create(first, last - first, alloc))
        { }

        const_pointer data() const
        {
            return impl_->data();
        }

        size_type size() const
        {
            return impl_->size();
        }

        const_pointer c_str() const
        {
            return impl_->data();
        }

        const_iterator begin() const
        {
            return impl_->data();
        }

        const_iterator end() const
        {
            return impl_->data() + impl_->size();
        }

    private:
        ref_ptr<impl_type> impl_;
    };

    template <class C, class T, class N, class A>
    bool operator==(basic_string_ptr<C, T, N, A> const &left,
                    basic_string_ptr<C, T, N, A> const &right)
    {
        return (left.size() == right.size() &&
                std::equal(left.begin(), left.end(), right.begin(), T::eq));
    }

    template <class C, class T, class N, class A>
    bool operator!=(basic_string_ptr<C, T, N, A> const &left,
                    basic_string_ptr<C, T, N, A> const &right)
    {
        return !(left == right);
    }

    template <class C, class T, class N, class A>
    bool operator<(basic_string_ptr<C, T, N, A> const &left,
                   basic_string_ptr<C, T, N, A> const &right)
    {
        return std::lexicographical_compare(left.begin(), left.end(),
                                            right.begin(), right.end(), T::lt);
    }

    template <class C, class T, class N, class A>
    bool operator<=(basic_string_ptr<C, T, N, A> const &left,
                    basic_string_ptr<C, T, N, A> const &right)
    {
        return !(right < left);
    }

    template <class C, class T, class N, class A>
    bool operator>=(basic_string_ptr<C, T, N, A> const &left,
                    basic_string_ptr<C, T, N, A> const &right)
    {
        return !(left < right);
    }

    template <class C, class T, class N, class A>
    bool operator>(basic_string_ptr<C, T, N, A> const &left,
                   basic_string_ptr<C, T, N, A> const &right)
    {
        return right < left;
    }

    template <class C, class T, class N, class A>
    bool operator==(basic_string_ptr<C, T, N, A> const &left, C const *right)
    {
        assert(right);
        std::size_t n = T::length(right);
        return left.size() == n && std::equal(left.begin(), left.end(), right);
    }

    template <class C, class T, class N, class A>
    bool operator!=(basic_string_ptr<C, T, N, A> const &left, C const *right)
    {
        return !(left == right);
    }

    template <class C, class T, class N, class A>
    bool operator<(basic_string_ptr<C, T, N, A> const &left, C const *right)
    {
        assert(right);
        return std::lexicographical_compare(left.begin(), left.end(),
                                            right, right + T::length(right),
                                            T::lt);
    }

    template <class C, class T, class N, class A>
    bool operator<=(basic_string_ptr<C, T, N, A> const &left, C const *right)
    {
        return !(right < left);
    }

    template <class C, class T, class N, class A>
    bool operator>=(basic_string_ptr<C, T, N, A> const &left, C const *right)
    {
        return !(left < right);
    }

    template <class C, class T, class N, class A>
    bool operator>(basic_string_ptr<C, T, N, A> const &left, C const *right)
    {
        return right < left;
    }

    template <class C, class T, class N, class A>
    bool operator==(C const *left, basic_string_ptr<C, T, N, A> const &right)
    {
        assert(left);
        std::size_t n = T::length(left);
        return n == right.size() && std::equal(left, left + n, right.begin());
    }

    template <class C, class T, class N, class A>
    bool operator!=(C const *left, basic_string_ptr<C, T, N, A> const &right)
    {
        return !(left == right);
    }

    template <class C, class T, class N, class A>
    bool operator<(C const *left, basic_string_ptr<C, T, N, A> const &right)
    {
        assert(left);
        return std::lexicographical_compare(left, left + T::length(left),
                                            right.begin(), right.end(),
                                            T::lt);
    }

    template <class C, class T, class N, class A>
    bool operator<=(C const *left, basic_string_ptr<C, T, N, A> const &right)
    {
        return !(right < left);
    }

    template <class C, class T, class N, class A>
    bool operator>=(C const *left, basic_string_ptr<C, T, N, A> const &right)
    {
        return !(left < right);
    }

    template <class C, class T, class N, class A>
    bool operator>(C const *left, basic_string_ptr<C, T, N, A> const &right)
    {
        return right < left;
    }

    typedef basic_string_ptr<char> string_ptr;
    typedef basic_string_ptr<wchar_t> wstring_ptr;
}

#endif // ELEMEL_STRING_PTR_HPP
