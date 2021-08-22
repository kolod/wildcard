//================================================================================
//
// Copyright (c) 2021 by Oleksandr Kolodkin <alexandr.kolodkin@gmail.com>
//
// This file is provided under the terms of the MIT License:
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//================================================================================

// https://stackoverflow.com/questions/22950412/c-cant-get-wcout-to-print-unicode-and-leave-cout-working

#pragma once

#include <iostream>
#include <locale>
#include <locale.h>
#include <stdlib.h>

#ifndef MS_STDLIB_BUGS // Allow overriding the autodetection.
// The Microsoft C and C++ runtime libraries that ship with Visual Studio, as
// of 2017, have a bug that neither stdio, iostreams or wide iostreams can
// handle Unicode input or output.  Windows needs some non-standard magic to
// work around that.  This includes programs compiled with MinGW and Clang
// for the win32 and win64 targets.
#if (_MSC_VER || __MINGW32__ || __MSVCRT__)
// This code is being compiled either on MS Visual C++, or MinGW, or clang++
// in compatibility mode for either, or is being linked to the msvcrt.dll runtime.
#define MS_STDLIB_BUGS 1
#else
#define MS_STDLIB_BUGS 0
#endif
#endif

#if MS_STDLIB_BUGS
#include <io.h>
#include <fcntl.h>
#endif

// Does magic so that wcout can work.
void init_locale(void);
