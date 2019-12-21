/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016-2019 Morwenn
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
#ifndef CPPSORT_DETAIL_PROJECTION_COMPARE_H_
#define CPPSORT_DETAIL_PROJECTION_COMPARE_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <utility>
#include <cpp-sort/utility/as_function.h>

namespace cppsort::detail
{
    template<typename Compare, typename Projection>
    class projection_compare
    {
        private:

            using compare_t = decltype(utility::as_function(std::declval<Compare&>()));
            using projection_t = decltype(utility::as_function(std::declval<Projection&>()));
            [[no_unique_address]] compare_t comp;
            [[no_unique_address]] projection_t proj;

        public:

            projection_compare(Compare compare, Projection projection):
                comp(utility::as_function(compare)),
                proj(utility::as_function(projection))
            {}

            template<typename T, typename U>
            auto operator()(T&& lhs, U&& rhs)
                noexcept(noexcept(comp(proj(std::forward<T>(lhs)), proj(std::forward<U>(rhs)))))
                -> decltype(comp(proj(std::forward<T>(lhs)), proj(std::forward<U>(rhs))))
            {
                return comp(proj(std::forward<T>(lhs)), proj(std::forward<U>(rhs)));
            }
    };
}

#endif // CPPSORT_DETAIL_PROJECTION_COMPARE_H_
