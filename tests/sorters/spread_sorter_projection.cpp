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
#include <algorithm>
#include <functional>
#include <iterator>
#include <random>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include <catch2/catch.hpp>
#include <cpp-sort/sorters/spread_sorter.h>
#include <cpp-sort/sort.h>
#include "../algorithm.h"

namespace
{
    template<typename T>
    struct wrapper
    {
        wrapper(T value):
            value(std::move(value))
        {}

        std::string value;
    };
}

TEST_CASE( "spread_sorter tests with projections",
           "[spread_sorter][projection]" )
{
    // Pseudo-random number engine
    std::mt19937_64 engine(Catch::rngSeed());

    SECTION( "sort with int iterable" )
    {
        std::vector<std::pair<int, float>> vec;
        for (int i = 0 ; i < 100'000 ; ++i)
        {
            vec.emplace_back(i, i);
        }
        std::shuffle(std::begin(vec), std::end(vec), engine);
        cppsort::sort(cppsort::spread_sorter{}, vec,
                      &std::pair<int, float>::first);
        CHECK( helpers::is_sorted(std::begin(vec), std::end(vec),
                                  std::less<>{}, &std::pair<int, float>::second) );
    }

    SECTION( "sort with unsigned int iterators" )
    {
        std::vector<std::pair<unsigned, float>> vec;
        for (int i = 0 ; i < 100'000 ; ++i)
        {
            vec.emplace_back(i, i);
        }
        std::shuffle(std::begin(vec), std::end(vec), engine);
        cppsort::sort(cppsort::spread_sorter{}, vec,
                      &std::pair<unsigned, float>::first);
        CHECK( helpers::is_sorted(std::begin(vec), std::end(vec),
                                  std::less<>{}, &std::pair<unsigned, float>::second) );
    }

    SECTION( "sort with float iterable" )
    {
        std::vector<std::pair<int, float>> vec;
        for (int i = 0 ; i < 100'000 ; ++i)
        {
            vec.emplace_back(i, i);
        }
        std::shuffle(std::begin(vec), std::end(vec), engine);
        cppsort::sort(cppsort::spread_sorter{}, vec,
                      &std::pair<int, float>::second);
        CHECK( helpers::is_sorted(std::begin(vec), std::end(vec),
                                  std::less<>{}, &std::pair<int, float>::first) );
    }

    SECTION( "sort with double iterators" )
    {
        std::vector<std::pair<int, double>> vec;
        for (int i = 0 ; i < 100'000 ; ++i)
        {
            vec.emplace_back(i, i);
        }
        std::shuffle(std::begin(vec), std::end(vec), engine);
        cppsort::sort(cppsort::spread_sorter{}, vec,
                      &std::pair<int, double>::second);
        CHECK( helpers::is_sorted(std::begin(vec), std::end(vec),
                                  std::less<>{}, &std::pair<int, double>::first) );
    }

    SECTION( "sort with std::string iterators" )
    {
        std::vector<wrapper<std::string>> vec;
        for (int i = 0 ; i < 100'000 ; ++i) {
            vec.push_back({std::to_string(i)});
        }
        std::shuffle(std::begin(vec), std::end(vec), engine);
        cppsort::sort(cppsort::spread_sorter{}, vec, &wrapper<std::string>::value);
        CHECK( helpers::is_sorted(std::begin(vec), std::end(vec),
                                  std::less<>{}, &wrapper<std::string>::value) );
    }

    SECTION( "reverse sort with std::string iterators" )
    {
        std::vector<wrapper<std::string>> vec;
        for (int i = 0 ; i < 100'000 ; ++i) {
            vec.push_back({std::to_string(i)});
        }
        std::shuffle(std::begin(vec), std::end(vec), engine);
        cppsort::sort(cppsort::spread_sorter{}, vec, std::greater<>{}, &wrapper<std::string>::value);
        CHECK( helpers::is_sorted(std::begin(vec), std::end(vec),
                                  std::greater<>{}, &wrapper<std::string>::value) );
    }

    SECTION( "sort with std::string_view iterators" )
    {
        std::vector<std::string> string_vec;
        for (int i = 0 ; i < 100'000 ; ++i) {
            string_vec.push_back({std::to_string(i)});
        }
        std::vector<wrapper<std::string_view>> vec(std::begin(string_vec), std::end(string_vec));

        std::shuffle(std::begin(vec), std::end(vec), engine);
        cppsort::sort(cppsort::spread_sorter{}, vec, &wrapper<std::string_view>::value);
        CHECK( helpers::is_sorted(std::begin(vec), std::end(vec),
                                  std::less<>{}, &wrapper<std::string_view>::value) );
    }

    SECTION( "reverse sort with std::string_view iterators" )
    {
        std::vector<std::string> string_vec;
        for (int i = 0 ; i < 100'000 ; ++i) {
            string_vec.push_back({std::to_string(i)});
        }
        std::vector<wrapper<std::string_view>> vec(std::begin(string_vec), std::end(string_vec));

        std::shuffle(std::begin(vec), std::end(vec), engine);
        cppsort::sort(cppsort::spread_sorter{}, vec, std::greater<>{}, &wrapper<std::string_view>::value);
        CHECK( helpers::is_sorted(std::begin(vec), std::end(vec),
                                  std::greater<>{}, &wrapper<std::string_view>::value) );
    }
}