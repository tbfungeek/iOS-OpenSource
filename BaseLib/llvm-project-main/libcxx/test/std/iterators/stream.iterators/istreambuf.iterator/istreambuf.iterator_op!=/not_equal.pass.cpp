//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <iterator>

// istreambuf_iterator

// template <class charT, class traits>
//   bool operator!=(const istreambuf_iterator<charT,traits>& a,
//                   const istreambuf_iterator<charT,traits>& b);

#include <iterator>
#include <sstream>
#include <cassert>

#include "test_macros.h"

int main(int, char**) {
  {
    std::istringstream inf1("abc");
    std::istringstream inf2("def");
    std::istreambuf_iterator<char> i1(inf1);
    std::istreambuf_iterator<char> i2(inf2);
    std::istreambuf_iterator<char> i3;
    std::istreambuf_iterator<char> i4;
    std::istreambuf_iterator<char> i5(nullptr);

    assert(!(i1 != i1));
    assert(!(i1 != i2));
    assert( (i1 != i3));
    assert( (i1 != i4));
    assert( (i1 != i5));

    assert(!(i2 != i1));
    assert(!(i2 != i2));
    assert( (i2 != i3));
    assert( (i2 != i4));
    assert( (i2 != i5));

    assert( (i3 != i1));
    assert( (i3 != i2));
    assert(!(i3 != i3));
    assert(!(i3 != i4));
    assert(!(i3 != i5));

    assert( (i4 != i1));
    assert( (i4 != i2));
    assert(!(i4 != i3));
    assert(!(i4 != i4));
    assert(!(i4 != i5));

    assert( (i5 != i1));
    assert( (i5 != i2));
    assert(!(i5 != i3));
    assert(!(i5 != i4));
    assert(!(i5 != i5));
  }

#if TEST_STD_VER > 17
  {
    std::istreambuf_iterator<char> i1;
    std::istreambuf_iterator<char> i2(std::default_sentinel);
    assert(i1 == i2);

    assert(!(i1 != std::default_sentinel));
    assert(!(i2 != std::default_sentinel));
    assert(!(std::default_sentinel != i1));
    assert(!(std::default_sentinel != i2));

    std::istringstream stream(" 1 23");
    std::istreambuf_iterator<char> i3(stream);

    assert(i3 != std::default_sentinel);
    assert(std::default_sentinel != i3);
  }
#endif

#ifndef TEST_HAS_NO_WIDE_CHARACTERS
  {
    std::wistringstream inf1(L"abc");
    std::wistringstream inf2(L"def");
    std::istreambuf_iterator<wchar_t> i1(inf1);
    std::istreambuf_iterator<wchar_t> i2(inf2);
    std::istreambuf_iterator<wchar_t> i3;
    std::istreambuf_iterator<wchar_t> i4;
    std::istreambuf_iterator<wchar_t> i5(nullptr);

    assert(!(i1 != i1));
    assert(!(i1 != i2));
    assert( (i1 != i3));
    assert( (i1 != i4));
    assert( (i1 != i5));

    assert(!(i2 != i1));
    assert(!(i2 != i2));
    assert( (i2 != i3));
    assert( (i2 != i4));
    assert( (i2 != i5));

    assert( (i3 != i1));
    assert( (i3 != i2));
    assert(!(i3 != i3));
    assert(!(i3 != i4));
    assert(!(i3 != i5));

    assert( (i4 != i1));
    assert( (i4 != i2));
    assert(!(i4 != i3));
    assert(!(i4 != i4));
    assert(!(i4 != i5));

    assert( (i5 != i1));
    assert( (i5 != i2));
    assert(!(i5 != i3));
    assert(!(i5 != i4));
    assert(!(i5 != i5));
  }
#endif // TEST_HAS_NO_WIDE_CHARACTERS

  return 0;
}
