/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Morwenn
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef CPPSORT_DETAIL_CONTAINER_AWARE_SELECTION_SORT_H_
#define CPPSORT_DETAIL_CONTAINER_AWARE_SELECTION_SORT_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <forward_list>
#include <functional>
#include <iterator>
#include <list>
#include <type_traits>
#include <cpp-sort/fwd.h>
#include <cpp-sort/sorter_traits.h>
#include <cpp-sort/utility/functional.h>
#include "../min_element.h"

namespace cppsort
{
    namespace detail
    {
        template<typename T, typename Allocator,
                 typename Compare, typename Projection>
        auto list_selection_sort(std::list<T, Allocator>& collection,
                                 Compare compare, Projection projection)
            -> void
        {
            auto it = std::begin(collection);
            auto last = std::end(collection);
            while (it != last)
            {
                auto min_it = min_element(it, last, compare, projection);
                if (min_it == it)
                {
                    ++it;
                }
                else
                {
                    collection.splice(it, collection, min_it);
                }
            }
        }

        template<typename T, typename Allocator,
                 typename Compare, typename Projection>
        auto flist_selection_sort(std::forward_list<T, Allocator>& collection,
                                  Compare compare, Projection projection)
            -> void
        {
            auto&& proj = utility::as_function(projection);

            auto first = collection.before_begin();
            auto last = collection.end();
            while (std::next(first) != last)
            {
                auto min_it = first;
                auto it = first;
                while (std::next(it) != last)
                {
                    if (compare(proj(*std::next(it)), proj(*std::next(min_it))))
                    {
                        min_it = it;
                    }
                    ++it;
                }

                collection.splice_after(first, collection, min_it);
                ++first;
            }
        }
    }

    template<>
    struct container_aware_adapter<selection_sorter>:
        detail::container_aware_adapter_base<selection_sorter>
    {
        using detail::container_aware_adapter_base<selection_sorter>::operator();

        ////////////////////////////////////////////////////////////
        // std::list

        template<typename T, typename Allocator>
        auto operator()(std::list<T, Allocator>& iterable) const
            -> void
        {
            detail::list_selection_sort(iterable, std::less<>{}, utility::identity{});
        }

        template<typename T, typename Allocator, typename Compare>
        auto operator()(std::list<T, Allocator>& iterable, Compare compare) const
            -> std::enable_if_t<
                is_projection_v<utility::identity, std::list<T, Allocator>, Compare>
            >
        {
            detail::list_selection_sort(iterable, compare, utility::identity{});
        }

        template<typename T, typename Allocator, typename Projection>
        auto operator()(std::list<T, Allocator>& iterable, Projection projection) const
            -> std::enable_if_t<
                is_projection_v<Projection, std::list<T, Allocator>>
            >
        {
            detail::list_selection_sort(iterable, std::less<>{}, projection);
        }

        template<
            typename T,
            typename Allocator,
            typename Compare,
            typename Projection,
            typename = std::enable_if_t<
                is_projection_v<Projection, std::list<T, Allocator>, Compare>
            >
        >
        auto operator()(std::list<T, Allocator>& iterable,
                        Compare compare, Projection projection) const
            -> void
        {
            detail::list_selection_sort(iterable, compare, projection);
        }

        ////////////////////////////////////////////////////////////
        // std::forward_list

        template<typename T, typename Allocator>
        auto operator()(std::forward_list<T, Allocator>& iterable) const
            -> void
        {
            detail::flist_selection_sort(iterable, std::less<>{}, utility::identity{});
        }

        template<typename T, typename Allocator, typename Compare>
        auto operator()(std::forward_list<T, Allocator>& iterable, Compare compare) const
            -> std::enable_if_t<
                is_projection_v<utility::identity, std::forward_list<T>, Compare>
            >
        {
            detail::flist_selection_sort(iterable, compare, utility::identity{});
        }

        template<typename T, typename Allocator, typename Projection>
        auto operator()(std::forward_list<T, Allocator>& iterable, Projection projection) const
            -> std::enable_if_t<
                is_projection_v<Projection, std::forward_list<T, Allocator>>
            >
        {
            detail::flist_selection_sort(iterable, std::less<>{}, projection);
        }

        template<
            typename T,
            typename Allocator,
            typename Compare,
            typename Projection,
            typename = std::enable_if_t<
                is_projection_v<Projection, std::forward_list<T, Allocator>, Compare>
            >
        >
        auto operator()(std::forward_list<T, Allocator>& iterable,
                        Compare compare, Projection projection) const
            -> void
        {
            detail::flist_selection_sort(iterable, compare, projection);
        }
    };
}

#endif // CPPSORT_DETAIL_CONTAINER_AWARE_SELECTION_SORT_H_
