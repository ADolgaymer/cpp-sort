/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015-2016 Morwenn
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
#ifndef CPPSORT_UTILITY_FUNCTIONAL_H_
#define CPPSORT_UTILITY_FUNCTIONAL_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>
#include <utility>

namespace cppsort
{
namespace utility
{
    ////////////////////////////////////////////////////////////
    // Identity (mostly useful for projections)

    struct identity
    {
        template<typename T>
        constexpr auto operator()(T&& value) const noexcept
            -> T&&
        {
            return std::forward<T>(value);
        }

        using is_transparent = void;
    };

    ////////////////////////////////////////////////////////////
    // Math functions (mostly useful for buffer providers)

    struct half
    {
        template<typename T>
        constexpr auto operator()(T&& value) const
            -> decltype(std::forward<T>(value) / 2)
        {
            return std::forward<T>(value) / 2;
        }
    };

    struct log
    {
        template<typename T>
        constexpr auto operator()(T&& value) const
            -> decltype(auto)
        {
            using std::log;
            return log(std::forward<T>(value));
        }
    };

    struct sqrt
    {
        template<typename T>
        constexpr auto operator()(T&& value) const
            -> decltype(auto)
        {
            using std::sqrt;
            return sqrt(std::forward<T>(value));
        }
    };
}}

#endif // CPPSORT_UTILITY_FUNCTIONAL_H_
