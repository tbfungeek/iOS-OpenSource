//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// UNSUPPORTED: libcpp-has-no-threads
// UNSUPPORTED: c++03

// <future>

// class promise<R>

// promise& operator=(promise&& rhs);

#include <future>
#include <cassert>

#include "test_macros.h"
#include "test_allocator.h"

int main(int, char**)
{
    test_allocator_statistics alloc_stats;
    assert(alloc_stats.alloc_count == 0);
    {
        std::promise<int> p0(std::allocator_arg, test_allocator<int>(&alloc_stats));
        std::promise<int> p(std::allocator_arg, test_allocator<int>(&alloc_stats));
        assert(alloc_stats.alloc_count == 2);
        p = std::move(p0);
        assert(alloc_stats.alloc_count == 1);
        std::future<int> f = p.get_future();
        assert(alloc_stats.alloc_count == 1);
        assert(f.valid());
#ifndef TEST_HAS_NO_EXCEPTIONS
        try
        {
            f = p0.get_future();
            assert(false);
        }
        catch (const std::future_error& e)
        {
            assert(e.code() == make_error_code(std::future_errc::no_state));
        }
#endif
        assert(alloc_stats.alloc_count == 1);
    }
    assert(alloc_stats.alloc_count == 0);
    {
        std::promise<int&> p0(std::allocator_arg, test_allocator<int>(&alloc_stats));
        std::promise<int&> p(std::allocator_arg, test_allocator<int>(&alloc_stats));
        assert(alloc_stats.alloc_count == 2);
        p = std::move(p0);
        assert(alloc_stats.alloc_count == 1);
        std::future<int&> f = p.get_future();
        assert(alloc_stats.alloc_count == 1);
        assert(f.valid());
#ifndef TEST_HAS_NO_EXCEPTIONS
        try
        {
            f = p0.get_future();
            assert(false);
        }
        catch (const std::future_error& e)
        {
            assert(e.code() == make_error_code(std::future_errc::no_state));
        }
#endif
        assert(alloc_stats.alloc_count == 1);
    }
    assert(alloc_stats.alloc_count == 0);
    {
        std::promise<void> p0(std::allocator_arg, test_allocator<void>(&alloc_stats));
        std::promise<void> p(std::allocator_arg, test_allocator<void>(&alloc_stats));
        assert(alloc_stats.alloc_count == 2);
        p = std::move(p0);
        assert(alloc_stats.alloc_count == 1);
        std::future<void> f = p.get_future();
        assert(alloc_stats.alloc_count == 1);
        assert(f.valid());
#ifndef TEST_HAS_NO_EXCEPTIONS
        try
        {
            f = p0.get_future();
            assert(false);
        }
        catch (const std::future_error& e)
        {
            assert(e.code() == make_error_code(std::future_errc::no_state));
        }
#endif
        assert(alloc_stats.alloc_count == 1);
    }
    assert(alloc_stats.alloc_count == 0);

  return 0;
}
