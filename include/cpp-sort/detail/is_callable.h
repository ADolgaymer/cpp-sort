/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016-2017 Morwenn
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
#ifndef CPPSORT_DETAIL_IS_CALLABLE_H_
#define CPPSORT_DETAIL_IS_CALLABLE_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <type_traits>

namespace cppsort::detail
{
    template<typename T, typename Ret=void, typename=void>
    struct is_callable_impl:
        std::false_type
    {};

    template<typename Func, typename... Args>
    struct is_callable_impl<Func(Args...), void, std::void_t<std::result_of_t<Func(Args...)>>>:
        std::true_type
    {};

    template<typename Func, typename Ret, typename... Args>
    struct is_callable_impl<Func(Args...), Ret, std::void_t<std::result_of_t<Func(Args...)>>>:
        std::is_convertible<std::result_of_t<Func(Args...)>, Ret>
    {};

    //
    // is_callable type trait as proposed by P0077R2
    //

    template<typename T, typename Ret=void>
    struct is_callable:
        is_callable_impl<T, Ret>
    {};

    template<typename T, typename Ret=void>
    constexpr bool is_callable_v = is_callable<T, Ret>::value;
}

#endif // CPPSORT_DETAIL_IS_CALLABLE_H_
